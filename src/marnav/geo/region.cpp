#include "region.hpp"

namespace marnav
{
namespace geo
{

region::region(const position & a0, const position & a1)
	: p0(a0)
	, p1(a1)
{
	if (p0.lat < p1.lat)
		swap(p0.lat, p1.lat);
	if (p0.lon < p1.lon)
		swap(p0.lon, p1.lon);
}

latitude region::left() const { return p0.lat; }

latitude region::right() const { return p1.lat; }

longitude region::top() const { return p0.lon; }

longitude region::bottom() const { return p1.lon; }

/// Returns true if the specified position is inside (inclusive)
/// the region.
///
/// @param[in] p Point to test
///
/// @todo Handle datum barrier correctly
bool region::inside(const position & p) const
{
	if (p.lat > p0.lat)
		return false;
	if (p.lat < p1.lat)
		return false;
	if (p.lon > p0.lon)
		return false;
	if (p.lon < p1.lon)
		return false;
	return true;
}

}
}
