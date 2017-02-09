#ifndef MARNAV__SEATALK__MESSAGE_36__HPP
#define MARNAV__SEATALK__MESSAGE_36__HPP

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
	constexpr static size_t SIZE = 3;

	message_36();
	message_36(const message_36 &) = default;
	message_36 & operator=(const message_36 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);
};
}
}

#endif
