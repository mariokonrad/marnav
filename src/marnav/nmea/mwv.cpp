#include <marnav/nmea/mwv.hpp>
#include "checks.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id mwv::ID;
constexpr const char * mwv::TAG;

mwv::mwv()
	: sentence(ID, TAG, talker::integrated_instrumentation)
{
}

mwv::mwv(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in mwv"};

	read(*(first + 0), angle_);
	read(*(first + 1), angle_ref_);
	read(*(first + 2), speed_);
	read(*(first + 3), speed_unit_);
	read(*(first + 4), data_valid_);
}

void mwv::set_angle(double deg, reference ref)
{
	check_value(ref, {reference::TRUE, reference::RELATIVE}, "angle_ref");
	angle_ = deg;
	angle_ref_ = ref;
}

void mwv::set_speed(units::velocity speed, unit::velocity u) noexcept
{
	switch (u) {
		case unit::velocity::knot:
			set_speed(speed.get<units::knots>());
			break;
		case unit::velocity::kmh:
			set_speed(speed.get<units::kilometers_per_hour>());
			break;
		case unit::velocity::mps:
			set_speed(speed.get<units::meters_per_second>());
			break;
	}
}

void mwv::set_speed(units::knots speed) noexcept
{
	speed_ = speed.value();
	speed_unit_ = unit::velocity::knot;
}

void mwv::set_speed(units::kilometers_per_hour speed) noexcept
{
	speed_ = speed.value();
	speed_unit_ = unit::velocity::kmh;
}

void mwv::set_speed(units::meters_per_second speed) noexcept
{
	speed_ = speed.value();
	speed_unit_ = unit::velocity::mps;
}

std::optional<units::velocity> mwv::get_speed() const
{
	if (!speed_ || !speed_unit_)
		return {};

	switch (*speed_unit_) {
		case unit::velocity::knot:
			return {units::knots{*speed_}};
		case unit::velocity::kmh:
			return {units::kilometers_per_hour{*speed_}};
		case unit::velocity::mps:
			return {units::meters_per_second{*speed_}};
	}

	return {};
}

void mwv::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(angle_));
	append(s, to_string(angle_ref_));
	append(s, to_string(speed_));
	append(s, to_string(speed_unit_));
	append(s, to_string(data_valid_));
}
}
}
