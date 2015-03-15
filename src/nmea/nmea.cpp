#include "nmea.hpp"
#include "angle.hpp"
#include "time.hpp"
#include "date.hpp"
#include "sentence.hpp"
#include "dbt.hpp"
#include "dpt.hpp"
#include "gga.hpp"
#include "gll.hpp"
#include "gsa.hpp"
#include "gsv.hpp"
#include "hdg.hpp"
#include "mtw.hpp"
#include "mwv.hpp"
#include "rmb.hpp"
#include "rmc.hpp"
#include "rte.hpp"
#include "vtg.hpp"
#include "unique.hpp"
#include <algorithm>
#include <regex>

namespace nmea
{

static sentence::parse_function
instantiate_sentence(const std::string& tag) throw(std::invalid_argument)
{
	using namespace std;

	using entry = std::pair<std::string, sentence::parse_function>;
	static const std::vector<entry> known_sentences = {
		{"DBT", dbt::parse},
		{"DPT", dpt::parse},
		{"GGA", gga::parse},
		{"GLL", gll::parse},
		{"GSA", gsa::parse},
		{"GSV", gsv::parse},
		{"HDG", hdg::parse},
		{"MTW", mtw::parse},
		{"MWV", mwv::parse},
		{"RMB", rmb::parse},
		{"RMC", rmc::parse},
		{"RTE", rte::parse},
		{"VTG", vtg::parse},
	};

	auto const& i = std::find_if(begin(known_sentences), end(known_sentences),
								 [tag](const entry& e) { return e.first == tag; });

	if (i == end(known_sentences))
		throw std::invalid_argument{"unknown sentence in instantiate_sentence: " + tag};

	return i->second;
}

std::unique_ptr<sentence> make_sentence(const std::string& s) throw(std::invalid_argument,
																	checksum_error)
{
	using namespace std;

	// perform various checks

	if (s.empty())
		throw invalid_argument{"empty string in make_sentence"};

	// TODO: support AIVDM

	if (s[0] != sentence::START_TOKEN)
		throw invalid_argument{"no start token in make_sentence"};

	auto const end_pos = s.find_first_of(sentence::END_TOKEN, 1);

	if (s.size() != end_pos + 3)
		throw invalid_argument{"invalid format in make_sentence"};

	const string::const_iterator end = begin(s) + end_pos;

	uint8_t checksum = 0x00;
	for_each(begin(s) + 1, end, [&checksum](char c) { checksum ^= c; });
	size_t pos = 0;
	if (checksum != stoul(s.substr(end_pos + 1, 2), &pos, 16))
		throw checksum_error{};

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
