#include "vbw.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * vbw::TAG;

vbw::vbw()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

void vbw::set_water_speed(double l, double t, status s) noexcept
{
	water_speed_longitudinal = l;
	water_speed_transveral = t;
	water_speed_status = s;
}

void vbw::set_ground_speed(double l, double t, status s) noexcept
{
	ground_speed_longitudinal = l;
	ground_speed_transveral = t;
	ground_speed_status = s;
}

std::unique_ptr<sentence> vbw::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	if (fields.size() != 6)
		throw std::invalid_argument{"invalid number of fields in vbw::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<vbw>();
	result->set_talker(talker);
	vbw & detail = static_cast<vbw &>(*result);

	read(fields[0], detail.water_speed_longitudinal);
	read(fields[1], detail.water_speed_transveral);
	read(fields[2], detail.water_speed_status);
	read(fields[3], detail.ground_speed_longitudinal);
	read(fields[4], detail.ground_speed_transveral);
	read(fields[5], detail.water_speed_status);

	return result;
}

std::vector<std::string> vbw::get_data() const
{
	return {format(water_speed_longitudinal, 1), format(water_speed_transveral, 1),
		to_string(water_speed_status), format(ground_speed_longitudinal, 1),
		format(ground_speed_transveral, 1), to_string(ground_speed_status)};
}
}
}
