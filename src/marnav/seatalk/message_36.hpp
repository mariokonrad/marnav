#ifndef __SEATALK__MESSAGE_36__HPP__
#define __SEATALK__MESSAGE_36__HPP__

#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace seatalk
{

/// @brief Cancel MOB (Man Over Board) condition
///
/// @code
/// 36 00 01
/// @endcode
///
class message_36 : public message
{
public:
	constexpr static const message_id ID = message_id::cancel_mob_condition;

	message_36();
	message_36(const message_36 &) = default;
	message_36 & operator=(const message_36 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data) throw(std::invalid_argument);
};
}
}

#endif
