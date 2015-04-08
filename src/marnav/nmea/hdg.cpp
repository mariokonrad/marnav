#include "hdg.hpp"
#include "io.hpp"
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

hdg::hdg()
	: sentence(ID, "HDG", talker_id::magnetic_compass)
{
}

void hdg::set_magn_dev(double deg, char hem)
{
	check_hem(hem);
	magn_dev = deg;
	magn_dev_hem = hem;
}

void hdg::set_magn_var(double deg, char hem)
{
	check_hem(hem);
	magn_var = deg;
	magn_var_hem = hem;
}

void hdg::check_hem(char hem) throw(std::invalid_argument)
{
	if ((hem != direction::EAST) && (hem != direction::WEST))
		throw std::invalid_argument{"invalid hemisphere"};
}

std::unique_ptr<sentence> hdg::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 5)
		throw std::invalid_argument{"invalid number of fields in hdg::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<hdg>();
	result->set_talker(talker);
	hdg & detail = static_cast<hdg &>(*result);

	read(fields[0], detail.heading);
	read(fields[1], detail.magn_dev);
	read(fields[2], detail.magn_dev_hem);
	read(fields[3], detail.magn_var);
	read(fields[4], detail.magn_var_hem);

	return result;
}

std::vector<std::string> hdg::get_data() const
{
	return {to_string(heading), to_string(magn_dev), to_string(magn_dev_hem),
		to_string(magn_var), to_string(magn_var_hem)};
}
}
}
