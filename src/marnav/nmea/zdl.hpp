#ifndef __NMEA__ZDL__HPP__
#define __NMEA__ZDL__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(zdl)

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
	MARNAV_NMEA_SENTENCE_FRIENDS(zdl)

public:
	constexpr static const sentence_id ID = sentence_id::ZDL;
	constexpr static const char * TAG = "ZDL";

	virtual ~zdl() {}

	zdl();
	zdl(const zdl &) = default;
	zdl & operator=(const zdl &) = default;

protected:
	zdl(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	duration time_to_point;
	double distance = 0.0;
	type_of_point type_point = type_of_point::reference;

public:
	NMEA_GETTER(time_to_point)
	NMEA_GETTER(distance)
	NMEA_GETTER(type_point)

	void set_time_to_point(const duration & t) noexcept { time_to_point = t; }
	void set_distance(double t) noexcept { distance = t; }
	void set_type_point(type_of_point t) noexcept { type_point = t; }
};
}
}

#endif
