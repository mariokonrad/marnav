#ifndef MARNAV_NMEA_HFB_HPP
#define MARNAV_NMEA_HFB_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
/// @brief HFB - Trawl Headrope to Footrope and Bottom
///
/// @code
///        1   2 3   4
///        |   | |   |
/// $--HFB,x.x,M,y.y,M*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Distance from headrope to footrope in meters (0..100)
/// 2. Unit of distance headrope to footrope
///    - M = Meters
/// 3. Distance from headrope to bottom in meters (0..100)
/// 4. Unit of distance headrope to bottom
///    - M = Meters
///
class hfb : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::HFB;
	constexpr static const char * TAG = "HFB";

	hfb();
	hfb(const hfb &) = default;
	hfb & operator=(const hfb &) = default;
	hfb(hfb &&) = default;
	hfb & operator=(hfb &&) = default;

protected:
	hfb(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	units::meters distance_head_foot_;
	units::meters distance_head_bottom_;

public:
	units::length get_distance_head_foot() const { return {distance_head_foot_}; }
	units::length get_distance_head_bottom() const { return {distance_head_bottom_}; }

	void set_head_foot(units::length t) noexcept
	{
		distance_head_foot_ = t.get<units::meters>();
	}

	void set_head_bottom(units::length t) noexcept
	{
		distance_head_bottom_ = t.get<units::meters>();
	}
};
}
}

#endif
