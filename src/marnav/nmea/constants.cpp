#include "constants.hpp"
#include <stdexcept>
#include <cassert>
#include <marnav/geo/angle.hpp>

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
}
}
