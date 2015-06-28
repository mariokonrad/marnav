#include "nmea.hpp"
#include "angle.hpp"
#include "time.hpp"
#include "date.hpp"
#include "sentence.hpp"
#include "aam.hpp"
#include "bod.hpp"
#include "dbk.hpp"
#include "dbt.hpp"
#include "dpt.hpp"
#include "gga.hpp"
#include "gll.hpp"
#include "gsa.hpp"
#include "gsv.hpp"
#include "hdg.hpp"
#include "hdm.hpp"
#include "mtw.hpp"
#include "mwd.hpp"
#include "mwv.hpp"
#include "r00.hpp"
#include "rma.hpp"
#include "rmb.hpp"
#include "rmc.hpp"
#include "rsa.hpp"
#include "rte.hpp"
#include "vhw.hpp"
#include "vlw.hpp"
#include "vtg.hpp"
#include "vwr.hpp"
#include "vdm.hpp"
#include "vdo.hpp"
#include "wnc.hpp"
#include "wpl.hpp"
#include "xdr.hpp"
#include "xte.hpp"
#include "zda.hpp"
#include <marnav/utils/unique.hpp>
#include <algorithm>
#include <regex>

/// @example parse_nmea.cpp
/// This is an example on how to parse and handle NMEA sentences from a string.

namespace marnav
{
namespace nmea
{

/// Returns the parse function of a particular sentence.
///
/// If an unknown sentence tag is specified, an exception is thrown.
///
/// @param[in] tag The tag of the sentence to get the parse function for.
/// @return The parse function of the specified sentence.
/// @exception std::invalid_argument The specified tag could not be found,
///   the argument cannot be processed.
static sentence::parse_function instantiate_sentence(const std::string & tag) throw(
	std::invalid_argument)
{
	using namespace std;

	using entry = std::pair<std::string, sentence::parse_function>;
	static const std::vector<entry> known_sentences
		= {{"AAM", aam::parse}, {"BOD", bod::parse}, {"DBK", dbk::parse}, {"DBT", dbt::parse},
			{"DPT", dpt::parse}, {"GGA", gga::parse}, {"GLL", gll::parse}, {"GSA", gsa::parse},
			{"GSV", gsv::parse}, {"HDG", hdg::parse}, {"HDM", hdm::parse}, {"MTW", mtw::parse},
			{"MWD", mwd::parse}, {"MWV", mwv::parse}, {"R00", r00::parse}, {"RMA", rma::parse},
			{"RMB", rmb::parse}, {"RMC", rmc::parse}, {"RSA", rsa::parse}, {"RTE", rte::parse},
			{"VHW", vhw::parse}, {"VLW", vlw::parse}, {"VTG", vtg::parse}, {"VWR", vwr::parse},
			{"VDM", vdm::parse}, {"VDO", vdo::parse}, {"WNC", wnc::parse}, {"WPL", wpl::parse},
			{"XDR", xdr::parse}, {"XTE", xte::parse}, {"ZDA", zda::parse}};

	auto const & i = std::find_if(begin(known_sentences), end(known_sentences),
		[tag](const entry & e) { return e.first == tag; });

	if (i == end(known_sentences))
		throw std::invalid_argument{"unknown sentence in instantiate_sentence: " + tag};

	return i->second;
}

/// Parses the string and returns the corresponding sentence.
///
/// @param[in] s The sentence to parse.
/// @return The object of the corresponding type.
/// @exception checksum_error Will be thrown if the checksum is wrong.
/// @exception std::invalid_argument Will be thrown if the specified string
///   is not a NMEA sentence (malformed) or the sentence is not known.
///
/// Example:
/// @code
///   auto s =
///   nmea::make_sentence("$GPRMC,201034,A,4702.4040,N,00818.3281,E,0.0,328.4,260807,0.6,E,A*17");
/// @endcode
std::unique_ptr<sentence> make_sentence(const std::string & s) throw(
	std::invalid_argument, checksum_error)
{
	using namespace std;

	// perform various checks

	if (s.empty())
		throw invalid_argument{"empty string in make_sentence"};

	if ((s[0] != sentence::START_TOKEN) && (s[0] != sentence::START_TOKEN_AIS))
		throw invalid_argument{"no start token in make_sentence"};

	auto const end_pos = s.find_first_of(sentence::END_TOKEN, 1);

	if (s.size() != end_pos + 3)
		throw invalid_argument{"invalid format in make_sentence"};

	const string::const_iterator end = begin(s) + end_pos;

	uint8_t checksum = 0x00;
	for_each(begin(s) + 1, end, [&checksum](char c) { checksum ^= c; });
	size_t pos = 0;
	const uint8_t expected_checksum = stoul(s.substr(end_pos + 1, 2), &pos, 16);
	if (checksum != expected_checksum)
		throw checksum_error{expected_checksum, checksum};

	if (end_pos < 7) // talker id (2), tag (3), first comma (1)
		throw invalid_argument{"malformed sentence in make_sentence"};

	// extract particular data
	const std::string tag = s.substr(3, 3);
	const std::string talker = s.substr(1, 2);

	// the additional separator is needed because the last entry can be empty,
	// therefore there is no separator for the last entry at the end. this additional
	// separator makes sure there is a separator for the regex to parse them correctly.
	const std::string data = s.substr(7, end_pos - 7) + ",";

	// extract fields from data
	std::regex field_regex{","};
	auto fields_begin = std::sregex_token_iterator{data.begin(), data.end(), field_regex, -1};
	auto fields_end = std::sregex_token_iterator();
	std::vector<std::string> fields{fields_begin, fields_end};

	return instantiate_sentence(tag)(talker, fields);
}
}
}
