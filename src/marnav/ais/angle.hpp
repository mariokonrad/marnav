#ifndef __AIS__ANGLE__HPP__
#define __AIS__ANGLE__HPP__

#include <marnav/geo/angle.hpp>

namespace marnav
{
namespace ais
{
marnav::geo::latitude to_geo_latitude(uint32_t latitude_minutes);
uint32_t to_latitude_minutes(const marnav::geo::latitude & lat);
marnav::geo::longitude to_geo_longitude(uint32_t longitude_minutes);
uint32_t to_longitude_minutes(const marnav::geo::longitude & lon);
}
}

#endif
