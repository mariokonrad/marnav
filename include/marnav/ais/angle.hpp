#ifndef MARNAV__AIS__ANGLE__HPP
#define MARNAV__AIS__ANGLE__HPP

#include <marnav/geo/angle.hpp>

namespace marnav
{
namespace ais
{
/// Enumeration of angle scaling according to http://www.catb.org/gpsd/AIVDM.html
enum class angle_scale { I1, I3, I4 };

marnav::geo::latitude to_geo_latitude(
	uint32_t latitude_minutes, std::size_t bits, angle_scale scale);

uint32_t to_latitude_minutes(
	const marnav::geo::latitude & lat, std::size_t bits, angle_scale scale);

marnav::geo::longitude to_geo_longitude(
	uint32_t longitude_minutes, std::size_t bits, angle_scale scale);

uint32_t to_longitude_minutes(
	const marnav::geo::longitude & lon, std::size_t bits, angle_scale scale);
}
}

#endif
