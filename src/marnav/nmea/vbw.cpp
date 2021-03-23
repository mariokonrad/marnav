#include <marnav/nmea/vbw.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id vbw::ID;
constexpr const char * vbw::TAG;

vbw::vbw()
	: sentence(ID, TAG, talker::integrated_instrumentation)
{
}

vbw::vbw(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in vbw"};

	read(*(first + 0), water_speed_longitudinal_);
	read(*(first + 1), water_speed_transveral_);
	read(*(first + 2), water_speed_status_);
	read(*(first + 3), ground_speed_longitudinal_);
	read(*(first + 4), ground_speed_transveral_);
	read(*(first + 5), ground_speed_status_);
}

void vbw::set_water_speed(units::velocity l, units::velocity t, status s)
{
	water_speed_longitudinal_ = l.get<units::knots>();
	water_speed_transveral_ = t.get<units::knots>();
	water_speed_status_ = s;
}

void vbw::set_ground_speed(units::velocity l, units::velocity t, status s)
{
	ground_speed_longitudinal_ = l.get<units::knots>();
	ground_speed_transveral_ = t.get<units::knots>();
	ground_speed_status_ = s;
}

utils::optional<units::velocity> vbw::get_water_speed_longitudinal() const
{
	if (!water_speed_longitudinal_)
		return {};
	return {*water_speed_longitudinal_};
}

utils::optional<units::velocity> vbw::get_water_speed_transveral() const
{
	if (!water_speed_transveral_)
		return {};
	return {*water_speed_transveral_};
}

utils::optional<units::velocity> vbw::get_ground_speed_longitudinal() const
{
	if (!ground_speed_longitudinal_)
		return {};
	return {*ground_speed_longitudinal_};
}

utils::optional<units::velocity> vbw::get_ground_speed_transveral() const
{
	if (!ground_speed_transveral_)
		return {};
	return {*ground_speed_transveral_};
}

void vbw::append_data_to(std::string & s) const
{
	append(s, format(water_speed_longitudinal_, 1));
	append(s, format(water_speed_transveral_, 1));
	append(s, to_string(water_speed_status_));
	append(s, format(ground_speed_longitudinal_, 1));
	append(s, format(ground_speed_transveral_, 1));
	append(s, to_string(ground_speed_status_));
}
}
}
