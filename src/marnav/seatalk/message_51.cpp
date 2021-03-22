#include <marnav/seatalk/message_51.hpp>
#include <marnav/math/floatingpoint.hpp>

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
	check_size(data, SIZE);

	std::unique_ptr<message> result = std::make_unique<message_51>();
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
		= (m & 0x8000) ? geo::longitude::hemisphere::east : geo::longitude::hemisphere::west;

	msg.lon_ = geo::longitude{degrees, minutes, seconds, hemisphere};

	// deliberately ignored 'Z'

	return result;
}

raw message_51::get_data() const
{
	uint16_t m = 0;
	m += lon_.minutes() * 100;
	m += math::float_cast<decltype(m)>((lon_.seconds() * 100) / 60);
	if (lon_.hem() == geo::longitude::hemisphere::east)
		m |= 0x8000;

	return raw{static_cast<uint8_t>(ID), 0x02, static_cast<uint8_t>(lon_.degrees() & 0xff),
		static_cast<uint8_t>((m >> 8) & 0xff), static_cast<uint8_t>((m >> 0) & 0xff)};
}
}
}
