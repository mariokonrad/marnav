#include <marnav/nmea/hdg.hpp>
#include "checks.hpp"
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id hdg::ID;
constexpr const char * hdg::TAG;

hdg::hdg()
	: sentence(ID, TAG, talker::magnetic_compass)
{
}

hdg::hdg(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in hdg"};

	read(*(first + 0), heading_);
	read(*(first + 1), magn_dev_);
	read(*(first + 2), magn_dev_hem_);
	read(*(first + 3), magn_var_);
	read(*(first + 4), magn_var_hem_);
}

void hdg::set_magn_dev(double deg, direction hem)
{
	check_value(hem, {direction::east, direction::west}, "magn_dev hemisphere");
	magn_dev_ = deg;
	magn_dev_hem_ = hem;
}

void hdg::set_magn_var(double deg, direction hem)
{
	check_value(hem, {direction::east, direction::west}, "magn_var hemisphere");
	magn_var_ = deg;
	magn_var_hem_ = hem;
}

void hdg::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(heading_));
	append(s, to_string(magn_dev_));
	append(s, to_string(magn_dev_hem_));
	append(s, to_string(magn_var_));
	append(s, to_string(magn_var_hem_));
}
}
}
