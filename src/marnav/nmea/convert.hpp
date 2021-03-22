#ifndef MARNAV_NMEA_CONVERT_HPP
#define MARNAV_NMEA_CONVERT_HPP

#include <marnav/nmea/constants.hpp>
#include <marnav/geo/angle.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
direction convert_hemisphere(const geo::latitude & p) noexcept;
direction convert_hemisphere(const geo::longitude & p) noexcept;
geo::latitude::hemisphere convert_hemisphere_lat(direction t);
geo::longitude::hemisphere convert_hemisphere_lon(direction t);

geo::latitude correct_hemisphere(const geo::latitude & v, const direction & d);

std::optional<geo::latitude> correct_hemisphere(
	const std::optional<geo::latitude> & v, const std::optional<direction> & d);

geo::longitude correct_hemisphere(const geo::longitude & v, const direction & d);

std::optional<geo::longitude> correct_hemisphere(
	const std::optional<geo::longitude> & v, const std::optional<direction> & d);
}
}

#endif
