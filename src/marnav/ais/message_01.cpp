#include <marnav/ais/message_01.hpp>
#include <marnav/ais/angle.hpp>
#include <cmath>

namespace marnav::ais
{
constexpr message_id message_01::ID;
constexpr std::size_t message_01::SIZE_BITS;

message_01::message_01()
	: message_01(ID)
{
}

message_01::message_01(message_id id)
	: message(id)
{
}

message_01::message_01(const raw & bits)
	: message_01(ID)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in ais/message_01"};
	read_data(bits);
}

std::optional<geo::longitude> message_01::get_lon() const
{
	if (longitude_minutes_ == longitude_not_available)
		return std::make_optional<geo::longitude>();
	return to_geo_longitude(longitude_minutes_, longitude_minutes_.count, angle_scale::I4);
}

std::optional<geo::latitude> message_01::get_lat() const
{
	if (latitude_minutes_ == latitude_not_available)
		return std::make_optional<geo::latitude>();
	return to_geo_latitude(latitude_minutes_, latitude_minutes_.count, angle_scale::I4);
}

void message_01::set_lon_unavailable()
{
	longitude_minutes_ = longitude_not_available;
}

void message_01::set_lat_unavailable()
{
	latitude_minutes_ = latitude_not_available;
}

void message_01::set_lon(const geo::longitude & t)
{
	longitude_minutes_ = to_longitude_minutes(t, longitude_minutes_.count, angle_scale::I4);
}

void message_01::set_lat(const geo::latitude & t)
{
	latitude_minutes_ = to_latitude_minutes(t, latitude_minutes_.count, angle_scale::I4);
}

std::optional<units::knots> message_01::get_sog() const noexcept
{
	// ignores special value of 1022 = 102.2 knots or faster

	if (sog_ == sog_not_available)
		return {};
	return units::knots{0.1 * sog_};
}

void message_01::set_sog_unavailable()
{
	sog_ = sog_not_available;
}

void message_01::set_sog(units::velocity t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"SOG less than zero"};

	const auto v = t.get<units::knots>();
	sog_ = std::min(sog_max, static_cast<uint32_t>(round(v * 10).value()));
}

/// Returns course over ground in degrees true north.
std::optional<double> message_01::get_cog() const noexcept
{
	if (cog_ == cog_not_available)
		return {};
	return 0.1 * cog_;
}

void message_01::set_cog(std::optional<double> t) noexcept
{
	cog_ = !t ? cog_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

/// Returns heading in degrees.
std::optional<uint32_t> message_01::get_hdg() const noexcept
{
	if (hdg_ == hdg_not_available)
		return {};
	return {hdg_};
}

void message_01::set_hdg(std::optional<uint32_t> t) noexcept
{
	hdg_ = !t ? hdg_not_available : *t;
}

rate_of_turn message_01::get_rot() const noexcept
{
	return rate_of_turn(rot_);
}

void message_01::set_rot(rate_of_turn t) noexcept
{
	rot_ = t.raw();
}

void message_01::read_data(const raw & bits)
{
	get(bits, repeat_indicator_);
	get(bits, mmsi_);
	get(bits, nav_status_);
	get(bits, rot_);
	get(bits, sog_);
	get(bits, position_accuracy_);
	get(bits, longitude_minutes_);
	get(bits, latitude_minutes_);
	get(bits, cog_);
	get(bits, hdg_);
	get(bits, timestamp_);
	get(bits, maneuver_indicator_);
	get(bits, raim_);
	get(bits, radio_status_);
}

raw message_01::get_data() const
{
	raw bits(SIZE_BITS);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator_);
	set(bits, mmsi_);
	set(bits, nav_status_);
	set(bits, rot_);
	set(bits, sog_);
	set(bits, position_accuracy_);
	set(bits, longitude_minutes_);
	set(bits, latitude_minutes_);
	set(bits, cog_);
	set(bits, hdg_);
	set(bits, timestamp_);
	set(bits, maneuver_indicator_);
	set(bits, raim_);
	set(bits, radio_status_);

	return bits;
}
}
