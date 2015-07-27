#include "mwd.hpp"
#include "io.hpp"
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * mwd::TAG;

mwd::mwd()
	: sentence(ID, TAG, talker_id::weather_instruments)
{
}

void mwd::set_direction_true(double t)
{
	direction_true = t;
	direction_true_ref = reference::TRUE;
}

void mwd::set_direction_mag(double t)
{
	direction_mag = t;
	direction_mag_ref = reference::MAGNETIC;
}

void mwd::set_speed_knots(double t)
{
	speed_kn = t;
	speed_kn_unit = unit::KNOT;
}

void mwd::set_speed_mps(double t)
{
	speed_ms = t;
	speed_ms_unit = unit::MPS;
}

std::unique_ptr<sentence> mwd::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 8)
		throw std::invalid_argument{"invalid number of fields in mwd::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<mwd>();
	result->set_talker(talker);
	mwd & detail = static_cast<mwd &>(*result);

	read(fields[0], detail.direction_true);
	read(fields[1], detail.direction_true_ref);
	read(fields[2], detail.direction_mag);
	read(fields[3], detail.direction_mag_ref);
	read(fields[4], detail.speed_kn);
	read(fields[5], detail.speed_kn_unit);
	read(fields[6], detail.speed_ms);
	read(fields[7], detail.speed_ms_unit);

	return result;
}

std::vector<std::string> mwd::get_data() const
{
	return {format(direction_true, 1), to_string(direction_true_ref), format(direction_mag, 1),
		to_string(direction_mag_ref), format(speed_kn, 1), to_string(speed_kn_unit),
		format(speed_ms, 1), to_string(speed_ms_unit)};
}
}
}
