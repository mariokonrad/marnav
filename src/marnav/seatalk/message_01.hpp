#ifndef MARNAV__SEATALK__MESSAGE_01__HPP
#define MARNAV__SEATALK__MESSAGE_01__HPP

#include <marnav/seatalk/message.hpp>
#include <marnav/seatalk/equipment.hpp>

namespace marnav
{
namespace seatalk
{
/// @brief Equipment ID
///
/// @code
/// 01 05 XX XX XX XX XX XX
/// @endcode
///
/// Known examples:
/// @code
/// 01 05 00 00 00 60 01 00 : Course Computer 400G
/// 01 05 04 BA 20 28 01 00 : ST60 Tridata
/// 01 05 70 99 10 28 01 00 : ST60 Log
/// 01 05 F3 18 00 26 0F 06 : ST80 Masterview
/// 01 05 FA 03 00 30 07 03 : ST80 Maxi Display
/// 01 05 FF FF FF D0 00 00 : Smart Controller Remote Control Handset
/// @endcode
///
class message_01 : public message
{
public:
	constexpr static const message_id ID = message_id::equipment_id;
	constexpr static size_t SIZE = 8;

	/// @{
	constexpr static equipment_id course_computer_400g{{0x00, 0x00, 0x00, 0x60, 0x01, 0x00}};
	constexpr static equipment_id st60_tridata{{0x04, 0xba, 0x20, 0x28, 0x01, 0x00}};
	constexpr static equipment_id st60_log{{0x70, 0x99, 0x10, 0x28, 0x01, 0x00}};
	constexpr static equipment_id st80_masterview{{0xf3, 0x18, 0x00, 0x26, 0x0f, 0x06}};
	constexpr static equipment_id st80_maxi_display{{0xfa, 0x03, 0x00, 0x30, 0x07, 0x03}};
	constexpr static equipment_id smart_controller_remote_control_handset{
		{0xff, 0xff, 0xff, 0xd0, 0x00, 0x00}};
	/// @}

	message_01();
	message_01(const message_01 &) = default;
	message_01 & operator=(const message_01 &) = default;

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
