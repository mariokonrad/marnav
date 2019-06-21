#ifndef MARNAV__SEATALK__MESSAGE_22__HPP
#define MARNAV__SEATALK__MESSAGE_22__HPP

#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace seatalk
{

/// @brief Total Mileage
///
/// @code
/// 22 02 XX XX 00
///
/// Total Mileage: XXXX/10 nautical miles
/// @endcode
///
class message_22 : public message
{
public:
	constexpr static const message_id ID = message_id::total_mileage;
	constexpr static size_t SIZE = 5;

	message_22();
	message_22(const message_22 &) = default;
	message_22 & operator=(const message_22 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	uint32_t distance_; // in 1/10th nautical miles

public:
	uint32_t get_distance() const noexcept { return distance_; }

	void set_distance(uint32_t t) noexcept { distance_ = t; }
};
}
}

#endif
