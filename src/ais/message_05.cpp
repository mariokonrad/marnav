#include "message_05.hpp"
#include <utils/unique.hpp>
#include <cstdio>

namespace ais
{
message_05::message_05()
	: message(ID)
	, repeat_indicator(0)
	, mmsi(0)
	, ais_version(0)
	, imo_number(0)
	, callsign("@@@@@@@")
	, shipname("@@@@@@@@@@@@@@@@@@@@")
	, shiptype(ship_type::not_available)
	, to_bow(0)
	, to_stern(0)
	, to_port(0)
	, to_starboard(0)
	, eta_month(eta_month_not_available)
	, eta_day(eta_day_not_available)
	, eta_hour(eta_hour_not_available)
	, eta_minute(eta_minute_not_available)
	, draught(0)
	, destination("@@@@@@@@@@@@@@@@@@@@")
	, dte(true)
{
}

std::unique_ptr<message> message_05::parse(const raw& bits) throw(std::invalid_argument)
{
	// TODO: also handle message with length of 420 and 422 bits

	if (bits.size() != SIZE_BITS)
		throw std::invalid_argument{"invalid number of bits in message_05::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_05>();
	message_05& msg = static_cast<message_05&>(*result);

	msg.read_data(bits);

	return result;
}

std::string message_05::read_string(const raw& bits, raw::size_type ofs,
									raw::size_type count_sixbits) const
{
	std::string s;
	s.reserve(count_sixbits);

	// TODO: consider to hide characters after '@'

	for (raw::size_type i = 0; i < count_sixbits; ++i) {
		uint8_t sixbit = 0;
		bits.get(sixbit, ofs + i * 6, 6);
		s += decode_sixbit_ascii(sixbit);
	}

	return s;
}

void message_05::write_string(raw& bits, raw::size_type ofs, raw::size_type count_sixbits,
					  const std::string& s) const
{
	for (raw::size_type i = 0; i < count_sixbits; ++i) {
		uint8_t value;
		if (i < s.size()) {
			value = encode_sixbit_ascii(s[i]);
		} else {
			value = encode_sixbit_ascii('@');
		}
		bits.set(value, ofs + i * 6, 6);
	}
}

void message_05::read_data(const raw& bits)
{
	bits.get(repeat_indicator, 6, 2);
	bits.get(mmsi, 8, 30);
	bits.get(ais_version, 38, 2);
	bits.get(imo_number, 40, 30);
	callsign = read_string(bits, 70, 7);
	shipname = read_string(bits, 112, 20);
	bits.get(shiptype, 232, 8);
	bits.get(to_bow, 240, 9);
	bits.get(to_stern, 249, 9);
	bits.get(to_port, 258, 9);
	bits.get(to_starboard, 264, 9);
	bits.get(epfd_fix, 270, 4);
	bits.get(eta_month, 274, 4);
	bits.get(eta_day, 278, 5);
	bits.get(eta_hour, 283, 5);
	bits.get(eta_minute, 288, 6);
	bits.get(draught, 294, 8);
	destination = read_string(bits, 302, 20);
	bits.get(dte, 422, 1);
	// 423 spare
}

raw message_05::get_data() const
{
	raw bits{SIZE_BITS};

	bits.set(type(), 0, 6);
	bits.set(repeat_indicator, 6, 2);
	bits.set(mmsi, 8, 30);
	bits.set(ais_version, 38, 2);
	bits.set(imo_number, 40, 30);
	write_string(bits, 70, 7, callsign);
	write_string(bits, 112, 20, shipname);
	bits.set(shiptype, 232, 8);
	bits.set(to_bow, 240, 9);
	bits.set(to_stern, 249, 9);
	bits.set(to_port, 258, 9);
	bits.set(to_starboard, 264, 9);
	bits.set(epfd_fix, 270, 4);
	bits.set(eta_month, 274, 4);
	bits.set(eta_day, 278, 5);
	bits.set(eta_hour, 283, 5);
	bits.set(eta_minute, 288, 6);
	bits.set(draught, 294, 8);
	write_string(bits, 302, 20, destination);
	bits.set(dte, 422, 1);
	// 423 spare

	return bits;
}

void message_05::set_callsign(const std::string& t)
{
	if (t.size() > 7) {
		callsign = t.substr(0, 7);
	} else {
		callsign = t;
	}
}

void message_05::set_shipname(const std::string& t)
{
	if (t.size() > 20) {
		shipname = t.substr(0, 20);
	} else {
		shipname = t;
	}
}

void message_05::set_destination(const std::string& t)
{
	if (t.size() > 20) {
		destination = t.substr(0, 20);
	} else {
		destination = t;
	}
}
}
