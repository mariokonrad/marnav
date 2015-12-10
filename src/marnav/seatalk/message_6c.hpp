#ifndef __SEATALK__MESSAGE_6C__HPP__
#define __SEATALK__MESSAGE_6C__HPP__

#include <array>
#include <marnav/seatalk/message.hpp>

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
	using equipment_id_t = std::array<uint8_t, 6>;

	constexpr static const message_id ID = message_id::equipment_id_2;
	constexpr static size_t SIZE = 8;

	message_6c();
	message_6c(const message_6c &) = default;
	message_6c & operator=(const message_6c &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	equipment_id_t equipment_id;

public:
	equipment_id_t get_equipment_id() const noexcept { return equipment_id; }

	void set_equipment_id(const equipment_id_t & t) noexcept { equipment_id = t; }
};
}
}

#endif
