#include "mwv.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * mwv::TAG;

mwv::mwv()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

mwv::mwv(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in mwv"};

	read(*(first + 0), angle);
	read(*(first + 1), angle_ref);
	read(*(first + 2), speed);
	read(*(first + 3), speed_unit);
	read(*(first + 4), data_valid);
}

void mwv::set_angle(double deg, reference ref)
{
	check_value(ref, {reference::TRUE, reference::RELATIVE}, "angle_ref");
	angle = deg;
	angle_ref = ref;
}

void mwv::set_speed(double speed, unit::velocity u) noexcept
{
	this->speed = speed;
	speed_unit = u;
}

std::vector<std::string> mwv::get_data() const
{
	return {to_string(angle), to_string(angle_ref), to_string(speed), to_string(speed_unit),
		to_string(data_valid)};
}
}
}
