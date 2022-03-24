#ifndef MARNAV_NMEA_BEC_HPP
#define MARNAV_NMEA_BEC_HPP

#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/units/units.hpp>

namespace marnav
{
namespace nmea
{
/// @brief BEC - Bearing and Distance to Waypoint - Dead Reckoning
///
/// @code
///        1         2       3 4        5 6   7 8   9 10 11 12
///        |         |       | |        | |   | |   | |   | |
/// $--BEC,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x.x,T,x.x,M,x.x,N,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  Time UTC
/// 2.  Latitude
/// 3.  Latitude hemisphere
///     - N = North
///     - S = South
/// 4.  Longitude
/// 5.  Longitude hemisphere
///     - E = East
///     - W = West
/// 6.  Bearing True
/// 7.  Bearing Reference
///     - T = True
/// 8.  Bearing Magnetic
/// 9.  - M = Magnetic
/// 10. Distance to waypoint in nautical miles
/// 11. Units of distance to waypoint
///     - N = nautical miles
/// 12. Waypoint ID
///
class bec : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::BEC;
	constexpr static const char * TAG = "BEC";

	bec();
	bec(const bec &) = default;
	bec & operator=(const bec &) = default;
	bec(bec &&) = default;
	bec & operator=(bec &&) = default;

protected:
	bec(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	nmea::time time_utc_;
	geo::latitude lat_;
	direction lat_hem_ = direction::north;
	geo::longitude lon_;
	direction lon_hem_ = direction::east;
	double bearing_true_ = {};
	double bearing_magn_ = {};
	units::nautical_miles distance_ = {};
	waypoint waypoint_id_;

public:
	nmea::time get_time_utc() const { return time_utc_; }
	double get_bearing_true() const { return bearing_true_; }
	double get_bearing_magn() const { return bearing_magn_; }
	units::length get_distance() const { return {distance_}; }
	waypoint get_waypoint() const { return waypoint_id_; }
	geo::latitude get_lat() const;
	geo::longitude get_lon() const;

	void set_time_utc(const nmea::time & t);
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_bearing_true(double t);
	void set_bearing_magn(double t);
	void set_distance(units::length t);
	void set_waypoint(const waypoint & id) { waypoint_id_ = id; }
};
}
}

#endif
