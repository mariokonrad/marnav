#include <marnav/ais/message_05.hpp>
#include <iostream>

namespace marnav
{
namespace ais
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
	, callsign("@@@@@@@")
	, shipname("@@@@@@@@@@@@@@@@@@@@")
	, destination("@@@@@@@@@@@@@@@@@@@@")
{
}

message_05::message_05(const raw & bits)
	: message(ID)
	, callsign("@@@@@@@")
	, shipname("@@@@@@@@@@@@@@@@@@@@")
	, destination("@@@@@@@@@@@@@@@@@@@@")
{
	if ((bits.size() < SIZE_BITS_MIN) || (bits.size() > SIZE_BITS))
		throw std::invalid_argument{"invalid number of bits in message_05"};
	read_data(bits);
}

void message_05::read_data(const raw & bits)
{
	get(bits, repeat_indicator);
	get(bits, mmsi);
	get(bits, ais_version);
	get(bits, imo_number);
	get(bits, callsign);
	get(bits, shipname);
	get(bits, shiptype);
	get(bits, to_bow);
	get(bits, to_stern);
	get(bits, to_port);
	get(bits, to_starboard);
	get(bits, epfd_fix);
	get(bits, eta_month);
	get(bits, eta_day);
	get(bits, eta_hour);
	get(bits, eta_minute);
	get(bits, draught);
	get(bits, destination);

	if (bits.size() > SIZE_BITS_MIN)
		get(bits, dte);
}

raw message_05::get_data() const
{
	raw bits(SIZE_BITS);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator);
	set(bits, mmsi);
	set(bits, ais_version);
	set(bits, imo_number);
	set(bits, callsign);
	set(bits, shipname);
	set(bits, shiptype);
	set(bits, to_bow);
	set(bits, to_stern);
	set(bits, to_port);
	set(bits, to_starboard);
	set(bits, epfd_fix);
	set(bits, eta_month);
	set(bits, eta_day);
	set(bits, eta_hour);
	set(bits, eta_minute);
	set(bits, draught);
	set(bits, destination);
	set(bits, dte);

	return bits;
}

std::string message_05::get_callsign() const
{
	return trim_ais_string(callsign);
}

std::string message_05::get_shipname() const
{
	return trim_ais_string(shipname);
}

std::string message_05::get_destination() const
{
	return trim_ais_string(destination);
}

void message_05::set_callsign(const std::string & t)
{
	if (t.size() > 7) {
		callsign = t.substr(0, 7);
	} else {
		callsign = t;
	}
}

void message_05::set_shipname(const std::string & t)
{
	if (t.size() > 20) {
		shipname = t.substr(0, 20);
	} else {
		shipname = t;
	}
}

void message_05::set_destination(const std::string & t)
{
	if (t.size() > 20) {
		destination = t.substr(0, 20);
	} else {
		destination = t;
	}
}

units::meters message_05::get_to_bow() const noexcept
{
	return units::meters{to_bow.as<units::meters::value_type>()};
}

units::meters message_05::get_to_stern() const noexcept
{
	return units::meters{to_stern.as<units::meters::value_type>()};
}

units::meters message_05::get_to_port() const noexcept
{
	return units::meters{to_port.as<units::meters::value_type>()};
}

units::meters message_05::get_to_starboard() const noexcept
{
	return units::meters{to_starboard.as<units::meters::value_type>()};
}

void message_05::set_to_bow(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"length less than zero"};
	to_bow = round(t.get<units::meters>()).value();
}

void message_05::set_to_stern(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"length less than zero"};
	to_stern = round(t.get<units::meters>()).value();
}

void message_05::set_to_port(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"length less than zero"};
	to_port = round(t.get<units::meters>()).value();
}

void message_05::set_to_starboard(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"length less than zero"};
	to_starboard = round(t.get<units::meters>()).value();
}

units::meters message_05::get_draught() const noexcept
{
	return units::meters{0.1 * draught.as<units::meters::value_type>()};
}

void message_05::set_draught(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"length less than zero"};
	draught = ceil((10.0 * t).get<units::meters>()).value();
}
}
}
