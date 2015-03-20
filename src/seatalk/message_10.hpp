#ifndef __SEATALK__MESSAGE_10__HPP__
#define __SEATALK__MESSAGE_10__HPP__

#include "message.hpp"

namespace seatalk
{

class message_10 : public message
{
public:
	constexpr static const message_id ID = message_id::apparent_wind_angle;

	message_10();
	message_10(const message_10&) = default;
	message_10& operator=(const message_10&) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw& data) throw(std::invalid_argument);

private:
	uint16_t angle; // 1/10th of degrees right of bow

public:
	uint16_t get_angle() const { return angle; }

	void set_angle(uint16_t t) { angle = t; }
};

}

#endif
