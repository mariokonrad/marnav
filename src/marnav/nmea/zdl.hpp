#ifndef __NMEA__ZDL__HPP__
#define __NMEA__ZDL__HPP__

#include "sentence.hpp"
#include "time.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief ZDL - Time and Distance to Variable Point
///
/// @code
///         1         2   3 4
///         |         |   | |
///  $--ZDL,hhmmss.ss,x.x,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Time to Point, hh=00..99
/// 2. Distance to Point, nautical miles
/// 3. Type of Point, see below
/// x. Checksum
///
/// Type of Point:
/// - C = Collision
/// - T = Turning Point
/// - R = Reference (general)
/// - W = Wheelover
///
class zdl : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::ZDL;
	constexpr static const char * TAG = "ZDL";

	zdl();
	zdl(const zdl &) = default;
	zdl & operator=(const zdl &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	duration time_to_point;
	double distance;
	char type_point;

public:
	decltype(time_to_point) get_time_to_point() const { return time_to_point; }
	decltype(distance) get_distance() const { return distance; }
	decltype(type_point) get_type_point() const { return type_point; }

	void set_time_to_point(const duration & t) { time_to_point = t; }
	void set_distance(double t) { distance = t; }
	void set_type_point(char t) { type_point = t; }
};
}
}

#endif
