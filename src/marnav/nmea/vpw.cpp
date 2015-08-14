#include "vpw.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * vpw::TAG;

vpw::vpw()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

void vpw::set_speed_knots(double t)
{
	speed_knots = t;
	speed_knots_unit = unit::velocity::KNOT;
}

void vpw::set_speed_mps(double t)
{
	speed_meters_per_second = t;
	speed_meters_per_second_unit = unit::velocity::MPS;
}

std::unique_ptr<sentence> vpw::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument, std::runtime_error)
{
	if (fields.size() != 4)
		throw std::invalid_argument{"invalid number of fields in vpw::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<vpw>();
	result->set_talker(talker);
	vpw & detail = static_cast<vpw &>(*result);

	read(fields[0], detail.speed_knots);
	read(fields[1], detail.speed_knots_unit);
	read(fields[2], detail.speed_meters_per_second);
	read(fields[3], detail.speed_meters_per_second_unit);

	return result;
}

std::vector<std::string> vpw::get_data() const
{
	return {to_string(speed_knots), to_string(speed_knots_unit),
		to_string(speed_meters_per_second), to_string(speed_meters_per_second_unit)};
}
}
}
