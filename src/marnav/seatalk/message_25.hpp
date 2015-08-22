#ifndef __SEATALK__MESSAGE_25__HPP__
#define __SEATALK__MESSAGE_25__HPP__

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

	message_25();
	message_25(const message_25 &) = default;
	message_25 & operator=(const message_25 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data) throw(std::invalid_argument);

private:
	uint32_t total; // in 1/10th nautical miles
	uint32_t trip; // in 1/100th nautical miles

public:
	uint32_t get_total() const { return total; }
	uint32_t get_trip() const { return trip; }

	void set_total(uint32_t t) { total = t; }
	void set_trip(uint32_t t) { trip = t; }
};
}
}

#endif
