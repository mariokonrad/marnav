#ifndef MARNAV__NMEA__CHECKSUM_ENUM__HPP
#define MARNAV__NMEA__CHECKSUM_ENUM__HPP

#include <marnav/marnav_export.h>

namespace marnav
{
namespace nmea
{
/// This enumeration defines options about strategies of handling checksums.
enum class MARNAV_EXPORT checksum_handling {
	check, ///< Perform checksum check.
	ignore ///< Ignore the checksum.
};
}
}

#endif
