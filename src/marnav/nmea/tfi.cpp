#include "tfi.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
namespace
{
/// Converts data read from the NMEA string to the corresponding
/// enumerator.
///
/// @param[in] value The numerical value to convert.
/// @return The corresponding enumerator.
/// @exception std::invalid_argument The specified value to convert is unknown.
///
static tfi::state state_mapping(typename std::underlying_type<tfi::state>::type value)
{
	switch (value) {
		case 0:
			return tfi::state::off;
		case 1:
			return tfi::state::on;
		case 2:
			return tfi::state::no_answer;
	}
	throw std::invalid_argument{"invaild value for conversion to tfi::state"};
}
}

std::string to_string(tfi::state value)
{
	switch (value) {
		case tfi::state::off:
			return "0";
		case tfi::state::on:
			return "1";
		case tfi::state::no_answer:
			return "2";
	}
	throw std::invalid_argument{"invaild value for conversion of tfi::state"};
}

constexpr const char * tfi::TAG;

tfi::tfi()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
	for (auto & t : sensors_)
		t = state::no_answer;
}

tfi::tfi(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 3)
		throw std::invalid_argument{"invalid number of fields in tfi"};

	for (size_t i = 0; i < num_sensors; ++i)
		read(*(first + i), sensors_[i], state_mapping);
}

void tfi::check_index(int index) const
{
	if ((index < 0) || (index >= num_sensors)) {
		throw std::out_of_range{"sensor index out of range"};
	}
}

tfi::state tfi::get_sensor(int index) const
{
	check_index(index);
	return sensors_[index];
}

void tfi::set_sensor(int index, state t)
{
	check_index(index);
	sensors_[index] = t;
}

void tfi::append_data_to(std::string & s) const
{
	for (auto const & t : sensors_)
		append(s, to_string(t));
}
}
}
