#ifndef MARNAV__NMEA__HFB__HPP
#define MARNAV__NMEA__HFB__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

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
	virtual void append_data_to(std::string &) const override;

private:
	double distance_head_foot_ = 0.0;
	unit::distance distance_head_foot_unit_ = unit::distance::meter;
	double distance_head_bottom_ = 0.0;
	unit::distance distance_head_bottom_unit_ = unit::distance::meter;

public:
	decltype(distance_head_foot_) get_distance_head_foot() const { return distance_head_foot_; }
	decltype(distance_head_foot_unit_) get_distance_head_foot_unit() const
	{
		return distance_head_foot_unit_;
	}
	decltype(distance_head_bottom_) get_distance_head_bottom() const
	{
		return distance_head_bottom_;
	}
	decltype(distance_head_bottom_unit_) get_distance_head_bottom_unit() const
	{
		return distance_head_bottom_unit_;
	}

	void set_head_foot(double t) noexcept
	{
		distance_head_foot_ = t;
		distance_head_foot_unit_ = unit::distance::meter;
	};
	void set_head_bottom(double t) noexcept
	{
		distance_head_bottom_ = t;
		distance_head_bottom_unit_ = unit::distance::meter;
	};
};
}
}

#endif
