#ifndef __SEATALK__MESSAGE__HPP__
#define __SEATALK__MESSAGE__HPP__

#include <vector>
#include <functional>
#include <typeinfo>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace seatalk
{

constexpr const int MAX_MESSAGE_SIZE = 32;

/// Enumeration of all known SeaTalk message types.
///
/// Omitted: 0x81
///
enum class message_id : uint8_t {
	depth_below_transducer = 0x00,
	equipment_id = 0x01,
	engine_rpm_and_pitch = 0x05,
	apparent_wind_angle = 0x10,
	apparent_wind_speed = 0x11,
	speed_through_water = 0x20,
	trip_mileage = 0x21,
	total_mileage = 0x22,
	water_temperature_1 = 0x23,
	display_units_mileage_speed = 0x24,
	total_and_trip_log = 0x25,
	speed_through_water_2 = 0x26,
	water_temperature_2 = 0x27,
	set_lamp_intensity = 0x30,
	cancel_mob_condition = 0x36,
	codelock_data = 0x38,
	position_latitude = 0x50,
	position_longitude = 0x51,
	speed_over_ground = 0x52,
	magnetic_course = 0x53,
	gmt_time = 0x54,
	track_keystroke_on_gps = 0x55,
	date = 0x56,
	sat_info = 0x57,
	lat_lon = 0x58,
	countdown_timer = 0x59,
	e80_initialization = 0x61,
	display_unit_select_fathom = 0x65,
	wind_alarm = 0x66,
	alarm_ack = 0x68,
	equipment_id_2 = 0x6c,
	mob = 0x6e,
	st60_keystroke = 0x70,
	lamp_intensity_2 = 0x80, ///< @todo What is the difference to 0x30, seems the same
	target_waypoint_name = 0x82,
	course_computer = 0x83,
	heading_course_rudder = 0x84,
	navigation_waypoint_info = 0x85,
	keystroke = 0x86,
	response_level = 0x87,
	autopilot_parameter = 0x88,
	st40_compass_heading = 0x89
};

namespace unit
{
constexpr const char KNOT = 'N';
constexpr const char MPS = 'M'; // meters per second
}

using raw = std::vector<uint8_t>;

/// @brief Base class for all SeaTalk messages
///
class message
{
public:
	using parse_function = std::function<std::unique_ptr<message>(const raw &)>;

	virtual ~message() {}

	message_id type() const;
	virtual raw get_data() const = 0;

protected:
	message(message_id id);
	static void check_size(const raw & data, size_t size);

private:
	message_id message_type;
};

/// Casts the specified message to the message given by the template parameter.
/// The object converted only if it is valid and of the correct type. It is not
/// possible to cast a message into a completley different one.
///
/// @param[in] s The message object to convert.
/// @retval nullptr The specified message is invalid.
/// @return The converted message . The specified message is now invalid.
/// @exception std::bad_cast The specified message has the wrong ID.
template <class T> T * message_cast(message * s)
{
	if (!s)
		return nullptr;
	if (s->type() != T::ID)
		throw std::bad_cast{};

	return static_cast<T *>(s);
}

/// const variant.
///
/// @see message_cast(message * s)
template <class T> const T * message_cast(const message * s)
{
	if (!s)
		return nullptr;
	if (s->type() != T::ID)
		throw std::bad_cast{};

	return static_cast<const T *>(s);
}

/// std::unique_ptr variant.
///
/// @note This cast does not change ownership of the specified pointer.
///  The return value is a naked pointer.
///
/// @see message_cast(message * s)
template <class T> T * message_cast(std::unique_ptr<message> & s)
{
	if (!s)
		return nullptr;
	if (s->type() != T::ID)
		throw std::bad_cast{};

	return static_cast<T *>(s.get());
}

/// const std::unique_ptr variant.
///
/// @note This cast does not change ownership of the specified pointer.
///  The return value is a naked pointer.
///
/// @see message_cast(message * s)
template <class T> const T * message_cast(const std::unique_ptr<message> & s)
{
	if (!s)
		return nullptr;
	if (s->type() != T::ID)
		throw std::bad_cast{};

	return static_cast<const T *>(s.get());
}

/// reference variant
///
/// @see message_cast(message * s)
template <class T> T & message_cast(message & s)
{
	if (s.type() != T::ID)
		throw std::bad_cast{};
	return *static_cast<T *>(&s);
}

/// const reference variant
///
/// @see message_cast(message * s)
template <class T> const T & message_cast(const message & s)
{
	if (s.type() != T::ID)
		throw std::bad_cast{};
	return *static_cast<const T *>(&s);
}
}
}

#endif
