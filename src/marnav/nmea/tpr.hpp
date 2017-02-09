#ifndef MARNAV__NMEA__TPR__HPP
#define MARNAV__NMEA__TPR__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(tpr)

/// @brief TPR - Trawl Position Relative Vessel
///
/// @code
///        1 2 3 4  5  6 7
///        | | | |  |  | |
/// $--TPR,x,M,y,P,z.z,M*hh,<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Horizontal range relative to target in meters (0..4000)
/// 2. Unit of horizontal range
///    - M = Meters
/// 3. Bearing to target relative to vessel heading. Resolution is one degree.
/// 4. Separator
/// 5. Depth of trawl below the surface in meters (0..2000)
/// 6. Unit of depth
///    - M = Meters
///
class tpr : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(tpr)

public:
	constexpr static const sentence_id ID = sentence_id::TPR;
	constexpr static const char * TAG = "TPR";

	tpr();
	tpr(const tpr &) = default;
	tpr & operator=(const tpr &) = default;
	tpr(tpr &&) = default;
	tpr & operator=(tpr &&) = default;

protected:
	tpr(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	double range = 0.0;
	unit::distance range_unit = unit::distance::meter;
	double bearing = 0.0;
	double depth = 0.0;
	unit::distance depth_unit = unit::distance::meter;

public:
	decltype(range) get_range() const { return range; }
	decltype(range_unit) get_range_unit() const { return range_unit; }
	decltype(bearing) get_bearing() const { return bearing; }
	decltype(depth) get_depth() const { return depth; }
	decltype(depth_unit) get_depth_unit() const { return depth_unit; }

	void set_range(double t) noexcept
	{
		range = t;
		range_unit = unit::distance::meter;
	}
	void set_bearing(double t) noexcept { bearing = t; }
	void set_depth(double t) noexcept
	{
		depth = t;
		range_unit = unit::distance::meter;
	}
};
}
}

#endif
