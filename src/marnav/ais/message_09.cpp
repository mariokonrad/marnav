#include <marnav/ais/message_09.hpp>
#include <marnav/ais/angle.hpp>

namespace marnav::ais
{
constexpr message_id message_09::ID;
constexpr std::size_t message_09::SIZE_BITS;

constexpr uint32_t message_09::altitude_not_available;
constexpr uint32_t message_09::altitude_max;

message_09::message_09()
	: message(ID)
{
}

message_09::message_09(const raw & bits)
	: message(ID)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_09"};
	read_data(bits);
}

void message_09::read_data(const raw & bits)
{
	get(bits, repeat_indicator_);
	get(bits, mmsi_);
	get(bits, altitude_);
	get(bits, speed_);
	get(bits, position_accuracy_);
	get(bits, longitude_minutes_);
	get(bits, latitude_minutes_);
	get(bits, course_);
	get(bits, utc_second_);
	get(bits, reserved_);
	get(bits, dte_);
	get(bits, assigned_);
	get(bits, raim_);
	get(bits, radio_status_);
}

raw message_09::get_data() const
{
	raw bits(SIZE_BITS);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator_);
	set(bits, mmsi_);
	set(bits, altitude_);
	set(bits, speed_);
	set(bits, position_accuracy_);
	set(bits, longitude_minutes_);
	set(bits, latitude_minutes_);
	set(bits, course_);
	set(bits, utc_second_);
	set(bits, reserved_);
	set(bits, dte_);
	set(bits, assigned_);
	set(bits, raim_);
	set(bits, radio_status_);

	return bits;
}

std::optional<geo::longitude> message_09::get_lon() const
{
	if (longitude_minutes_ == longitude_not_available)
		return std::make_optional<geo::longitude>();
	return to_geo_longitude(longitude_minutes_, longitude_minutes_.count, angle_scale::I4);
}

std::optional<geo::latitude> message_09::get_lat() const
{
	if (latitude_minutes_ == latitude_not_available)
		return std::make_optional<geo::latitude>();
	return to_geo_latitude(latitude_minutes_, latitude_minutes_.count, angle_scale::I4);
}

void message_09::set_lon_unavailable()
{
	longitude_minutes_ = longitude_not_available;
}

void message_09::set_lat_unavailable()
{
	latitude_minutes_ = latitude_not_available;
}

void message_09::set_lon(const geo::longitude & t)
{
	longitude_minutes_ = to_longitude_minutes(t, longitude_minutes_.count, angle_scale::I4);
}

void message_09::set_lat(const geo::latitude & t)
{
	latitude_minutes_ = to_latitude_minutes(t, latitude_minutes_.count, angle_scale::I4);
}

std::optional<units::meters> message_09::get_altitude() const noexcept
{
	// ignores special value is in meter 4094 = 4094 meters or higher

	if (speed_ == altitude_not_available)
		return {};
	return units::meters{altitude_.as<units::meters::value_type>()};
}

void message_09::set_altitude_unavailable()
{
	altitude_ = altitude_not_available;
}

void message_09::set_altitude(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"altitude less than zero"};

	const auto m = t.get<units::meters>();
	altitude_ = std::min(altitude_max, static_cast<uint32_t>(round(m).value()));
}

std::optional<units::knots> message_09::get_speed() const noexcept
{
	// ignores special value of 1022 = 102.2 knots or faster

	if (speed_ == sog_not_available)
		return {};
	return units::knots{speed_.as<units::knots::value_type>()};
}

void message_09::set_speed_unavailable()
{
	speed_ = sog_not_available;
}

void message_09::set_speed(units::velocity t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"SOG less than zero"};

	const auto v = t.get<units::knots>();
	speed_ = std::min(sog_max, static_cast<uint32_t>(round(v).value()));
}
}
