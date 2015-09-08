#include "region.hpp"
#include <cmath>

namespace marnav
{
namespace geo
{

/// Initializes the region by the specified corners
///
/// @code
/// a0
/// +--------------+
/// |              |
/// |              |
/// |              |
/// +--------------+ a1
/// @endcode
///
/// @note There is no sorting of coordinates, the positions a0/a1 must
///       already be top/left,bottom/right ordering. There is no automatic
///       way to sort them because of the international date line.
///
/// @param[in] a0 Position top/left
/// @param[in] a1 Position bottom/right
/// @exception std::invalid_argument Positions are not correct. The latitude
///   of the second point <tt>p1</tt> is northerly than <tt>p0</tt>. Or positions
///   are party or fully the same.
///
region::region(const position & a0, const position & a1)
	: p0(a0)
	, p1(a1)
{
	if ((a0.lat() == a1.lat()) || (a0.lon() == a1.lon()))
		throw std::invalid_argument{"specified region lacks a dimension"};
	if (a0.lat() < a1.lat())
		throw std::invalid_argument{"specified region is upside down"};
}

/// Initializes the region by a point and two dimensions
///
/// @code
/// a     d_lon
/// +--------------+
/// |              |
/// |              | d_lat
/// |              |
/// +--------------+
/// @endcode
///
/// @param[in] a The point at the top/left corner.
/// @param[in] d_lat Height of the region towards bottom. The absolute
///                  value of this is processed.
/// @param[in] d_lon Width of the region towards right. The absolute
///                  value of this is processed.
///
region::region(const position & a, double d_lat, double d_lon)
	: p0(a)
	, p1(a)
{
	d_lat = std::abs(d_lat);
	d_lon = std::abs(d_lon);

	double t_lat = p0.lat() - d_lat;
	if (t_lat < latitude::min) {
		t_lat += (latitude::max - latitude::min);
	}
	if (t_lat > latitude::max) {
		t_lat -= (latitude::max - latitude::min);
	}

	double t_lon = p0.lon() + d_lon;
	if (t_lon < longitude::min) {
		t_lon += (longitude::max - longitude::min);
	}
	if (t_lon > longitude::max) {
		t_lon -= (longitude::max - longitude::min);
	}

	p1 = position{t_lat, t_lon};
}

longitude region::left() const { return p0.lon(); }

longitude region::right() const { return p1.lon(); }

latitude region::top() const { return p0.lat(); }

latitude region::bottom() const { return p1.lat(); }

/// Returns true if the specified position is inside (inclusive)
/// the region.
///
/// @param[in] p Point to test.
/// @retval true Point is in the region or on regions boundary.
/// @retval false Point outside the region.
///
bool region::inside(const position & p) const
{
	// testing latitude is easy, there is no date line, no wrap-arround
	if (p.lat() > p0.lat())
		return false;
	if (p.lat() < p1.lat())
		return false;

	// testint longitude

	// shifted longitudes, now between 0..360 (date line, eastwards)
	const double plon_s = 180.0 + p.lon();
	const double p0lon_s = 180.0 + p0.lon();
	const double p1lon_s = 180.0 + p1.lon();

	// p is west of p0, but not west enough to reach p1
	if ((plon_s < p0lon_s) && (plon_s > p1lon_s))
		return false;

	return true;
}
}
}
