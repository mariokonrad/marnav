#include "position.hpp"
#include <cmath>

namespace marnav
{
namespace geo
{
bool position::operator==(const position & other) const
{
	return lat == other.lat && lon == other.lon;
}

position deg2rad(const position & p) { return {M_PI / 180.0 * p.lat, M_PI / 180.0 * p.lon}; }
position rad2deg(const position & p) { return {p.lat / M_PI * 180.0, p.lon / M_PI * 180.0}; }
}
}
