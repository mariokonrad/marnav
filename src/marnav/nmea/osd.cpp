#include <marnav/nmea/osd.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id osd::ID;
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

	read(*(first + 0), heading_);
	read(*(first + 1), data_valid_);
	read(*(first + 2), course_);
	read(*(first + 3), course_ref_);
	read(*(first + 4), speed_);
	read(*(first + 5), speed_unit_);
	read(*(first + 6), vessel_set_);
	read(*(first + 7), vessel_drift_);
	read(*(first + 8), vessel_drift_unit_);
}

void osd::set_course(double t) noexcept
{
	course_ = t;
	course_ref_ = reference::TRUE;
}

void osd::set_speed(double t, unit::velocity u) noexcept
{
	speed_ = t;
	speed_unit_ = u;
}

void osd::set_drift(double t, unit::velocity u) noexcept
{
	vessel_drift_ = t;
	vessel_drift_unit_ = u;
}

void osd::append_data_to(std::string & s) const
{
	append(s, to_string(heading_));
	append(s, to_string(data_valid_));
	append(s, to_string(course_));
	append(s, to_string(course_ref_));
	append(s, to_string(speed_));
	append(s, to_string(speed_unit_));
	append(s, to_string(vessel_set_));
	append(s, to_string(vessel_drift_));
	append(s, to_string(vessel_drift_unit_));
}
}
}
