#include <marnav/nmea/dse.hpp>
#include "checks.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
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

std::string to_name(dse::query_flag value)
{
	switch (value) {
		case dse::query_flag::query:
			return "Query";
		case dse::query_flag::reply:
			return "Reply";
		case dse::query_flag::a:
			return "A";
	}
	throw std::invalid_argument{"invaild value for conversion of dse::query_flag"};
}

std::string to_name(dse::code_id value)
{
	switch (value) {
		case dse::code_id::enhanced_position_resolution:
			return "Enhanced Position Resolution";
		case dse::code_id::source_and_data_of_position:
			return "Source and Data of Position";
		case dse::code_id::current_speed_of_vessel:
			return "Current Speed of Vessel";
		case dse::code_id::current_course_of_vessel:
			return "Current Course of Vessel";
		case dse::code_id::additional_station_identification:
			return "Additional Station Identification";
		case dse::code_id::enhanced_geographic_area:
			return "Enhanced Geographic Area";
		case dse::code_id::number_of_persons_on_board:
			return "Number of Persons on Board";
	}
	throw std::invalid_argument{"invaild value for conversion of dse::code_id"};
}

constexpr sentence_id dse::ID;
constexpr const char * dse::TAG;

dse::dse()
	: sentence(ID, TAG, talker::communications_dsc)
{
}

dse::dse(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in dse"};

	read(*(first + 0), number_of_messages_);
	read(*(first + 1), sentence_number_);
	read(*(first + 2), flag_, flag_mapping);
	read(*(first + 3), address_);

	// TODO: read data set fields
}

utils::mmsi dse::get_mmsi() const
{
	return utils::mmsi{static_cast<utils::mmsi::value_type>(address_ / 10)};
}

void dse::set_mmsi(const utils::mmsi & t) noexcept
{
	address_ = t;
	address_ *= 10;
}

void dse::append_data_to(std::string & s) const
{
	append(s, to_string(number_of_messages_));
	append(s, to_string(sentence_number_));
	append(s, to_string(flag_));
	append(s, format(address_, 10));
	append(s, "");
	append(s, "");
}
}
}
