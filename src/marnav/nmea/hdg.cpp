#include "hdg.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * hdg::TAG;

hdg::hdg()
	: sentence(ID, TAG, talker_id::magnetic_compass)
{
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

std::unique_ptr<sentence> hdg::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in hdg::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<hdg>();
	result->set_talker(talker);
	hdg & detail = static_cast<hdg &>(*result);

	read(*(first + 0), detail.heading);
	read(*(first + 1), detail.magn_dev);
	read(*(first + 2), detail.magn_dev_hem);
	read(*(first + 3), detail.magn_var);
	read(*(first + 4), detail.magn_var_hem);

	return result;
}

std::vector<std::string> hdg::get_data() const
{
	return {to_string(heading), to_string(magn_dev), to_string(magn_dev_hem),
		to_string(magn_var), to_string(magn_var_hem)};
}
}
}
