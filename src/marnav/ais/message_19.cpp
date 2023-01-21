#include <marnav/ais/message_19.hpp>
#include <marnav/ais/angle.hpp>

namespace marnav::ais
{
constexpr message_id message_19::ID;
constexpr std::size_t message_19::SIZE_BITS;

message_19::message_19()
	: message_19(ID)
{
}

message_19::message_19(message_id id)
	: message(id)
	, shipname_("@@@@@@@@@@@@@@@@@@@@")
{
}

message_19::message_19(const raw & bits)
	: message_19(ID)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_19"};
	read_data(bits);
}

void message_19::read_data(const raw & bits)
{
	get(bits, repeat_indicator_);
	get(bits, mmsi_);
	get(bits, sog_);
	get(bits, position_accuracy_);
	get(bits, longitude_minutes_);
	get(bits, latitude_minutes_);
	get(bits, cog_);
	get(bits, hdg_);
	get(bits, timestamp_);
	get(bits, shipname_);
	get(bits, shiptype_);
	get(bits, to_bow_);
	get(bits, to_stern_);
	get(bits, to_port_);
	get(bits, to_starboard_);
	get(bits, epfd_fix_);
	get(bits, raim_);
	get(bits, dte_);
	get(bits, assigned_);
}

raw message_19::get_data() const
{
	raw bits(SIZE_BITS);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator_);
	set(bits, mmsi_);
	set(bits, sog_);
	set(bits, position_accuracy_);
	set(bits, longitude_minutes_);
	set(bits, latitude_minutes_);
	set(bits, cog_);
	set(bits, hdg_);
	set(bits, timestamp_);
	set(bits, shipname_);
	set(bits, shiptype_);
	set(bits, to_bow_);
	set(bits, to_stern_);
	set(bits, to_port_);
	set(bits, to_starboard_);
	set(bits, epfd_fix_);
	set(bits, raim_);
	set(bits, dte_);
	set(bits, assigned_);

	return bits;
}

std::optional<geo::longitude> message_19::get_lon() const
{
	if (longitude_minutes_ == longitude_not_available)
		return std::make_optional<geo::longitude>();
	return to_geo_longitude(longitude_minutes_, longitude_minutes_.count, angle_scale::I4);
}

std::optional<geo::latitude> message_19::get_lat() const
{
	if (latitude_minutes_ == latitude_not_available)
		return std::make_optional<geo::latitude>();
	return to_geo_latitude(latitude_minutes_, latitude_minutes_.count, angle_scale::I4);
}

void message_19::set_lon_unavailable()
{
	longitude_minutes_ = longitude_not_available;
}

void message_19::set_lat_unavailable()
{
	latitude_minutes_ = latitude_not_available;
}

void message_19::set_lon(const geo::longitude & t)
{
	longitude_minutes_ = to_longitude_minutes(t, longitude_minutes_.count, angle_scale::I4);
}

void message_19::set_lat(const geo::latitude & t)
{
	latitude_minutes_ = to_latitude_minutes(t, latitude_minutes_.count, angle_scale::I4);
}

void message_19::set_shipname(const std::string & t)
{
	if (t.size() > 20) {
		shipname_ = t.substr(0, 20);
	} else {
		shipname_ = t;
	}
}

std::optional<units::knots> message_19::get_sog() const noexcept
{
	// ignores special value of 1022 = 102.2 knots or faster

	if (sog_ == sog_not_available)
		return {};
	return units::knots{0.1 * sog_};
}

void message_19::set_sog_unavailable()
{
	sog_ = sog_not_available;
}

void message_19::set_sog(units::velocity t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"SOG less than zero"};

	const auto v = t.get<units::knots>();
	sog_ = std::min(sog_max, static_cast<uint32_t>(round(v * 10).value()));
}

vessel_dimension message_19::get_vessel_dimension() const noexcept
{
	return {to_bow_, to_stern_, to_port_, to_starboard_};
}

void message_19::set_vessel_dimension(const vessel_dimension & t)
{
	to_bow_ = t.get_raw_to_bow();
	to_stern_ = t.get_raw_to_stern();
	to_port_ = t.get_raw_to_port();
	to_starboard_ = t.get_raw_to_starboard();
}
}
