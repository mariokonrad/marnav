#include <marnav/seatalk/message_58.hpp>
#include <limits>
#include <cmath>

namespace marnav
{
namespace seatalk
{

message_58::message_58()
	: message(ID)
{
}

std::unique_ptr<message> message_58::parse(const raw & data)
{
	check_size(data, SIZE);

	std::unique_ptr<message> result = utils::make_unique<message_58>();
	message_58 & msg = static_cast<message_58 &>(*result);

	//  58 Z5 LA XX YY LO QQ RR
	// raw  1  2  3  4  5  6  7

	const double lat_minutes = (data[3] * 256 + data[4]) / 1000.0;
	const double lon_minutes = (data[6] * 256 + data[7]) / 1000.0;

	double lat = data[2] + (lat_minutes * 100.0 / 60.0) / 100.0;
	double lon = data[5] + (lon_minutes * 100.0 / 60.0) / 100.0;

	if (((data[1] & 0x10) == 0x10) && (std::abs(lat) > std::numeric_limits<double>::epsilon()))
		lat = -lat;
	if (((data[1] & 0x20) == 0x00) && (std::abs(lon) > std::numeric_limits<double>::epsilon()))
		lon = -lon;

	msg.pos_ = geo::position{geo::latitude{lat}, geo::longitude{lon}};

	return result;
}

raw message_58::get_data() const
{
	uint8_t z = 0;

	const auto lat = pos_.lat();
	const uint8_t la = lat.degrees();
	const uint32_t la_min = std::floor(std::fmod(lat.get(), 1.0) * 60.0 / 100.0 * 100 * 1000.0);
	if (lat.hem() == geo::latitude::hemisphere::south)
		z |= 0x10;

	const auto lon = pos_.lon();
	const uint8_t lo = lon.degrees();
	const uint32_t lo_min
		= std::floor(std::fmod(lon.get(), 1.0) * 60.0 / 100.0 * 100.0 * 1000.0);
	if (lon.hem() == geo::longitude::hemisphere::east)
		z |= 0x20;

	return raw{static_cast<uint8_t>(ID), static_cast<uint8_t>(0x05 | z), la,
		static_cast<uint8_t>(la_min / 256), static_cast<uint8_t>(la_min % 256), lo,
		static_cast<uint8_t>(lo_min / 256), static_cast<uint8_t>(lo_min % 256)};
}
}
}
