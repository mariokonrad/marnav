#include "message_21.hpp"
#include <marnav/ais/angle.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace ais
{

message_21::message_21()
	: message(ID)
	, repeat_indicator(0)
	, mmsi(0)
	, aid_type(aid_type_id::unspecified)
	, position_accuracy(false)
	, longitude_minutes(0)
	, latitude_minutes(0)
	, to_bow(0)
	, to_stern(0)
	, to_port(0)
	, to_starboard(0)
	, epfd_fix()
	, utc_second(0)
	, off_position(off_position_indicator::off_position)
	, regional(0)
	, raim(false)
	, virtual_aid_flag(virtual_aid::virtual_aid)
	, assigned(false)
{
}

std::unique_ptr<message> message_21::parse(const raw & bits) throw(std::invalid_argument)
{
	if ((bits.size() < SIZE_BITS_MIN) || (bits.size() > SIZE_BITS_MAX))
		throw std::invalid_argument{"invalid number of bits in message_21::parse"};

	std::unique_ptr<message> result = utils::make_unique<message_21>();
	message_21 & msg = static_cast<message_21 &>(*result);

	msg.read_data(bits);

	return result;
}

void message_21::read_data(const raw & bits)
{
	bits.get(repeat_indicator, 6, 2);
	bits.get(mmsi, 8, 30);

	// TODO: implementation
}

raw message_21::get_data() const
{
	// TODO: implementation

	raw bits{SIZE_BITS_MIN};

	bits.set(type(), 0, 6);
	bits.set(mmsi, 8, 30);

	return bits;
}

void message_21::set_name(const std::string & t)
{
	if (t.size() > 20) {
		name = t.substr(0, 20);
	} else {
		name = t;
	}
}

void message_21::set_name_extension(const std::string & t)
{
	// 88 bits with 6-bit encoding are 14 characters
	if (t.size() > 14) {
		name = t.substr(0, 14);
	} else {
		name = t;
	}
}

geo::longitude message_21::get_longitude() const
{
	return to_geo_longitude(longitude_minutes);
}

geo::latitude message_21::get_latitude() const
{
	return to_geo_latitude(latitude_minutes);
}

void message_21::set_longitude(const geo::longitude & t)
{
	longitude_minutes = to_longitude_minutes(t);
}

void message_21::set_latitude(const geo::latitude & t)
{
	latitude_minutes = to_latitude_minutes(t);
}

}
}
