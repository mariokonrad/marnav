#ifndef MARNAV_SEATALK_MESSAGE_21_HPP
#define MARNAV_SEATALK_MESSAGE_21_HPP

#include <marnav/seatalk/message.hpp>

namespace marnav::seatalk
{

/// @brief Trip Mileage
///
/// @code
/// 21 02 XX XX 0X
///
/// Trip Mileage: XXXXX/100 nautical miles
/// @endcode
///
class message_21 : public message
{
public:
	constexpr static const message_id ID = message_id::trip_mileage;
	constexpr static size_t SIZE = 5;

	message_21();
	message_21(const message_21 &) = default;
	message_21 & operator=(const message_21 &) = default;

	raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	uint32_t distance_{0}; // in 1/100th nautical miles

public:
	uint32_t get_distance() const noexcept { return distance_; }

	void set_distance(uint32_t t) noexcept { distance_ = t; }
};
}

#endif
