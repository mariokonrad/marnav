#ifndef __GEO__POSITION__HPP__
#define __GEO__POSITION__HPP__

#include "angle.hpp"

namespace marnav
{
namespace geo
{
struct position {
	position() = default;

	latitude lat;
	longitude lon;
};
}
}

#endif
