#ifndef __SEATALK__MESSAGE__HPP__
#define __SEATALK__MESSAGE__HPP__

#include <vector>
#include <functional>
#include <utils/unique.hpp>

namespace seatalk
{

enum class message_id : uint8_t {
	depth_below_transducer = 0x00,
	equipment_id = 0x01,
	apparent_wind_angle = 0x10,
	apparent_wind_speed = 0x11,
	speed_through_water = 0x20,
	trip_mileage = 0x21,
	total_mileage = 0x22,
	water_temperature_1 = 0x23,
	total_and_trip_log = 0x25,
	water_temperature_2 = 0x27,
};

namespace unit
{
	constexpr const char KNOT = 'N';
	constexpr const char MPS = 'M'; // meters per second
}

using raw = std::vector<uint8_t>;

class message
{
public:
	using parse_function = std::function<std::unique_ptr<message>(const raw&)>;

	message_id type() const;
	virtual raw get_data() const = 0;

protected:
	message(message_id id);

private:
	message_id message_type;
};

template <class T> std::unique_ptr<T> message_cast(std::unique_ptr<message>& s)
{
	if (!s)
		return nullptr;
	if (s->type() != T::ID)
		return nullptr;

	return std::unique_ptr<T>{static_cast<T*>(s.release())};
}

}

#endif
