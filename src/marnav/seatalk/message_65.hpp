#ifndef MARNAV__SEATALK__MESSAGE_65__HPP
#define MARNAV__SEATALK__MESSAGE_65__HPP

#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace seatalk
{
/// @brief Select Fathom
///
/// @code
/// 65 00 02
/// @endcode
///
/// Select Fathom (feet/3.33) display units for depth display (see command 00)
///
class message_65 : public message
{
public:
	constexpr static const message_id ID = message_id::display_unit_select_fathom;
	constexpr static size_t SIZE = 3;

	message_65();
	message_65(const message_65 &) = default;
	message_65 & operator=(const message_65 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);
};
}
}

#endif
