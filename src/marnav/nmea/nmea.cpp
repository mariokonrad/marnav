#include "nmea.hpp"
#include "angle.hpp"
#include "time.hpp"
#include "date.hpp"
#include "sentence.hpp"
#include "aam.hpp"
#include "alm.hpp"
#include "apb.hpp"
#include "bod.hpp"
#include "bwc.hpp"
#include "bwr.hpp"
#include "bww.hpp"
#include "dbk.hpp"
#include "dbt.hpp"
#include "dpt.hpp"
#include "dsc.hpp"
#include "dse.hpp"
#include "fsi.hpp"
#include "gga.hpp"
#include "gll.hpp"
#include "gns.hpp"
#include "gsa.hpp"
#include "gsv.hpp"
#include "hdg.hpp"
#include "hdm.hpp"
#include "hsc.hpp"
#include "mtw.hpp"
#include "mwd.hpp"
#include "mwv.hpp"
#include "osd.hpp"
#include "r00.hpp"
#include "rma.hpp"
#include "rmb.hpp"
#include "rmc.hpp"
#include "rot.hpp"
#include "rsa.hpp"
#include "rte.hpp"
#include "sfi.hpp"
#include "vbw.hpp"
#include "vdm.hpp"
#include "vdo.hpp"
#include "vdr.hpp"
#include "vhw.hpp"
#include "vlw.hpp"
#include "vpw.hpp"
#include "vtg.hpp"
#include "vwr.hpp"
#include "wcv.hpp"
#include "wnc.hpp"
#include "wpl.hpp"
#include "xdr.hpp"
#include "xte.hpp"
#include "xtr.hpp"
#include "zda.hpp"
#include "zdl.hpp"
#include "zfo.hpp"
#include "ztg.hpp"
#include "pgrme.hpp"
#include <marnav/utils/unique.hpp>
#include <algorithm>
#include <regex>

/// @example parse_nmea.cpp
/// This is an example on how to parse and handle NMEA sentences from a string.

