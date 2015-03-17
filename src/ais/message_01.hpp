#ifndef __AIS__MESSAGE_01__HPP__
#define __AIS__MESSAGE_01__HPP__

#include "message.hpp"

namespace ais
{

class message_01 : public message
{
public:
	constexpr static const message_id ID = message_id::position_report_class_a;

	static std::unique_ptr<message> parse(const raw& bits) throw(std::invalid_argument);

private:
	unsigned int repeat_indicator;
	uint32_t mmsi;
};

}

#endif
