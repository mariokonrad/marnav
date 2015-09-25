#include "tfi.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

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
	for (auto & t : sensors)
		t = state::no_answer;
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
	return sensors[index];
}

void tfi::set_sensor(int index, state t)
{
	check_index(index);
	sensors[index] = t;
}

std::unique_ptr<sentence> tfi::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	if (fields.size() != 3)
		throw std::invalid_argument{"invalid number of fields in tfi::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<tfi>();
	result->set_talker(talker);
	tfi & detail = static_cast<tfi &>(*result);

	for (size_t i = 0; i < num_sensors; ++i)
		read(fields[i], detail.sensors[i], state_mapping);

	return result;
}

std::vector<std::string> tfi::get_data() const
{
	std::vector<std::string> result;
	result.reserve(num_sensors);
	for (auto const & t : sensors)
		result.push_back(to_string(t));
	return result;
}
}
}
