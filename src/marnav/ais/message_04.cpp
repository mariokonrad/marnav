#include <marnav/ais/message_04.hpp>
#include <marnav/ais/angle.hpp>

namespace marnav::ais
{
constexpr message_id message_04::ID;
constexpr std::size_t message_04::SIZE_BITS;

constexpr uint32_t message_04::eta_month_not_available;
constexpr uint32_t message_04::eta_day_not_available;
constexpr uint32_t message_04::eta_hour_not_available;
constexpr uint32_t message_04::eta_minute_not_available;

message_04::message_04()
	: message_04(ID)
{
}

message_04::message_04(message_id id)
	: message(id)
{
}

message_04::message_04(const raw & bits)
	: message_04(ID)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_04"};
	read_data(bits);
}

void message_04::read_data(const raw & bits)
{
	get(bits, repeat_indicator_);
	get(bits, mmsi_);
	get(bits, year_);
	get(bits, month_);
	get(bits, day_);
	get(bits, hour_);
	get(bits, minute_);
	get(bits, second_);
	get(bits, position_accuracy_);
	get(bits, longitude_minutes_);
	get(bits, latitude_minutes_);
	get(bits, epfd_fix_);
	get(bits, raim_);
	get(bits, radio_status_);
}

raw message_04::get_data() const
{
	raw bits(SIZE_BITS);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator_);
	set(bits, mmsi_);
	set(bits, year_);
	set(bits, month_);
	set(bits, day_);
	set(bits, hour_);
	set(bits, minute_);
	set(bits, second_);
	set(bits, position_accuracy_);
	set(bits, longitude_minutes_);
	set(bits, latitude_minutes_);
	set(bits, epfd_fix_);
	set(bits, raim_);
	set(bits, radio_status_);

	return bits;
}

std::optional<geo::longitude> message_04::get_lon() const
{
	if (longitude_minutes_ == longitude_not_available)
		return std::make_optional<geo::longitude>();
	return to_geo_longitude(longitude_minutes_, longitude_minutes_.count, angle_scale::I4);
}

std::optional<geo::latitude> message_04::get_lat() const
{
	if (latitude_minutes_ == latitude_not_available)
		return std::make_optional<geo::latitude>();
	return to_geo_latitude(latitude_minutes_, latitude_minutes_.count, angle_scale::I4);
}

void message_04::set_lon(const std::optional<geo::longitude> & t)
{
	longitude_minutes_ = t
		? to_longitude_minutes(t.value(), longitude_minutes_.count, angle_scale::I4)
		: longitude_not_available;
}

void message_04::set_lat(const std::optional<geo::latitude> & t)
{
	latitude_minutes_ = t
		? to_latitude_minutes(t.value(), latitude_minutes_.count, angle_scale::I4)
		: latitude_not_available;
}
}
