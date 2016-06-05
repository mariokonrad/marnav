#include "vbw.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(vbw)

constexpr const char * vbw::TAG;

vbw::vbw()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

vbw::vbw(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in vbw"};

	read(*(first + 0), water_speed_longitudinal);
	read(*(first + 1), water_speed_transveral);
	read(*(first + 2), water_speed_status);
	read(*(first + 3), ground_speed_longitudinal);
	read(*(first + 4), ground_speed_transveral);
	read(*(first + 5), water_speed_status);
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

std::vector<std::string> vbw::get_data() const
{
	return {format(water_speed_longitudinal, 1), format(water_speed_transveral, 1),
		to_string(water_speed_status), format(ground_speed_longitudinal, 1),
		format(ground_speed_transveral, 1), to_string(ground_speed_status)};
}
}
}
