#include <marnav/ais/message_21.hpp>
#include <marnav/ais/angle.hpp>
#include <algorithm>

namespace marnav::ais
{
constexpr message_id message_21::ID;
constexpr std::size_t message_21::SIZE_BITS_MIN;
constexpr std::size_t message_21::SIZE_BITS_MAX;

message_21::message_21()
	: message(ID)
	, name_("@@@@@@@@@@@@@@@@@@@@")
{
}

message_21::message_21(const raw & bits)
	: message(ID)
	, name_("@@@@@@@@@@@@@@@@@@@@")
{
	if ((bits.size() < SIZE_BITS_MIN) || (bits.size() > SIZE_BITS_MAX))
		throw std::invalid_argument{"invalid number of bits in message_21"};
	read_data(bits);
}

void message_21::read_data(const raw & bits)
{
	get(bits, repeat_indicator_);
	get(bits, mmsi_);
	get(bits, aid_type_);
	get(bits, name_);
	get(bits, position_accuracy_);
	get(bits, longitude_minutes_);
	get(bits, latitude_minutes_);
	get(bits, to_bow_);
	get(bits, to_stern_);
	get(bits, to_port_);
	get(bits, to_starboard_);
	get(bits, epfd_fix_);
	get(bits, utc_second_);
	get(bits, off_position_);
	get(bits, regional_);
	get(bits, raim_);
	get(bits, virtual_aid_flag_);
	get(bits, assigned_);

	auto rest = bits.size() - SIZE_BITS_MIN;
	if (rest > 0) {
		rest = std::min(rest, SIZE_BITS_MAX - SIZE_BITS_MIN);
		name_extension_ = read_string(bits, 272, rest / 6);
	}
}

raw message_21::get_data() const
{
	raw bits(SIZE_BITS_MIN);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator_);
	set(bits, mmsi_);
	set(bits, aid_type_);
	set(bits, name_);
	set(bits, position_accuracy_);
	set(bits, longitude_minutes_);
	set(bits, latitude_minutes_);
	set(bits, to_bow_);
	set(bits, to_stern_);
	set(bits, to_port_);
	set(bits, to_starboard_);
	set(bits, epfd_fix_);
	set(bits, utc_second_);
	set(bits, off_position_);
	set(bits, regional_);
	set(bits, raim_);
	set(bits, virtual_aid_flag_);
	set(bits, assigned_);

	if (name_extension_.size() > 0) {
		// compute number of bits, must be on a 8-bit boundary
		auto size = name_extension_.size() * 6;
		if ((size % 8) != 0)
			size += 8 - (size % 8);

		if (size <= SIZE_BITS_MAX - SIZE_BITS_MIN) {
			// append a temporary bitset to the real one
			raw t(size);
			write_string(t, 0, name_extension_.size(), name_extension_);
			bits.append(t);
		}
	}

	return bits;
}

std::string message_21::get_name() const
{
	return trim_ais_string(name_);
}

void message_21::set_name(const std::string & t)
{
	if (t.size() > 20) {
		name_ = t.substr(0, 20);
	} else {
		name_ = t;
	}
}

std::string message_21::get_name_extension() const
{
	return trim_ais_string(name_extension_);
}

void message_21::set_name_extension(const std::string & t)
{
	// 88 bits with 6-bit encoding are 14 characters
	if (t.size() > 14) {
		name_extension_ = t.substr(0, 14);
	} else {
		name_extension_ = t;
	}
}

std::optional<geo::longitude> message_21::get_lon() const
{
	if (longitude_minutes_ == longitude_not_available)
		return std::make_optional<geo::longitude>();
	return to_geo_longitude(longitude_minutes_, longitude_minutes_.count, angle_scale::I4);
}

std::optional<geo::latitude> message_21::get_lat() const
{
	if (latitude_minutes_ == latitude_not_available)
		return std::make_optional<geo::latitude>();
	return to_geo_latitude(latitude_minutes_, latitude_minutes_.count, angle_scale::I4);
}

void message_21::set_lon_unavailable()
{
	longitude_minutes_ = longitude_not_available;
}

void message_21::set_lat_unavailable()
{
	latitude_minutes_ = latitude_not_available;
}

void message_21::set_lon(const geo::longitude & t)
{
	longitude_minutes_ = to_longitude_minutes(t, longitude_minutes_.count, angle_scale::I4);
}

void message_21::set_lat(const geo::latitude & t)
{
	latitude_minutes_ = to_latitude_minutes(t, latitude_minutes_.count, angle_scale::I4);
}

vessel_dimension message_21::get_vessel_dimension() const noexcept
{
	return {to_bow_, to_stern_, to_port_, to_starboard_};
}

void message_21::set_vessel_dimension(const vessel_dimension & t)
{
	to_bow_ = t.get_raw_to_bow();
	to_stern_ = t.get_raw_to_stern();
	to_port_ = t.get_raw_to_port();
	to_starboard_ = t.get_raw_to_starboard();
}
}
