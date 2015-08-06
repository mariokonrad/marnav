#ifndef __AIS__MESSAGE_03__HPP__
#define __AIS__MESSAGE_03__HPP__

#include "message_01.hpp"

namespace marnav
{
namespace ais
{

/// @brief Position Report Class A (response to interrogation)
class message_03 : public message_01
{
public:
	constexpr static const message_id ID
		= message_id::position_report_class_a_response_to_interrogation;

	message_03();
	message_03(const message_03 &) = default;
	message_03 & operator=(const message_03 &) = default;

	static std::unique_ptr<message> parse(const raw & bits) throw(
		std::invalid_argument, std::out_of_range);
};
}
}

#endif
