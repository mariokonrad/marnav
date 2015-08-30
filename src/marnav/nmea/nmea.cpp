	#include "nmea.hpp"

	#include <algorithm>
#include <regex>

#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/date.hpp>
#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/aam.hpp>
#include <marnav/nmea/alm.hpp>
#include <marnav/nmea/apb.hpp>
#include <marnav/nmea/bod.hpp>
#include <marnav/nmea/bwc.hpp>
#include <marnav/nmea/bwr.hpp>
#include <marnav/nmea/bww.hpp>
#include <marnav/nmea/dbk.hpp>
#include <marnav/nmea/dbt.hpp>
#include <marnav/nmea/dpt.hpp>
#include <marnav/nmea/dsc.hpp>
#include <marnav/nmea/dse.hpp>
#include <marnav/nmea/dtm.hpp>
#include <marnav/nmea/fsi.hpp>
#include <marnav/nmea/gbs.hpp>
#include <marnav/nmea/gga.hpp>
#include <marnav/nmea/glc.hpp>
#include <marnav/nmea/gll.hpp>
#include <marnav/nmea/gns.hpp>
#include <marnav/nmea/grs.hpp>
#include <marnav/nmea/gsa.hpp>
#include <marnav/nmea/gst.hpp>
#include <marnav/nmea/gsv.hpp>
#include <marnav/nmea/gtd.hpp>
#include <marnav/nmea/hdg.hpp>
#include <marnav/nmea/hfb.hpp>
#include <marnav/nmea/hdm.hpp>
#include <marnav/nmea/hsc.hpp>
#include <marnav/nmea/lcd.hpp>
#include <marnav/nmea/msk.hpp>
#include <marnav/nmea/mss.hpp>
#include <marnav/nmea/mtw.hpp>
#include <marnav/nmea/mwd.hpp>
#include <marnav/nmea/mwv.hpp>
#include <marnav/nmea/osd.hpp>
#include <marnav/nmea/r00.hpp>
#include <marnav/nmea/rma.hpp>
#include <marnav/nmea/rmb.hpp>
#include <marnav/nmea/rmc.hpp>
#include <marnav/nmea/rot.hpp>
#include <marnav/nmea/rpm.hpp>
#include <marnav/nmea/rsa.hpp>
#include <marnav/nmea/rsd.hpp>
#include <marnav/nmea/rte.hpp>
#include <marnav/nmea/sfi.hpp>
#include <marnav/nmea/tds.hpp>
#include <marnav/nmea/tfi.hpp>
#include <marnav/nmea/tll.hpp>
#include <marnav/nmea/tpc.hpp>
#include <marnav/nmea/tpr.hpp>
#include <marnav/nmea/tpt.hpp>
#include <marnav/nmea/ttm.hpp>
#include <marnav/nmea/vbw.hpp>
#include <marnav/nmea/vdm.hpp>
#include <marnav/nmea/vdo.hpp>
#include <marnav/nmea/vdr.hpp>
#include <marnav/nmea/vhw.hpp>
#include <marnav/nmea/vlw.hpp>
#include <marnav/nmea/vpw.hpp>
#include <marnav/nmea/vtg.hpp>
#include <marnav/nmea/vwr.hpp>
#include <marnav/nmea/wcv.hpp>
#include <marnav/nmea/wnc.hpp>
#include <marnav/nmea/wpl.hpp>
#include <marnav/nmea/xdr.hpp>
#include <marnav/nmea/xte.hpp>
#include <marnav/nmea/xtr.hpp>
#include <marnav/nmea/zda.hpp>
#include <marnav/nmea/zdl.hpp>
#include <marnav/nmea/zfo.hpp>
#include <marnav/nmea/ztg.hpp>
#include <marnav/nmea/pgrme.hpp>
#include <marnav/utils/unique.hpp>

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
	REGISTER_SENTENCE(dtm), REGISTER_SENTENCE(fsi), REGISTER_SENTENCE(gbs),
	REGISTER_SENTENCE(gga), REGISTER_SENTENCE(glc), REGISTER_SENTENCE(gll),
	REGISTER_SENTENCE(grs), REGISTER_SENTENCE(gns), REGISTER_SENTENCE(gsa),
	REGISTER_SENTENCE(gst), REGISTER_SENTENCE(gsv), REGISTER_SENTENCE(gtd),
	REGISTER_SENTENCE(hdg), REGISTER_SENTENCE(hfb), REGISTER_SENTENCE(hdm),
	REGISTER_SENTENCE(hsc), REGISTER_SENTENCE(lcd), REGISTER_SENTENCE(msk),
	REGISTER_SENTENCE(mss), REGISTER_SENTENCE(mtw), REGISTER_SENTENCE(mwd),
	REGISTER_SENTENCE(mwv), REGISTER_SENTENCE(osd), REGISTER_SENTENCE(r00),
	REGISTER_SENTENCE(rma), REGISTER_SENTENCE(rmb), REGISTER_SENTENCE(rmc),
	REGISTER_SENTENCE(rot), REGISTER_SENTENCE(rpm), REGISTER_SENTENCE(rsa),
	REGISTER_SENTENCE(rsd), REGISTER_SENTENCE(rte), REGISTER_SENTENCE(sfi),
	REGISTER_SENTENCE(tds), REGISTER_SENTENCE(tfi), REGISTER_SENTENCE(tll),
	REGISTER_SENTENCE(tpc), REGISTER_SENTENCE(tpr), REGISTER_SENTENCE(tpt),
	REGISTER_SENTENCE(ttm), REGISTER_SENTENCE(vbw), REGISTER_SENTENCE(vdm),
	REGISTER_SENTENCE(vdo), REGISTER_SENTENCE(vdr), REGISTER_SENTENCE(vhw),
	REGISTER_SENTENCE(vlw), REGISTER_SENTENCE(vpw), REGISTER_SENTENCE(vtg),
	REGISTER_SENTENCE(vwr), REGISTER_SENTENCE(wcv), REGISTER_SENTENCE(wnc),
	REGISTER_SENTENCE(wpl), REGISTER_SENTENCE(xdr), REGISTER_SENTENCE(xte),
	REGISTER_SENTENCE(xtr), REGISTER_SENTENCE(zda), REGISTER_SENTENCE(zdl),
	REGISTER_SENTENCE(zfo), REGISTER_SENTENCE(ztg),

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
/// @exception std::invalid_argument The specified address was probably malformed or
//    empty.
static std::tuple<std::string, std::string> parse_address(const std::string & address) throw(
	std::invalid_argument)
{
	if (address.empty())
		throw std::invalid_argument{"invalid/malformed address in nmea/parse_address"};

	// check for vendor extensions
	if (address[0] == 'P') {
		// properitary extension / vendor extension
		return make_tuple(std::string{}, address);
	}

	// search in all known sentences
	auto const & index = std::find_if(begin(known_sentences), end(known_sentences),
		[address](const entry & e) { return e.TAG == address; });
	if (index != end(known_sentences))
		throw std::invalid_argument{"invalid address (" + address + ") in nmea/parse_address"};

	// found regular sentence
	if (address.size() != 5) // talker ID:2 + tag:3
		throw std::invalid_argument{"unknown or malformed address field: [" + address + "]"};

	return make_tuple(address.substr(0, 2), address.substr(2, 3));
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
	for_each(begin(s) + 1, begin(s) + end_pos,
		[&checksum](char c) { checksum ^= static_cast<uint8_t>(c); });
	const uint8_t expected_checksum
		= static_cast<uint8_t>(std::stoul(fields.back(), nullptr, 16));
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
