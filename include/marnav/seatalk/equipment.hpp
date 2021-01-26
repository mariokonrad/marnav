#ifndef MARNAV_SEATALK_EQUIPMENT_HPP
#define MARNAV_SEATALK_EQUIPMENT_HPP

#include <array>

namespace marnav
{
namespace seatalk
{
/// Type for the equipment identification.
using equipment_id = std::array<uint8_t, 6>;

/// Unknown or invalid equipment identifier.
constexpr equipment_id equipment_invalid{{0x00, 0x00, 0x00, 0x00, 0x00, 0x00}};
}
}

#endif
