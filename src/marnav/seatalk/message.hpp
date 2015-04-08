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
	using parse_function = std::function<std::unique_ptr<message>(const raw &)>;

	message_id type() const;
	virtual raw get_data() const = 0;

protected:
	message(message_id id);

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
template <class T> T * message_cast(message * s) throw(std::bad_cast)
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
template <class T> const T * message_cast(const message * s) throw(std::bad_cast)
{
	if (!s)
		return nullptr;
	if (s->type() != T::ID)
		throw std::bad_cast{};

	return static_cast<const T *>(s);
}

/// std::unique_ptr variant.
///
/// @see message_cast(message * s)
template <class T> T * message_cast(std::unique_ptr<message> & s) throw(std::bad_cast)
{
	if (!s)
		return nullptr;
	if (s->type() != T::ID)
		throw std::bad_cast{};

	return static_cast<T *>(s.get());
}

/// const std::unique_ptr variant.
///
/// @see message_cast(message * s)
template <class T> const T * message_cast(const std::unique_ptr<message> & s) throw(std::bad_cast)
{
	if (!s)
		return nullptr;
	if (s->type() != T::ID)
		throw std::bad_cast{};

	return static_cast<const T *>(s.get());
}
}
}

#endif
