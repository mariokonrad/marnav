#ifndef __SEATALK__MESSAGE_27__HPP__
#define __SEATALK__MESSAGE_27__HPP__

#include "message.hpp"

namespace marnav
{
namespace seatalk
{

class message_27 : public message
{
public:
	constexpr static const message_id ID = message_id::water_temperature_2;

	message_27();
	message_27(const message_27 &) = default;
	message_27 & operator=(const message_27 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data) throw(std::invalid_argument);

private:
	int32_t temperature; // temperature in 1/10th degrees celsius

public:
	int32_t get_temperature() const { return temperature; }

	void set_temperature(int32_t t) { temperature = t; }
};
}
}

#endif
