#ifndef MARNAV__NMEA__CONVERT__HPP
#define MARNAV__NMEA__CONVERT__HPP

#include <marnav/nmea/constants.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/optional.hpp>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace nmea
{
MARNAV_EXPORT direction convert_hemisphere(const geo::latitude & p) noexcept;
MARNAV_EXPORT direction convert_hemisphere(const geo::longitude & p) noexcept;
MARNAV_EXPORT geo::latitude::hemisphere convert_hemisphere_lat(direction t);
MARNAV_EXPORT geo::longitude::hemisphere convert_hemisphere_lon(direction t);

MARNAV_EXPORT geo::latitude correct_hemisphere(const geo::latitude & v, const direction & d);

MARNAV_EXPORT utils::optional<geo::latitude> correct_hemisphere(
	const utils::optional<geo::latitude> & v, const utils::optional<direction> & d);

MARNAV_EXPORT geo::longitude correct_hemisphere(const geo::longitude & v, const direction & d);

MARNAV_EXPORT utils::optional<geo::longitude> correct_hemisphere(
	const utils::optional<geo::longitude> & v, const utils::optional<direction> & d);
}
}

#endif
