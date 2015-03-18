#ifndef __AIS__MESSAGE_01__HPP__
#define __AIS__MESSAGE_01__HPP__

#include "message.hpp"

namespace ais
{

class message_01 : public message
{
public:
	constexpr static const message_id ID = message_id::position_report_class_a;

	message_01();
	message_01(const message_01&) = default;
	message_01& operator=(const message_01&) = default;

	static std::unique_ptr<message> parse(const raw& bits) throw(std::invalid_argument);

protected:
	void read_data(const raw& bits);

private:
	unsigned int repeat_indicator;
	uint32_t mmsi;
};

}

#endif
