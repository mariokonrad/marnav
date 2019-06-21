#ifndef MARNAV__SEATALK__MESSAGE_6C__HPP
#define MARNAV__SEATALK__MESSAGE_6C__HPP

#include <marnav/seatalk/message.hpp>
#include <marnav/seatalk/equipment.hpp>

namespace marnav
{
namespace seatalk
{
/// @brief Second Equipment ID
///
/// Second equipment ID message, follows message `01`.
///
/// @code
/// 6c 05 XX XX XX XX XX XX
/// @endcode
///
/// Known examples:
/// @code
/// 6C 05 04 BA 20 28 2D 2D : ST60 Tridata
/// 6C 05 05 70 99 10 28 2D : ST60 Log
/// 6C 05 F3 18 00 26 2D 2D : ST80 Masterview
/// @endcode
///
class message_6c : public message
{
public:
	constexpr static const message_id ID = message_id::equipment_id_2;
	constexpr static size_t SIZE = 8;

	/// @{
	constexpr static equipment_id st60_tridata{{0x04, 0xba, 0x20, 0x28, 0x2d, 0x2d}};
	constexpr static equipment_id st60_log{{0x05, 0x70, 0x99, 0x10, 0x28, 0x2d}};
	constexpr static equipment_id st80_masterview{{0xf3, 0x18, 0x00, 0x26, 0x2d, 0x2d}};
	/// @}

	message_6c();
	message_6c(const message_6c &) = default;
	message_6c & operator=(const message_6c &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	equipment_id id_;

public:
	equipment_id get_equipment_id() const noexcept { return id_; }

	void set_equipment_id(const equipment_id & t) noexcept { id_ = t; }
};
}
}

#endif
