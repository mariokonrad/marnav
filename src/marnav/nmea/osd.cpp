#include "osd.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * osd::TAG;

osd::osd()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
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

std::unique_ptr<sentence> osd::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	if (fields.size() != 9)
		throw std::invalid_argument{"invalid number of fields in osd::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<osd>();
	result->set_talker(talker);
	osd & detail = static_cast<osd &>(*result);

	read(fields[0], detail.heading);
	read(fields[1], detail.data_valid);
	read(fields[2], detail.course);
	read(fields[3], detail.course_ref);
	read(fields[4], detail.speed);
	read(fields[5], detail.speed_unit);
	read(fields[6], detail.vessel_set);
	read(fields[7], detail.vessel_drift);
	read(fields[8], detail.vessel_drift_unit);

	return result;
}

std::vector<std::string> osd::get_data() const
{
	return {to_string(heading), to_string(data_valid), to_string(course), to_string(course_ref),
		to_string(speed), to_string(speed_unit), to_string(vessel_set), to_string(vessel_drift),
		to_string(vessel_drift_unit)};
}
}
}

