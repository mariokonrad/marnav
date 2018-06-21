#ifndef MARNAV__NMEA__ZDL__HPP
#define MARNAV__NMEA__ZDL__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief ZDL - Time and Distance to Variable Point
///
/// @code
///        1         2   3
///        |         |   |
/// $--ZDL,hhmmss.ss,x.x,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Time to Point, hh=00..99
/// 2. Distance to Point, nautical miles
/// 3. Type of Point, see below
///
/// Type of Point:
/// - C = Collision
/// - T = Turning Point
/// - R = Reference (general)
/// - W = Wheelover
///
class zdl : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::ZDL;
	constexpr static const char * TAG = "ZDL";

	zdl();
	zdl(const zdl &) = default;
	zdl & operator=(const zdl &) = default;
	zdl(zdl &&) = default;
	zdl & operator=(zdl &&) = default;

protected:
	zdl(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	duration time_to_point_;
	double distance_ = 0.0;
	type_of_point type_point_ = type_of_point::reference;

public:
	decltype(time_to_point_) get_time_to_point() const { return time_to_point_; }
	decltype(distance_) get_distance() const { return distance_; }
	decltype(type_point_) get_type_point() const { return type_point_; }

	void set_time_to_point(const duration & t) noexcept { time_to_point_ = t; }
	void set_distance(double t) noexcept { distance_ = t; }
	void set_type_point(type_of_point t) noexcept { type_point_ = t; }
};
}
}

#endif
