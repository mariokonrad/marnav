#include "message_05.hpp"
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace ais
{
namespace
{
std::string trim_ais_string(const std::string & s) { return s.substr(0, s.find_first_of("@")); }
}

message_05::message_05()
	: message(ID)
	, callsign("@@@@@@@")
	, shipname("@@@@@@@@@@@@@@@@@@@@")
	, destination("@@@@@@@@@@@@@@@@@@@@")
{
}

/// @todo also handle message with length of 420 and 422 bits
std::unique_ptr<message> message_05::parse(const raw & bits)
{
	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_05::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_05>();
	message_05 & msg = static_cast<message_05 &>(*result);

	msg.read_data(bits);

	return result;
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
	get(bits, dte);
}

raw message_05::get_data() const
{
	raw bits{SIZE_BITS};

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

std::string message_05::get_callsign() const { return trim_ais_string(callsign); }

std::string message_05::get_shipname() const { return trim_ais_string(shipname); }

std::string message_05::get_destination() const { return trim_ais_string(destination); }

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
}
}
