#include "message_51.hpp"

namespace marnav
{
namespace seatalk
{

message_51::message_51()
	: message(ID)
{
}

std::unique_ptr<message> message_51::parse(const raw & data)
{
	if (data.size() != 5)
		throw std::invalid_argument{"invalid number of bytes in message_51::parse"};
	if ((data[1] & 0x0f) != 0x02)
		throw std::invalid_argument{"invalid size specified in message"};

	std::unique_ptr<message> result = utils::make_unique<message_51>();
	message_51 & msg = static_cast<message_51 &>(*result);

	// 51  Z2  XX  YY  YY
	// raw  1   2   3   4

	const uint32_t degrees = data[2];
	uint32_t m = 0;
	m += data[3];
	m <<= 8;
	m += data[4];

	const uint32_t minutes = (m & 0x7fff) / 100;
	const uint32_t seconds = (((m & 0x7fff) % 100) * 60) / 100;
	const geo::longitude::hemisphere hemisphere
		= (m & 0x8000) ? geo::longitude::hemisphere::EAST : geo::longitude::hemisphere::WEST;

	msg.lon = geo::longitude{degrees, minutes, seconds, hemisphere};

	// deliberately ignored 'Z'

	return result;
}

raw message_51::get_data() const
{
	uint16_t m = 0;
	m += lon.minutes() * 100;
	m += (lon.seconds() * 100) / 60;
	if (lon.hem() == geo::longitude::hemisphere::EAST)
		m |= 0x8000;

	return raw{static_cast<uint8_t>(ID), 0x02, static_cast<uint8_t>(lon.degrees() & 0xff),
		static_cast<uint8_t>((m >> 8) & 0xff), static_cast<uint8_t>((m >> 0) & 0xff)};
}
}
}
