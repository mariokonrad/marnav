#ifndef __SEATALK__MESSAGE_20__HPP__
#define __SEATALK__MESSAGE_20__HPP__

#include "message.hpp"

namespace marnav
{
namespace seatalk
{

class message_20 : public message
{
public:
	constexpr static const message_id ID = message_id::speed_through_water;

	message_20();
	message_20(const message_20 &) = default;
	message_20 & operator=(const message_20 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data) throw(std::invalid_argument);

private:
	uint16_t speed; // speed in 1/10th of knots

public:
	uint16_t get_speed() const { return speed; }

	void set_speed(uint16_t t) { speed = t; }
};
}
}

#endif
