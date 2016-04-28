#ifndef __NMEA__TPR__HPP__
#define __NMEA__TPR__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

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
public:
	constexpr static const sentence_id ID = sentence_id::TPR;
	constexpr static const char * TAG = "TPR";

	tpr();
	tpr(const tpr &) = default;
	tpr & operator=(const tpr &) = default;

	static std::unique_ptr<sentence> parse(
		const std::string & talker, fields::const_iterator first, fields::const_iterator last);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	double range;
	unit::distance range_unit;
	double bearing;
	double depth;
	unit::distance depth_unit;

public:
	NMEA_GETTER(range)
	NMEA_GETTER(range_unit)
	NMEA_GETTER(bearing)
	NMEA_GETTER(depth)
	NMEA_GETTER(depth_unit)

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
