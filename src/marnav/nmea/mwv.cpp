#include "mwv.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * mwv::TAG;

mwv::mwv()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
{
}

void mwv::set_angle(double deg, reference ref)
{
	check_value(ref, {reference::TRUE, reference::RELATIVE}, "angle_ref");
	angle = deg;
	angle_ref = ref;
}

void mwv::set_speed(double speed, char unit)
{
	this->speed = speed;
	speed_unit = unit;
}

std::unique_ptr<sentence> mwv::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 5)
		throw std::invalid_argument{"invalid number of fields in mwv::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<mwv>();
	result->set_talker(talker);
	mwv & detail = static_cast<mwv &>(*result);

	read(fields[0], detail.angle);
	read(fields[1], detail.angle_ref);
	read(fields[2], detail.speed);
	read(fields[3], detail.speed_unit);
	read(fields[4], detail.data_valid);

	return result;
}

std::vector<std::string> mwv::get_data() const
{
	return {to_string(angle), to_string(angle_ref), to_string(speed), to_string(speed_unit),
		to_string(data_valid)};
}
}
}
