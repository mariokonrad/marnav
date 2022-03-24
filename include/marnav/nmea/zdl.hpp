#ifndef MARNAV_NMEA_ZDL_HPP
#define MARNAV_NMEA_ZDL_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/units/units.hpp>
#include <optional>

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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	duration time_to_point_;
	units::nautical_miles distance_;
	type_of_point type_point_ = type_of_point::reference;

public:
	duration get_time_to_point() const { return time_to_point_; }
	units::length get_distance() const { return {distance_}; }
	type_of_point get_type_point() const { return type_point_; }

	void set_time_to_point(const duration & t) noexcept { time_to_point_ = t; }
	void set_distance(units::length t) noexcept { distance_ = t.get<units::nautical_miles>(); }
	void set_type_point(type_of_point t) noexcept { type_point_ = t; }
};
}
}

#endif
