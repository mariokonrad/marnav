#ifndef MARNAV_NMEA_CHECKSUM_ENUM_HPP
#define MARNAV_NMEA_CHECKSUM_ENUM_HPP

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
