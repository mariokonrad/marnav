#ifndef __GEO__REGION__HPP__
#define __GEO__REGION__HPP__

#include <marnav/geo/position.hpp>

namespace marnav
{
namespace geo
{

/// This class represents a geographical region, defined
/// by two coordinates top/left and bottom/right. The
/// coordinates are a pair of lat/lon.
class region
{
public:
	region(const position & a0, const position & a1);

	region(const region &) = default;
	region(region &&) = default;

	region & operator=(const region &) = default;
	region & operator=(region &&) = default;

	latitude left() const;
	latitude right() const;
	longitude top() const;
	longitude bottom() const;

	bool inside(const position & p) const;

private:
	position p0; // top, left
	position p1; // bottom, right
};
}
}

#endif
