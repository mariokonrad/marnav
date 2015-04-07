#ifndef __SEATALK__MESSAGE_22__HPP__
#define __SEATALK__MESSAGE_22__HPP__

#include "message.hpp"

namespace marnav
{
namespace seatalk
{

class message_22 : public message
{
public:
	constexpr static const message_id ID = message_id::total_mileage;

	message_22();
	message_22(const message_22 &) = default;
	message_22 & operator=(const message_22 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data) throw(std::invalid_argument);

private:
	uint32_t distance; // in 1/10th nautical miles

public:
	uint32_t get_distance() const { return distance; }

	void set_distance(uint32_t t) { distance = t; }
};
}
}

#endif
