#include <marnav/nmea/vpw.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id vpw::ID;
constexpr const char * vpw::TAG;

vpw::vpw()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

vpw::vpw(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 4)
		throw std::invalid_argument{"invalid number of fields in vpw"};

	read(*(first + 0), speed_knots_);
	read(*(first + 1), speed_knots_unit_);
	read(*(first + 2), speed_meters_per_second_);
	read(*(first + 3), speed_meters_per_second_unit_);
}

void vpw::set_speed_knots(double t) noexcept
{
	speed_knots_ = t;
	speed_knots_unit_ = unit::velocity::knot;
}

void vpw::set_speed_mps(double t) noexcept
{
	speed_meters_per_second_ = t;
	speed_meters_per_second_unit_ = unit::velocity::mps;
}

void vpw::append_data_to(std::string & s) const
{
	append(s, to_string(speed_knots_));
	append(s, to_string(speed_knots_unit_));
	append(s, to_string(speed_meters_per_second_));
	append(s, to_string(speed_meters_per_second_unit_));
}
}
}