namespace marnav
{
namespace nmea
{

namespace
{
// local macro, used for convenience while registering sentences
#define REGISTER_SENTENCE(s)    \
	{                           \
		s::TAG, s::ID, s::parse \
	}

struct entry {
	const char * TAG;
	const sentence_id ID;
	const sentence::parse_function parse;
};
static const std::vector<entry> known_sentences = {
	// regular
	REGISTER_SENTENCE(aam), REGISTER_SENTENCE(alm), REGISTER_SENTENCE(apb),
	REGISTER_SENTENCE(bod), REGISTER_SENTENCE(bwc), REGISTER_SENTENCE(bwr),
	REGISTER_SENTENCE(bww), REGISTER_SENTENCE(dbk), REGISTER_SENTENCE(dbt),
	REGISTER_SENTENCE(dpt), REGISTER_SENTENCE(dsc), REGISTER_SENTENCE(dse),
	REGISTER_SENTENCE(fsi), REGISTER_SENTENCE(gga), REGISTER_SENTENCE(gll),
	REGISTER_SENTENCE(gns), REGISTER_SENTENCE(gsa), REGISTER_SENTENCE(gsv),
	REGISTER_SENTENCE(hdg), REGISTER_SENTENCE(hdm), REGISTER_SENTENCE(hsc),
	REGISTER_SENTENCE(mtw), REGISTER_SENTENCE(mwd), REGISTER_SENTENCE(mwv),
	REGISTER_SENTENCE(osd), REGISTER_SENTENCE(r00), REGISTER_SENTENCE(rma),
	REGISTER_SENTENCE(rmb), REGISTER_SENTENCE(rmc), REGISTER_SENTENCE(rot),
	REGISTER_SENTENCE(rsa), REGISTER_SENTENCE(rte), REGISTER_SENTENCE(sfi),
	REGISTER_SENTENCE(vbw), REGISTER_SENTENCE(vdm), REGISTER_SENTENCE(vdo),
	REGISTER_SENTENCE(vdr), REGISTER_SENTENCE(vhw), REGISTER_SENTENCE(vlw),
	REGISTER_SENTENCE(vpw), REGISTER_SENTENCE(vtg), REGISTER_SENTENCE(vwr),
	REGISTER_SENTENCE(wcv), REGISTER_SENTENCE(wnc), REGISTER_SENTENCE(wpl),
	REGISTER_SENTENCE(xdr), REGISTER_SENTENCE(xte), REGISTER_SENTENCE(xtr),
	REGISTER_SENTENCE(zda), REGISTER_SENTENCE(zdl), REGISTER_SENTENCE(zfo),
	REGISTER_SENTENCE(ztg),

	// vendor extensions
	REGISTER_SENTENCE(pgrme)};

#undef REGISTER_SENTENCE
}

checksum_error::checksum_error(uint8_t expected, uint8_t actual)
	: expected(expected)
	, actual(actual)
{
	char buf[64];
	snprintf(buf, sizeof(buf), "checksum error (actual:%02X, expected:%02X)", actual, expected);
	text = buf;
}

/// Returns a list of tags of supported sentences.
std::vector<std::string> get_supported_sentences_str()
{
	std::vector<std::string> v;
	v.reserve(known_sentences.size());
	for (auto const & s : known_sentences) {
		v.push_back(s.TAG);
	}
	return v;
}

/// Returns a list of IDs of supported sentences.
std::vector<sentence_id> get_supported_sentences_id()
{
	std::vector<sentence_id> v;
	v.reserve(known_sentences.size());
	for (auto const & s : known_sentences) {
		v.push_back(s.ID);
	}
	return v;
}

/// Returns the tag of the specified ID. If the sentence is unknown,
/// an exception is thrown.
std::string to_string(sentence_id id) throw(unknown_sentence)
{
	using namespace std;
	auto i = find_if(begin(known_sentences), end(known_sentences),
		[id](const entry & e) { return e.ID == id; });
	if (i == end(known_sentences))
		throw unknown_sentence{"unknown sentence"};

	return i->TAG;
}

/// Returns the ID of the specified tag. If the sentence is unknown,
/// an exceptioni s thrown.
sentence_id tag_to_id(const std::string & tag) throw(unknown_sentence)
{
	using namespace std;
	auto i = find_if(begin(known_sentences), end(known_sentences),
		[tag](const entry & e) { return e.TAG == tag; });
	if (i == end(known_sentences))
		throw unknown_sentence{"unknown sentence: " + tag};

	return i->ID;
}

/// Returns the parse function of a particular sentence.
///
/// If an unknown sentence tag is specified, an exception is thrown.
///
/// @param[in] tag The tag of the sentence to get the parse function for.
/// @return The parse function of the specified sentence.
/// @exception std::unknown_sentence The specified tag could not be found,
///   the argument cannot be processed.
static sentence::parse_function instantiate_sentence(const std::string & tag) throw(
	unknown_sentence)
{
	using namespace std;

	auto const & i = std::find_if(begin(known_sentences), end(known_sentences),
		[tag](const entry & e) { return e.TAG == tag; });

	if (i == end(known_sentences))
		throw unknown_sentence{"unknown sentence in nmea/instantiate_sentence: " + tag};

	return i->parse;
}

/// Checks if the address field of the specified sentence is a vendor extension or
/// a regular sentence. It returns the talker ID and tag accordingly.
///
/// @param[in] address The address field of a sentence.
/// @return The tuple contains talker ID and tag. In case of a vendor extension,
///   the talker ID may be empty.
static std::tuple<std::string, std::string> parse_address(const std::string & address)
{
	auto const & index = std::find_if(begin(known_sentences), end(known_sentences),
		[address](const entry & e) { return e.TAG == address; });
	if (index == end(known_sentences)) {
		// regular
		if (address.size() < 5) // talker ID:2 + tag:3
			throw std::invalid_argument{"unknown or malformed address field: " + address};
		return make_tuple(address.substr(0, 2), address.substr(2, 3));
	} else {
		// vendor extension
		return make_tuple(std::string{}, address);
	}
}

/// Parses the string and returns the corresponding sentence.
///
/// @param[in] s The sentence to parse.
/// @return The object of the corresponding type.
/// @exception checksum_error Will be thrown if the checksum is wrong.
/// @exception std::invalid_argument Will be thrown if the specified string
///   is not a NMEA sentence (malformed).
/// @exception unknown_sentence Will be thrown if the sentence is
///   not supported.
///
/// Example:
/// @code
///   auto s =
///   nmea::make_sentence("$GPRMC,201034,A,4702.4040,N,00818.3281,E,0.0,328.4,260807,0.6,E,A*17");
/// @endcode
std::unique_ptr<sentence> make_sentence(const std::string & s) throw(
	std::invalid_argument, checksum_error, unknown_sentence)
{
	using namespace std;

	// perform various checks
	if (s.empty())
		throw invalid_argument{"empty string in nmea/make_sentence"};
	if ((s[0] != sentence::START_TOKEN) && (s[0] != sentence::START_TOKEN_AIS))
		throw invalid_argument{"no start token in nmea/make_sentence"};

	// extract all fields, skip start token
	std::regex field_regex{"(,|\\*)"};
	auto fields_begin = std::sregex_token_iterator{begin(s) + 1, end(s), field_regex, -1};
	auto fields_end = std::sregex_token_iterator();
	std::vector<std::string> fields{fields_begin, fields_end};
	if (fields.size() < 2) // at least address and checksum must be present
		throw std::invalid_argument{"malformed sentence in nmea/make_sentence"};

	// compute and check checksum
	auto const end_pos = s.find_first_of(sentence::END_TOKEN, 1);
	if (end_pos == std::string::npos) // end token not found
		throw invalid_argument{"invalid format in nmea/make_sentence"};
	if (s.size() != end_pos + 3) // short or no checksum
		throw invalid_argument{"invalid format in nmea/make_sentence"};
	uint8_t checksum = 0x00;
	for_each(begin(s) + 1, begin(s) + end_pos, [&checksum](char c) { checksum ^= c; });
	const uint8_t expected_checksum = stoul(fields.back(), 0, 16);
	if (checksum != expected_checksum)
		throw checksum_error{expected_checksum, checksum};

	// extract address and posibly talker_id and tag.
	// check for vendor extension is necessary because the address field of this extensions
	// to not follow the pattern talker_id/tag
	std::string talker;
	std::string tag;
	std::tie(talker, tag) = parse_address(fields.front());

	return instantiate_sentence(tag)(
		talker, std::vector<std::string>{fields.begin() + 1, fields.end() - 1});
}
}
}
