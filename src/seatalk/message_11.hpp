#ifndef __SEATALK__MESSAGE_11__HPP__
#define __SEATALK__MESSAGE_11__HPP__

#include "message.hpp"

namespace seatalk
{

class message_11 : public message
{
public:
	constexpr static const message_id ID = message_id::apparent_wind_speed;

	message_11();
	message_11(const message_11&) = default;
	message_11& operator=(const message_11&) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw& data) throw(std::invalid_argument);

private:
	uint8_t unit; // unit of value
	uint16_t speed; // wind speed in 1/10th of unit

public:
	uint8_t get_unit() const { return unit; }
	uint16_t get_speed() const { return speed; }

	void set_unit(uint8_t t) { unit = t; }
	void set_speed(uint16_t t) { speed = t; }
};

}

#endif
