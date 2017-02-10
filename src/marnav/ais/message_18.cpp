#include "message_18.hpp"
#include <cmath>
#include <marnav/ais/angle.hpp>

namespace marnav
{
namespace ais
{
message_18::message_18()
	: message_18(ID)
{
}

message_18::message_18(message_id id)
	: message(id)
{
}

message_18::message_18(const raw & bits)
	: message_18(ID)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_18"};
	read_data(bits);
}

void message_18::read_data(const raw & bits)
{
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, sog);
	get(bits, position_accuracy);
	get(bits, longitude_minutes);
	get(bits, latitude_minutes);
	get(bits, cog);
	get(bits, hdg);
	get(bits, timestamp);
	get(bits, cs_unit);
	get(bits, display_flag);
	get(bits, dsc_flag);
	get(bits, band_flag);
	get(bits, message_22_flag);
	get(bits, assigned);
	get(bits, raim);
	get(bits, radio_status);
}

raw message_18::get_data() const
{
	raw bits{SIZE_BITS};

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, sog);
	set(bits, position_accuracy);
	set(bits, longitude_minutes);
	set(bits, latitude_minutes);
	set(bits, cog);
	set(bits, hdg);
	set(bits, timestamp);
	set(bits, cs_unit);
	set(bits, display_flag);
	set(bits, dsc_flag);
	set(bits, band_flag);
	set(bits, message_22_flag);
	set(bits, assigned);
	set(bits, raim);
	set(bits, radio_status);

	return bits;
}

utils::optional<geo::longitude> message_18::get_longitude() const
{
	if (longitude_minutes == longitude_not_available)
		return utils::make_optional<geo::longitude>();
	return to_geo_longitude(longitude_minutes, longitude_minutes.count, angle_scale::I4);
}

utils::optional<geo::latitude> message_18::get_latitude() const
{
	if (latitude_minutes == latitude_not_available)
		return utils::make_optional<geo::latitude>();
	return to_geo_latitude(latitude_minutes, latitude_minutes.count, angle_scale::I4);
}

void message_18::set_longitude(const utils::optional<geo::longitude> & t)
{
	longitude_minutes = t
		? to_longitude_minutes(t.value(), longitude_minutes.count, angle_scale::I4)
		: longitude_not_available;
}

void message_18::set_latitude(const utils::optional<geo::latitude> & t)
{
	latitude_minutes = t
		? to_latitude_minutes(t.value(), latitude_minutes.count, angle_scale::I4)
		: latitude_not_available;
}

/// Returns speed in knots.
utils::optional<double> message_18::get_sog() const noexcept
{
	if (sog == sog_not_available)
		return {};
	return 0.1 * sog;
}

void message_18::set_sog(utils::optional<double> t) noexcept
{
	sog = !t ? sog_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

/// Returns course over ground in degrees true north.
utils::optional<double> message_18::get_cog() const noexcept
{
	if (cog == cog_not_available)
		return {};
	return 0.1 * cog;
}

void message_18::set_cog(utils::optional<double> t) noexcept
{
	cog = !t ? cog_not_available : static_cast<uint32_t>(std::round(*t / 0.1));
}

/// Returns heading in degrees.
utils::optional<uint32_t> message_18::get_hdg() const noexcept
{
	if (hdg == hdg_not_available)
		return {};
	return {hdg};
}

void message_18::set_hdg(utils::optional<uint32_t> t) noexcept
{
	hdg = !t ? hdg_not_available : *t;
}
}
}
