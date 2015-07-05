#include "constants.hpp"
#include <marnav/geo/angle.hpp>

namespace marnav
{
namespace nmea
{

char convert_hemisphere(const geo::latitude & p)
{
	switch (p.hem()) {
		case geo::latitude::hemisphere::NORTH:
			return direction::NORTH;
		case geo::latitude::hemisphere::SOUTH:
			return direction::SOUTH;
	}
	return '\0'; // never reached, bad for coverage, supresses compiler warning
}

char convert_hemisphere(const geo::longitude & p)
{
	switch (p.hem()) {
		case geo::longitude::hemisphere::EAST:
			return direction::EAST;
		case geo::longitude::hemisphere::WEST:
			return direction::WEST;
	}
	return '\0'; // never reached, bad for coverage, supresses compiler warning
}

void check_waypoint_id(const std::string & id) throw(std::invalid_argument)
{
	if (id.size() > 8)
		throw std::invalid_argument{"string size to large, only 8 characters allowed for id"};
}

}
}
