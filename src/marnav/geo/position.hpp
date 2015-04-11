#ifndef __GEO__POSITION__HPP__
#define __GEO__POSITION__HPP__

#include "angle.hpp"

namespace marnav
{
namespace geo
{
struct position {
	position() = default;

	bool operator==(const position & other) const;

	latitude lat;
	longitude lon;
};

position deg2rad(const position & p);
position rad2deg(const position & p);
}
}

#endif
