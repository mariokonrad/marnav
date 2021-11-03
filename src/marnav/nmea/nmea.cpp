#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/checksum.hpp>
#include <marnav/nmea/date.hpp>
#include <marnav/nmea/detail.hpp>
#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/aam.hpp>
#include <marnav/nmea/alm.hpp>
#include <marnav/nmea/apa.hpp>
#include <marnav/nmea/apb.hpp>
#include <marnav/nmea/bec.hpp>
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
#include <marnav/nmea/hdm.hpp>
#include <marnav/nmea/hdt.hpp>
#include <marnav/nmea/hfb.hpp>
#include <marnav/nmea/hsc.hpp>
#include <marnav/nmea/its.hpp>
#include <marnav/nmea/lcd.hpp>
#include <marnav/nmea/mob.hpp>
#include <marnav/nmea/msk.hpp>
#include <marnav/nmea/mss.hpp>
#include <marnav/nmea/mta.hpp>
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
#include <marnav/nmea/stn.hpp>
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
#include <marnav/nmea/wdr.hpp>
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
#include <marnav/nmea/pgrmm.hpp>
#include <marnav/nmea/pgrmz.hpp>
#include <marnav/nmea/stalk.hpp>
#include <algorithm>
#include <string>

/// @example parse_nmea.cpp
/// This is an example on how to parse and handle NMEA sentences from a string.

