#include "constants.hpp"
#include <marnav/geo/angle.hpp>

namespace marnav
{
namespace nmea
{
direction convert_hemisphere(const geo::latitude & p) noexcept
{
	switch (p.hem()) {
		case geo::latitude::hemisphere::NORTH:
			return direction::NORTH;
		case geo::latitude::hemisphere::SOUTH:
			return direction::SOUTH;
	}

	// never reached, bad for coverage, supresses compiler warning
	return static_cast<direction>(-1);
}

direction convert_hemisphere(const geo::longitude & p) noexcept
{
	switch (p.hem()) {
		case geo::longitude::hemisphere::EAST:
			return direction::EAST;
		case geo::longitude::hemisphere::WEST:
			return direction::WEST;
	}

	// never reached, bad for coverage, supresses compiler warning
	return static_cast<direction>(-1);
}

geo::latitude::hemisphere convert_hemisphere_lat(direction t)
{
	switch (t) {
		case direction::NORTH:
			return geo::latitude::hemisphere::NORTH;
		case direction::SOUTH:
			return geo::latitude::hemisphere::SOUTH;
		default:
			throw std::invalid_argument{"invalid hemisphere for latitude"};
	}
}

geo::longitude::hemisphere convert_hemisphere_lon(direction t)
{
	switch (t) {
		case direction::EAST:
			return geo::longitude::hemisphere::EAST;
		case direction::WEST:
			return geo::longitude::hemisphere::WEST;
		default:
			throw std::invalid_argument{"invalid hemisphere for longitude"};
	}
}
}
}
