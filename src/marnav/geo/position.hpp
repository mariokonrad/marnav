#ifndef __GEO__POSITION__HPP__
#define __GEO__POSITION__HPP__

#include "angle.hpp"

namespace marnav
{
namespace geo
{
struct position {
	position() = default;
	position(const position &) = default;
	position(position &&) = default;

	position & operator=(const position &) = default;
	position & operator=(position &&) = default;

	bool operator==(const position & other) const;

	latitude lat;
	longitude lon;
};

position deg2rad(const position & p);
position rad2deg(const position & p);
}
}

#endif
