#include "osd.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * osd::TAG;

osd::osd()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

osd::osd(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 9)
		throw std::invalid_argument{"invalid number of fields in osd"};

	read(*(first + 0), heading);
	read(*(first + 1), data_valid);
	read(*(first + 2), course);
	read(*(first + 3), course_ref);
	read(*(first + 4), speed);
	read(*(first + 5), speed_unit);
	read(*(first + 6), vessel_set);
	read(*(first + 7), vessel_drift);
	read(*(first + 8), vessel_drift_unit);
}

void osd::set_course(double t) noexcept
{
	course = t;
	course_ref = reference::TRUE;
}

void osd::set_speed(double t, unit::velocity u) noexcept
{
	speed = t;
	speed_unit = u;
}

void osd::set_drift(double t, unit::velocity u) noexcept
{
	vessel_drift = t;
	vessel_drift_unit = u;
}

void osd::append_data_to(std::string & s) const
{
	append(s, to_string(heading));
	append(s, to_string(data_valid));
	append(s, to_string(course));
	append(s, to_string(course_ref));
	append(s, to_string(speed));
	append(s, to_string(speed_unit));
	append(s, to_string(vessel_set));
	append(s, to_string(vessel_drift));
	append(s, to_string(vessel_drift_unit));
}
}
}
