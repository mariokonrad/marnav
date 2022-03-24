#ifndef MARNAV_NMEA_TPT_HPP
#define MARNAV_NMEA_TPT_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	units::meters range_;
	double bearing_ = 0.0;
	units::meters depth_;

public:
	units::length get_range() const { return range_; }
	double get_bearing() const { return bearing_; }
	units::length get_depth() const { return depth_; }

	void set_range(units::length t) noexcept { range_ = t.get<units::meters>(); }
	void set_bearing(double t) noexcept { bearing_ = t; }
	void set_depth(units::length t) noexcept { depth_ = t.get<units::meters>(); }
};
}
}

#endif
