#include "convert.hpp"
#include <stdexcept>
#include <cassert>

namespace marnav
{
namespace nmea
{
direction convert_hemisphere(const geo::latitude & p) noexcept
{
	switch (p.hem()) {
		case geo::latitude::hemisphere::north:
			return direction::north;
		case geo::latitude::hemisphere::south:
			return direction::south;
		default:
			assert(false);
	}
	return direction::none;
}

direction convert_hemisphere(const geo::longitude & p) noexcept
{
	switch (p.hem()) {
		case geo::longitude::hemisphere::east:
			return direction::east;
		case geo::longitude::hemisphere::west:
			return direction::west;
		default:
			assert(false);
	}
	return direction::none;
}

geo::latitude::hemisphere convert_hemisphere_lat(direction t)
{
	switch (t) {
		case direction::north:
			return geo::latitude::hemisphere::north;
		case direction::south:
			return geo::latitude::hemisphere::south;
		default:
			throw std::invalid_argument{"invalid hemisphere for latitude"};
	}
}

geo::longitude::hemisphere convert_hemisphere_lon(direction t)
{
	switch (t) {
		case direction::east:
			return geo::longitude::hemisphere::east;
		case direction::west:
			return geo::longitude::hemisphere::west;
		default:
			throw std::invalid_argument{"invalid hemisphere for longitude"};
	}
}

/// \cond DEV
namespace detail
{
static geo::latitude convert_latitude(const geo::latitude & v, direction d)
{
	return {v.get(), convert_hemisphere_lat(d)};
}

static geo::longitude convert_longitude(const geo::longitude & v, direction d)
{
	return {v.get(), convert_hemisphere_lon(d)};
}
}
/// \endcond

/// @{

/// Convertes the specified latitude to a latitude with the specified
/// hemisphere (specified as direction).
///
/// If the latitude is already on the specified hemisphere, no conversion
/// will take place. Otherwise the latitude will be transformed to get
/// the desired hemisphere.
///
/// @param[in] v The latitude to convert.
/// @param[in] d The desired direction. For latitudes only `north` and `south`
///   apply.
/// @return The converted latitude.
geo::latitude correct_hemisphere(const geo::latitude & v, const direction & d)
{
	return detail::convert_latitude(v, d);
}

/// The optional version of the latitude conversion.
/// @see correct_hemisphere
std::optional<geo::latitude> correct_hemisphere(
	const std::optional<geo::latitude> & v, const std::optional<direction> & d)
{
	if (v && d)
		return correct_hemisphere(v.value(), d.value());
	return v;
}

/// Convertes the specified longitude to a longitude with the specified
/// hemisphere (specified as direction).
///
/// If the longitude is already on the specified hemisphere, no conversion
/// will take place. Otherwise the longitude will be transformed to get
/// the desired hemisphere.
///
/// @param[in] v The longitude to convert.
/// @param[in] d The desired direction. For longitudes only `east` and `west`
///   apply.
/// @return The converted longitude.
geo::longitude correct_hemisphere(const geo::longitude & v, const direction & d)
{
	return detail::convert_longitude(v, d);
}

/// The optional version of the longitude conversion.
/// @see correct_hemisphere
std::optional<geo::longitude> correct_hemisphere(
	const std::optional<geo::longitude> & v, const std::optional<direction> & d)
{
	if (v && d)
		return correct_hemisphere(v.value(), d.value());
	return v;
}

/// @}
}
}
