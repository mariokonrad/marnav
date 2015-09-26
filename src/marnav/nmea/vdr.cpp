#include "vdr.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * vdr::TAG;

vdr::vdr()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

void vdr::set_degrees_true(double t) noexcept
{
	degrees_true = t;
	degrees_true_ref = reference::TRUE;
}

void vdr::set_degrees_mag(double t) noexcept
{
	degrees_mag = t;
	degrees_mag_ref = reference::MAGNETIC;
}

void vdr::set_speed(double t) noexcept
{
	speed = t;
	speed_unit = unit::velocity::knot;
}

std::unique_ptr<sentence> vdr::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	if (fields.size() != 6)
		throw std::invalid_argument{"invalid number of fields in vdr::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<vdr>();
	result->set_talker(talker);
	vdr & detail = static_cast<vdr &>(*result);

	read(fields[0], detail.degrees_true);
	read(fields[1], detail.degrees_true_ref);
	read(fields[2], detail.degrees_mag);
	read(fields[3], detail.degrees_mag_ref);
	read(fields[4], detail.speed);
	read(fields[5], detail.speed_unit);

	return result;
}

std::vector<std::string> vdr::get_data() const
{
	return {to_string(degrees_true), to_string(degrees_true_ref), to_string(degrees_mag),
		to_string(degrees_mag_ref), to_string(speed), to_string(speed_unit)};
}
}
}
