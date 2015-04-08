#ifndef __SEATALK__MESSAGE_01__HPP__
#define __SEATALK__MESSAGE_01__HPP__

#include "message.hpp"
#include <array>

namespace marnav
{
namespace seatalk
{

// 00 00 00 60 01 00  Course Computer 400G
// 04 BA 20 28 01 00  ST60 Tridata
// 70 99 10 28 01 00  ST60 Log
// F3 18 00 26 0F 06  ST80 Masterview
// FA 03 00 30 07 03  ST80 Maxi Display
// FF FF FF D0 00 00  Smart Controller Remote Control Handset
class message_01 : public message
{
public:
	using equipment_id_t = std::array<uint8_t, 6>;

	constexpr static const message_id ID = message_id::equipment_id;

	message_01();
	message_01(const message_01 &) = default;
	message_01 & operator=(const message_01 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data) throw(std::invalid_argument);

private:
	equipment_id_t equipment_id;

public:
	equipment_id_t get_equipment_id() const { return equipment_id; }

	void set_equipment_id(const equipment_id_t & t) { equipment_id = t; }
};
}
}

#endif
