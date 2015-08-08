#include "seatalk.hpp"

#include <algorithm>

#include <marnav/seatalk/message_00.hpp>
#include <marnav/seatalk/message_01.hpp>
#include <marnav/seatalk/message_05.hpp>
#include <marnav/seatalk/message_10.hpp>
#include <marnav/seatalk/message_11.hpp>
#include <marnav/seatalk/message_20.hpp>
#include <marnav/seatalk/message_21.hpp>
#include <marnav/seatalk/message_22.hpp>
#include <marnav/seatalk/message_23.hpp>
#include <marnav/seatalk/message_25.hpp>
#include <marnav/seatalk/message_27.hpp>

namespace marnav
{
namespace seatalk
{

static message::parse_function instantiate_message(message_id type) throw(std::invalid_argument)
{
	using entry = std::pair<message_id, message::parse_function>;
	static const std::vector<entry> known_messages = {
		{message_id::depth_below_transducer, message_00::parse},
		{message_id::equipment_id, message_01::parse},
		{message_id::engine_rpm_and_pitch, message_05::parse},
		{message_id::apparent_wind_angle, message_10::parse},
		{message_id::apparent_wind_speed, message_11::parse},
		{message_id::speed_through_water, message_20::parse},
		{message_id::trip_mileage, message_21::parse},
		{message_id::trip_mileage, message_22::parse},
		{message_id::total_mileage, message_23::parse},
		{message_id::total_and_trip_log, message_25::parse},
		{message_id::water_temperature_2, message_27::parse},
	};

	auto const & i = std::find_if(begin(known_messages), end(known_messages),
		[type](const entry & e) { return e.first == type; });

	if (i == end(known_messages))
		throw std::invalid_argument{"unknown message in instantiate_message: "
			+ std::to_string(static_cast<uint8_t>(type))};

	return i->second;
}

std::unique_ptr<message> make_message(const raw & data) throw(std::invalid_argument)
{
	if (data.size() < 1)
		throw std::invalid_argument{"raw data of insufficient size"};
	message_id type = static_cast<message_id>(data[0]);
	return instantiate_message(type)(data);
}

raw encode_message(const message & msg) throw(std::invalid_argument) { return msg.get_data(); }
}
}
