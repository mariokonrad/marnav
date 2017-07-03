#ifndef MARNAV__NMEA__CHECKSUM_ENUM__HPP
#define MARNAV__NMEA__CHECKSUM_ENUM__HPP

namespace marnav
{
namespace nmea
{
/// This enumeration defines options about strategies of handling checksums.
enum class checksum_handling {
	check, ///< Perform checksum check.
	ignore ///< Ignore the checksum.
};
}
}

#endif