namespace marnav
{
namespace nmea
{
/// @cond DEV
namespace
{
// local macro, used for convenience while registering sentences
#define REGISTER_SENTENCE(s)                     \
	{                                            \
		s::TAG, s::ID, detail::factory::parse<s> \
	}

struct entry {
	const char * TAG;
	const sentence_id ID;
	const sentence::parse_function parse;
};
static const std::vector<entry> known_sentences = {
	// regular
	REGISTER_SENTENCE(aam), REGISTER_SENTENCE(alm), REGISTER_SENTENCE(apa),
	REGISTER_SENTENCE(apb), REGISTER_SENTENCE(bec), REGISTER_SENTENCE(bod),
	REGISTER_SENTENCE(bwc), REGISTER_SENTENCE(bwr), REGISTER_SENTENCE(bww),
	REGISTER_SENTENCE(dbk), REGISTER_SENTENCE(dbt), REGISTER_SENTENCE(dpt),
	REGISTER_SENTENCE(dsc), REGISTER_SENTENCE(dse), REGISTER_SENTENCE(dtm),
	REGISTER_SENTENCE(fsi), REGISTER_SENTENCE(gbs), REGISTER_SENTENCE(gga),
	REGISTER_SENTENCE(glc), REGISTER_SENTENCE(gll), REGISTER_SENTENCE(grs),
	REGISTER_SENTENCE(gns), REGISTER_SENTENCE(gsa), REGISTER_SENTENCE(gst),
	REGISTER_SENTENCE(gsv), REGISTER_SENTENCE(gtd), REGISTER_SENTENCE(hdg),
	REGISTER_SENTENCE(hfb), REGISTER_SENTENCE(hdm), REGISTER_SENTENCE(hdt),
	REGISTER_SENTENCE(hsc), REGISTER_SENTENCE(its), REGISTER_SENTENCE(lcd),
	REGISTER_SENTENCE(mob), REGISTER_SENTENCE(msk), REGISTER_SENTENCE(mss),
	REGISTER_SENTENCE(mta), REGISTER_SENTENCE(mtw), REGISTER_SENTENCE(mwd),
	REGISTER_SENTENCE(mwv), REGISTER_SENTENCE(osd), REGISTER_SENTENCE(r00),
	REGISTER_SENTENCE(rma), REGISTER_SENTENCE(rmb), REGISTER_SENTENCE(rmc),
	REGISTER_SENTENCE(rot), REGISTER_SENTENCE(rpm), REGISTER_SENTENCE(rsa),
	REGISTER_SENTENCE(rsd), REGISTER_SENTENCE(rte), REGISTER_SENTENCE(sfi),
	REGISTER_SENTENCE(stn), REGISTER_SENTENCE(tds), REGISTER_SENTENCE(tfi),
	REGISTER_SENTENCE(tll), REGISTER_SENTENCE(tpc), REGISTER_SENTENCE(tpr),
	REGISTER_SENTENCE(tpt), REGISTER_SENTENCE(ttm), REGISTER_SENTENCE(vbw),
	REGISTER_SENTENCE(vdm), REGISTER_SENTENCE(vdo), REGISTER_SENTENCE(vdr),
	REGISTER_SENTENCE(vhw), REGISTER_SENTENCE(vlw), REGISTER_SENTENCE(vpw),
	REGISTER_SENTENCE(vtg), REGISTER_SENTENCE(vwr), REGISTER_SENTENCE(wcv),
	REGISTER_SENTENCE(wdr), REGISTER_SENTENCE(wnc), REGISTER_SENTENCE(wpl),
	REGISTER_SENTENCE(xdr), REGISTER_SENTENCE(xte), REGISTER_SENTENCE(xtr),
	REGISTER_SENTENCE(zda), REGISTER_SENTENCE(zdl), REGISTER_SENTENCE(zfo),
	REGISTER_SENTENCE(ztg),

	// vendor extensions
	REGISTER_SENTENCE(pgrme), REGISTER_SENTENCE(pgrmm), REGISTER_SENTENCE(pgrmz),
	REGISTER_SENTENCE(stalk)};
#undef REGISTER_SENTENCE
}

/// @endcond

/// @cond DEV
namespace detail
{
/// Searches in the known sentences for the entry carrying the specified tag.
static std::vector<entry>::const_iterator find_tag(const std::string & tag)
{
	return std::find_if(std::begin(known_sentences), std::end(known_sentences),
		[tag](const entry & e) { return e.TAG == tag; });
}

/// Returns the parse function of a particular sentence.
///
/// If an unknown sentence tag is specified, an exception is thrown.
///
/// @param[in] tag The tag of the sentence to get the parse function for.
/// @return The parse function of the specified sentence.
/// @exception std::unknown_sentence The specified tag could not be found,
///   the argument cannot be processed.
static sentence::parse_function find_parse_func(const std::string & tag)
{
	const auto i = find_tag(tag);
	if (i == std::end(known_sentences))
		throw unknown_sentence{"unknown sentence in nmea/find_parse_func: " + tag};

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
///
/// @note This function must be defined here, not in the file detail.cpp,
///       because it needs access to the known sentences, which the other file
///       does not, nor should have.
std::tuple<talker, std::string> parse_address(const std::string & address)
{
	if (address.empty())
		throw std::invalid_argument{"invalid/malformed address in nmea/parse_address"};

	// if the address is found as-is, it's a proprietary sentence, respectively
	// an address without a talker.
	if (find_tag(address) != std::end(known_sentences))
		return make_tuple(talker::none, address);

	// if the address looks like a regular address, we search for it, if not, it's an error
	if (address.size() != 5u) // talker ID:2 + tag:3
		throw std::invalid_argument{"unknown or malformed address field: [" + address + "]"};

	const auto tag = address.substr(2, 3);
	if (find_tag(tag) == std::end(known_sentences))
		throw std::invalid_argument("unknown regular tag in address: [" + address + "]");
	return make_tuple(make_talker(address.substr(0, 2)), tag);
}

/// Computes and checks the checksum of the specified sentence against the
/// expected checksum.
///
/// @param[in] s Sentence to check.
/// @param[in] expected The expected checksum to test against.
/// @param[in] start_pos Position within the sentence to start with computation of the checksum.
/// @exception checksum_error Thrown if the checksum does not match.
/// @exception std::invalid_argument Arguments were invalid.
///
/// @note This function must be defined here, not in the file detail.cpp,
///       because it needs access to the class sentence, which the other file
///       does not, nor should have.
///
/// @todo Parameters s/start_pos should be replaced with `string_view`, but not available in
/// C++11.
///
void ensure_checksum(
	const std::string & s, const std::string & expected, std::string::size_type start_pos)
{
	const auto end_pos = s.find_first_of(sentence::end_token, start_pos);
	if (end_pos == std::string::npos) // end token not found
		throw std::invalid_argument{"invalid format in nmea/ensure_checksum"};
	if (s.size() != end_pos + 3) // short or no checksum
		throw std::invalid_argument{"invalid format in nmea/ensure_checksum"};
	const uint8_t expected_checksum = static_cast<uint8_t>(std::stoul(expected, nullptr, 16));
	const uint8_t sum = checksum(begin(s) + start_pos, begin(s) + end_pos);
	if (expected_checksum != sum)
		throw checksum_error{expected_checksum, sum};
}

/// @note This function must be defined here, not in the file detail.cpp,
///       because it needs access to the class sentence, which the other file
///       does not, nor should have.
void check_raw_sentence(const std::string & s)
{
	// perform various checks
	if (s.empty())
		throw std::invalid_argument{"empty string in nmea/make_sentence"};
	if ((s[0] != sentence::start_token) && (s[0] != sentence::start_token_ais)
		&& (s[0] != sentence::tag_block_token))
		throw std::invalid_argument{"no start token in nmea/make_sentence"};
}
}
/// @endcond

/// Returns a list of tags of supported sentences.
std::vector<std::string> get_supported_sentences_str()
{
	std::vector<std::string> v;
	v.reserve(std::distance(std::begin(known_sentences), std::end(known_sentences)));
	for (const auto & s : known_sentences) {
		v.push_back(s.TAG);
	}
	return v;
}

/// Returns a list of IDs of supported sentences.
std::vector<sentence_id> get_supported_sentences_id()
{
	std::vector<sentence_id> v;
	v.reserve(std::distance(std::begin(known_sentences), std::end(known_sentences)));
	for (const auto & s : known_sentences) {
		v.push_back(s.ID);
	}
	return v;
}

/// Returns the tag of the specified ID. If the sentence is unknown,
/// an exception is thrown.
std::string to_string(sentence_id id)
{
	auto i = std::find_if(std::begin(known_sentences), std::end(known_sentences),
		[id](const entry & e) { return e.ID == id; });
	if (i == std::end(known_sentences))
		throw unknown_sentence{"unknown sentence"};

	return i->TAG;
}

/// Returns the ID of the specified tag. If the sentence is unknown,
/// an exceptioni s thrown.
sentence_id tag_to_id(const std::string & tag)
{
	const auto i = detail::find_tag(tag);
	if (i == std::end(known_sentences))
		throw unknown_sentence{"unknown sentence: " + tag};

	return i->ID;
}

/// Parses the string and returns the corresponding sentence.
///
/// @param[in] s The sentence to parse.
/// @param[in] chksum Checksum handling strategy.
/// @return The object of the corresponding type.
/// @exception checksum_error Will be thrown if the checksum is wrong.
/// @exception std::invalid_argument Will be thrown if the specified string
///   is not a NMEA sentence (malformed).
/// @exception unknown_sentence Will be thrown if the sentence is not supported.
///
/// Example:
/// @code
///   auto s = nmea::make_sentence("$IIVWR,084.0,R,10.4,N,5.4,M,19.3,K*4A");
/// @endcode
///
/// Example with ignoring the checksum:
/// @code
///   auto s = nmea::make_sentence("$IIVWR,084.0,R,10.4,N,5.4,M,19.3,K*00",
///                                checksum_handling::ignore);
/// @endcode
std::unique_ptr<sentence> make_sentence(const std::string & s, checksum_handling chksum)
{
	talker talk{talker::none};
	std::string tag;
	std::string tag_block;
	std::vector<std::string> fields;
	std::tie(talk, tag, tag_block, fields) = detail::extract_sentence_information(s, chksum);
	auto result = detail::find_parse_func(tag)(
		talk, std::next(std::begin(fields)), std::prev(std::end(fields)));
	result->set_tag_block(tag_block);
	return result;
}

/// Extracts and returns the sentence ID of the specified raw NMEA sentence.
///
/// This function does not check the checksum.
///
/// @param[in] s The raw NMEA sentence.
/// @return The sentence ID.
/// @exception std::invalid_argument Thrown if the sentence is in invalid form.
sentence_id extract_id(const std::string & s)
{
	detail::check_raw_sentence(s);

	std::string::size_type search_pos = 0;

	// skip tag block
	if (s[0] == sentence::tag_block_token) {
		const auto i = s.find(sentence::tag_block_token, 1);
		if (i != std::string::npos)
			search_pos = i + 1;
	}

	// get ID from first (regular) field
	const auto pos = s.find_first_of(",", search_pos);
	if (pos == std::string::npos)
		throw std::invalid_argument{"malformed sentence in extract_id"};

	talker talk{talker::none};
	std::string tag;
	std::tie(talk, tag) = detail::parse_address(s.substr(search_pos + 1, pos - search_pos - 1));

	return tag_to_id(tag);
}
}
}
