#include <marnav/ais/message_05.hpp>
#include <marnav/math/floatingpoint.hpp>
#include <iostream>

namespace marnav::ais
{
constexpr message_id message_05::ID;
constexpr std::size_t message_05::SIZE_BITS;
constexpr std::size_t message_05::SIZE_BITS_MIN;

constexpr uint32_t message_05::eta_month_not_available;
constexpr uint32_t message_05::eta_day_not_available;
constexpr uint32_t message_05::eta_hour_not_available;
constexpr uint32_t message_05::eta_minute_not_available;

message_05::message_05()
	: message(ID)
	, callsign_("@@@@@@@")
	, shipname_("@@@@@@@@@@@@@@@@@@@@")
	, destination_("@@@@@@@@@@@@@@@@@@@@")
{
}

message_05::message_05(const raw & bits)
	: message(ID)
	, callsign_("@@@@@@@")
	, shipname_("@@@@@@@@@@@@@@@@@@@@")
	, destination_("@@@@@@@@@@@@@@@@@@@@")
{
	if ((bits.size() < SIZE_BITS_MIN) || (bits.size() > SIZE_BITS))
		throw std::invalid_argument{"invalid number of bits in message_05"};
	read_data(bits);
}

void message_05::read_data(const raw & bits)
{
	get(bits, repeat_indicator_);
	get(bits, mmsi_);
	get(bits, ais_version_);
	get(bits, imo_number_);
	get(bits, callsign_);
	get(bits, shipname_);
	get(bits, shiptype_);
	get(bits, to_bow_);
	get(bits, to_stern_);
	get(bits, to_port_);
	get(bits, to_starboard_);
	get(bits, epfd_fix_);
	get(bits, eta_month_);
	get(bits, eta_day_);
	get(bits, eta_hour_);
	get(bits, eta_minute_);
	get(bits, draught_);
	get(bits, destination_);

	if (bits.size() > SIZE_BITS_MIN)
		get(bits, dte_);
}

raw message_05::get_data() const
{
	raw bits(SIZE_BITS);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator_);
	set(bits, mmsi_);
	set(bits, ais_version_);
	set(bits, imo_number_);
	set(bits, callsign_);
	set(bits, shipname_);
	set(bits, shiptype_);
	set(bits, to_bow_);
	set(bits, to_stern_);
	set(bits, to_port_);
	set(bits, to_starboard_);
	set(bits, epfd_fix_);
	set(bits, eta_month_);
	set(bits, eta_day_);
	set(bits, eta_hour_);
	set(bits, eta_minute_);
	set(bits, draught_);
	set(bits, destination_);
	set(bits, dte_);

	return bits;
}

std::string message_05::get_callsign() const
{
	return trim_ais_string(callsign_);
}

std::string message_05::get_shipname() const
{
	return trim_ais_string(shipname_);
}

std::string message_05::get_destination() const
{
	return trim_ais_string(destination_);
}

void message_05::set_callsign(const std::string & t)
{
	if (t.size() > 7) {
		callsign_ = t.substr(0, 7);
	} else {
		callsign_ = t;
	}
}

void message_05::set_shipname(const std::string & t)
{
	if (t.size() > 20) {
		shipname_ = t.substr(0, 20);
	} else {
		shipname_ = t;
	}
}

void message_05::set_destination(const std::string & t)
{
	if (t.size() > 20) {
		destination_ = t.substr(0, 20);
	} else {
		destination_ = t;
	}
}

vessel_dimension message_05::get_vessel_dimension() const noexcept
{
	return {to_bow_, to_stern_, to_port_, to_starboard_};
}

void message_05::set_vessel_dimension(const vessel_dimension & t)
{
	to_bow_ = t.get_raw_to_bow();
	to_stern_ = t.get_raw_to_stern();
	to_port_ = t.get_raw_to_port();
	to_starboard_ = t.get_raw_to_starboard();
}

units::meters message_05::get_draught() const noexcept
{
	return units::meters{0.1 * draught_.as<units::meters::value_type>()};
}

void message_05::set_draught(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"length less than zero"};
	draught_ = math::float_cast<uint32_t>(ceil((10.0 * t).get<units::meters>()).value());
}
}
