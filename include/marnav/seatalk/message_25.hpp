#ifndef MARNAV__SEATALK__MESSAGE_25__HPP
#define MARNAV__SEATALK__MESSAGE_25__HPP

#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace seatalk
{

/// @brief Total & Trip Log
///
/// @code
/// 25 Z4 XX YY UU VV AW
///    total= (XX+YY*256+Z* 4096)/ 10 [max=104857.5] nautical miles
///    trip = (UU+VV*256+W*65536)/100 [max=10485.75] nautical miles
/// @endcode
///
class message_25 : public message
{
public:
	constexpr static const message_id ID = message_id::total_and_trip_log;
	constexpr static size_t SIZE = 7;

	message_25();
	message_25(const message_25 &) = default;
	message_25 & operator=(const message_25 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	uint32_t total_; // in 1/10th nautical miles
	uint32_t trip_; // in 1/100th nautical miles

public:
	uint32_t get_total() const noexcept { return total_; }
	uint32_t get_trip() const noexcept { return trip_; }

	void set_total(uint32_t t) noexcept { total_ = t; }
	void set_trip(uint32_t t) noexcept { trip_ = t; }
};
}
}

#endif
