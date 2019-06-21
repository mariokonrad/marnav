#ifndef MARNAV__NMEA__TPT__HPP
#define MARNAV__NMEA__TPT__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief TPT - Trawl Position True
///
/// @code
///        1 2 3 4  5  6
///        | | | |  |  |
/// $--TPT,x,M,y,P,z.z,M*hh,<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Horizontal range relative to target in meters (0..4000)
/// 2. Unit of horizontal range
///    - M = Meters
/// 3. True bearing to taget (ie. relative north). Resolution is one degree.
/// 4. Separator
/// 5. Depth of trawl below the surface in meters (0..2000)
/// 6. Unit of depth
///    - M = Meters
///
class tpt : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::TPT;
	constexpr static const char * TAG = "TPT";

	tpt();
	tpt(const tpt &) = default;
	tpt & operator=(const tpt &) = default;
	tpt(tpt &&) = default;
	tpt & operator=(tpt &&) = default;

protected:
	tpt(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	double range_ = 0.0;
	unit::distance range_unit_ = unit::distance::meter;
	double bearing_ = 0.0;
	double depth_ = 0.0;
	unit::distance depth_unit_ = unit::distance::meter;

public:
	decltype(range_) get_range() const { return range_; }
	decltype(range_unit_) get_range_unit() const { return range_unit_; }
	decltype(bearing_) get_bearing() const { return bearing_; }
	decltype(depth_) get_depth() const { return depth_; }
	decltype(depth_unit_) get_depth_unit() const { return depth_unit_; }

	void set_range(double t) noexcept
	{
		range_ = t;
		range_unit_ = unit::distance::meter;
	}
	void set_bearing(double t) noexcept { bearing_ = t; }
	void set_depth(double t) noexcept
	{
		depth_ = t;
		range_unit_ = unit::distance::meter;
	}
};
}
}

#endif
