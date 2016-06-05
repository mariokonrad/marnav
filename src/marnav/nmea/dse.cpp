#include "dse.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(dse)

namespace
{
static dse::query_flag flag_mapping(typename std::underlying_type<dse::query_flag>::type value)
{
	switch (value) {
		case 'Q':
			return dse::query_flag::query;
		case 'R':
			return dse::query_flag::reply;
		case 'A':
			return dse::query_flag::a;
	}
	throw std::invalid_argument{"invaild value for conversion to dse::query_flag"};
}

static dse::code_id code_mapping(typename std::underlying_type<dse::code_id>::type value)
{
	switch (value) {
		case 0:
			return dse::code_id::enhanced_position_resolution;
		case 1:
			return dse::code_id::source_and_data_of_position;
		case 2:
			return dse::code_id::current_speed_of_vessel;
		case 3:
			return dse::code_id::current_course_of_vessel;
		case 4:
			return dse::code_id::additional_station_identification;
		case 5:
			return dse::code_id::enhanced_geographic_area;
		case 6:
			return dse::code_id::number_of_persons_on_board;
	}
	throw std::invalid_argument{"invaild value for conversion to dse::code_id"};
}
}

std::string to_string(dse::query_flag value)
{
	switch (value) {
		case dse::query_flag::query:
			return "Q";
		case dse::query_flag::reply:
			return "R";
		case dse::query_flag::a:
			return "A";
	}
	throw std::invalid_argument{"invaild value for conversion of dse::query_flag"};
}

std::string to_string(dse::code_id value)
{
	switch (value) {
		case dse::code_id::enhanced_position_resolution:
			return "0";
		case dse::code_id::source_and_data_of_position:
			return "1";
		case dse::code_id::current_speed_of_vessel:
			return "2";
		case dse::code_id::current_course_of_vessel:
			return "3";
		case dse::code_id::additional_station_identification:
			return "4";
		case dse::code_id::enhanced_geographic_area:
			return "5";
		case dse::code_id::number_of_persons_on_board:
			return "6";
	}
	throw std::invalid_argument{"invaild value for conversion of dse::code_id"};
}

constexpr const char * dse::TAG;

dse::dse()
	: sentence(ID, TAG, talker_id::communications_dsc)
{
}

dse::dse(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in dse"};

	read(*(first + 0), number_of_messages);
	read(*(first + 1), sentence_number);
	read(*(first + 2), flag, flag_mapping);
	read(*(first + 3), address);

	// TODO: read data set fields
}

utils::mmsi dse::get_mmsi() const
{
	return utils::mmsi{static_cast<utils::mmsi::value_type>(address / 10)};
}

void dse::set_mmsi(const utils::mmsi & t) noexcept
{
	address = t;
	address *= 10;
}

std::vector<std::string> dse::get_data() const
{
	return {to_string(number_of_messages), to_string(sentence_number), to_string(flag),
		format(address, 10), "", ""};
}
}
}
