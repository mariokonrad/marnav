#include "seatalk.hpp"
#include "message_00.hpp"
#include "message_01.hpp"
#include "message_10.hpp"
#include "message_11.hpp"
#include "message_20.hpp"
#include "message_21.hpp"
#include <algorithm>

namespace seatalk
{

static message::parse_function instantiate_message(message_id type) throw(std::invalid_argument)
{
	using entry = std::pair<message_id, message::parse_function>;
	static const std::vector<entry> known_messages = {
		{message_id::depth_below_transducer, message_00::parse},
		{message_id::equipment_id, message_01::parse},
		{message_id::apparent_wind_angle, message_10::parse},
		{message_id::apparent_wind_speed, message_11::parse},
		{message_id::speed_through_water, message_20::parse},
		{message_id::trip_mileage, message_21::parse},
	};

	auto const& i = std::find_if(begin(known_messages), end(known_messages),
								 [type](const entry& e) { return e.first == type; });

	if (i == end(known_messages))
		throw std::invalid_argument{"unknown message in instantiate_message: "
									+ std::to_string(static_cast<uint8_t>(type))};

	return i->second;
}

std::unique_ptr<message> make_message(const raw& data) throw(std::invalid_argument)
{
	if (data.size() < 1)
		throw std::invalid_argument{"raw data of insufficient size"};
	message_id type = static_cast<message_id>(data[0]);
	return instantiate_message(type)(data);
}

raw encode_message(const message& msg) throw(std::invalid_argument)
{
	return msg.get_data();
}
}
