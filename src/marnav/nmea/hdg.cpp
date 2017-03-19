#include "hdg.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * hdg::TAG;

hdg::hdg()
	: sentence(ID, TAG, talker_id::magnetic_compass)
{
}

hdg::hdg(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in hdg"};

	read(*(first + 0), heading);
	read(*(first + 1), magn_dev);
	read(*(first + 2), magn_dev_hem);
	read(*(first + 3), magn_var);
	read(*(first + 4), magn_var_hem);
}

void hdg::set_magn_dev(double deg, direction hem)
{
	check_value(hem, {direction::east, direction::west}, "magn_dev hemisphere");
	magn_dev = deg;
	magn_dev_hem = hem;
}

void hdg::set_magn_var(double deg, direction hem)
{
	check_value(hem, {direction::east, direction::west}, "magn_var hemisphere");
	magn_var = deg;
	magn_var_hem = hem;
}

void hdg::append_data_to(std::string & s) const
{
	append(s, to_string(heading));
	append(s, to_string(magn_dev));
	append(s, to_string(magn_dev_hem));
	append(s, to_string(magn_var));
	append(s, to_string(magn_var_hem));
}
}
}
