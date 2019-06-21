#ifndef MARNAV__SEATALK__KEY__HPP
#define MARNAV__SEATALK__KEY__HPP

#include <cstdint>

namespace marnav
{
namespace seatalk
{
// clang-format off

/// Enumeration of all supported keystrokes, regardless of possible
/// origin for keystrokes (not all origins can send all keystrokes).
///
/// The enumeration also contains all unused codes up to somewhere `0x8f`.
///
/// This must be an `enum class` in order to prevent combinations
/// of the listed keystrokes, they are not supposed to be combined.
///
enum class key : uint8_t {
	//                      0x00
	key_auto              = 0x01, ///< Auto
	key_standby           = 0x02, ///< Standby
	key_track             = 0x03, ///< Track
	key_disp              = 0x04, ///< Disp
	key_m1                = 0x05, ///< -1
	key_m10               = 0x06, ///< -10
	key_p1                = 0x07, ///< +1
	key_p10               = 0x08, ///< +10
	key_m1_rg             = 0x09, ///< -1 (rudder gain mode)
	key_p1_rg             = 0x0a, ///< +1 (rudder gain mode)
	//                      0x0b
	//                      0x0c
	//                      0x0d
	//                      0x0e
	//                      0x0f
	//                      0x10
	//                      0x10
	//                      0x11
	//                      0x12
	//                      0x13
	//                      0x14
	//                      0x15
	//                      0x16
	//                      0x17
	//                      0x18
	//                      0x19
	//                      0x1a
	//                      0x1b
	//                      0x1c
	//                      0x1d
	//                      0x1e
	//                      0x1f
	key_p1_m1             = 0x20, ///< +1 & -1
	key_m1_m10            = 0x21, ///< -1 & -10
	key_p1_p10            = 0x22, ///< +1 & -10
	key_standby_auto      = 0x23, ///< Standby & Auto
	//                      0x24
	//                      0x25
	//                      0x26
	//                      0x27
	key_p10_m10           = 0x28, ///< +10 & -10
	//                      0x29,
	//                      0x2a,
	//                      0x2b,
	//                      0x2c,
	//                      0x2d,
	key_p1_m1_rd          = 0x2e, ///< +1 & -1 (Response Display)
	//                      0x2e,
	//                      0x2f,
	//                      0x30,
	//                      0x31,
	//                      0x32,
	//                      0x33,
	//                      0x34,
	//                      0x35,
	//                      0x36,
	//                      0x37,
	//                      0x38,
	//                      0x39,
	//                      0x3a,
	//                      0x3b,
	//                      0x3c,
	//                      0x3d,
	//                      0x3e,
	//                      0x3f,
	//                      0x40,
	key_auto_long         = 0x41, ///< Auto pressed longer
	key_standby_long      = 0x42, ///< Standby pressed longer
	key_track_long        = 0x43, ///< Track pressed longer
	key_disp_long         = 0x44, ///< Disp pressed longer
	key_m1_long           = 0x45, ///<  -1 pressed longer
	key_m10_long          = 0x46, ///< -10 pressed longer
	key_p1_long           = 0x47, ///<  +1 pressed longer
	key_p10_long          = 0x48, ///< +10 pressed longer
	//                      0x49,
	//                      0x4a,
	//                      0x4b,
	//                      0x4c,
	//                      0x4d,
	//                      0x4e,
	//                      0x4f,
	//                      0x50,
	//                      0x51,
	//                      0x52,
	//                      0x53,
	//                      0x54,
	//                      0x55,
	//                      0x56,
	//                      0x57,
	//                      0x58,
	//                      0x59,
	//                      0x5a,
	//                      0x5b,
	//                      0x5c,
	//                      0x5d,
	//                      0x5e,
	//                      0x5f,
	key_p1_m1_long        = 0x60, ///< +1 &  -1  pressed longer
	key_p1_m10_long       = 0x61, ///< -1 & -10  pressed longer
	key_p1_p10_long       = 0x62, ///< +1 & +10  pressed longer
	key_standby_auto_long = 0x63, ///< Standby & Auto pressed longer (previous wind angle)
	key_p10_m10_long_s    = 0x64, ///< +10 & -10  pressed longer (why not 11 68 97 ?)
	//                      0x65,
	//                      0x66,
	//                      0x67,
	key_p10_m10_long      = 0x68, ///< +10 & -10 pressed longer (in auto mode)
	//                      0x69,
	//                      0x6a,
	//                      0x6b,
	//                      0x6c,
	//                      0x6d,
	key_p1_m1_long_rg     = 0x6e, ///< +1 & -1 pressed longer (Rudder Gain Display)
	//                      0x6f,
	//                      0x70,
	//                      0x71,
	//                      0x72,
	//                      0x73,
	//                      0x74,
	//                      0x75,
	//                      0x76,
	//                      0x77,
	//                      0x78,
	//                      0x79,
	//                      0x7a,
	//                      0x7b,
	//                      0x7c,
	//                      0x7d,
	//                      0x7e,
	//                      0x7f,
	key_m1_repeat         = 0x80, ///< -1 pressed (repeated 1x per second)
	key_p1_repeat         = 0x81, ///< +1 pressed (repeated 1x per second)
	key_m10_repeat        = 0x82, ///< -10 pressed (repeated 1x per second)
	key_p10_repeat        = 0x83, ///< +10 pressed (repeated 1x per second)
	key_num_release       = 0x84, ///< +1, -1, +10 or -10 released
	//                      0x85,
	// ... and all until 0xff ...
};

// clang-format on
}
}

#endif
