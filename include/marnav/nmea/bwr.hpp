#ifndef MARNAV_NMEA_BWR_HPP
#define MARNAV_NMEA_BWR_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/units/units.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief BWR - Bearing & Distance to Waypoint - Rhumb line
///
/// @code
///                                                         12
///        1         2       3 4        5 6   7 8   9 10  11|    13
///        |         |       | |        | |   | |   | |   | |    |
/// $--BWR,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x.x,T,x.x,M,x.x,N,c--c,m*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  UTCTime
/// 2.  Waypoint Latitude
/// 3.  Latitude Hemisphere
///     - N = North
///     - S = South
/// 4.  Waypoint Longitude
/// 5.  Longitude Hemisphere
///     - E = East
///     - W = West
/// 6.  Bearing True
/// 7.  Bearing True reference
///     - T = True
/// 8.  Bearing Magnetic
/// 9.  Bearing Magnetic reference
///     - M = Magnetic
/// 10. Nautical Miles
/// 11. Nautical Miles unit
///     - N = Nautical Miles
/// 12. Waypoint ID
/// 13. Mode Indicator
///     - A = Autonomous
///     - D = Differential
///     - E = Estimated
///     - M = Manual Input
///     - S = Simulated
///     - N = Data not valid
///
class bwr : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::BWR;
	constexpr static const char * TAG = "BWR";

	bwr();
	bwr(const bwr &) = default;
	bwr & operator=(const bwr &) = default;
	bwr(bwr &&) = default;
	bwr & operator=(bwr &&) = default;

protected:
	bwr(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<nmea::time> time_utc_;
	utils::optional<geo::latitude> lat_;
	utils::optional<direction> lat_hem_;
	utils::optional<geo::longitude> lon_;
	utils::optional<direction> lon_hem_;
	utils::optional<double> bearing_true_;
	utils::optional<double> bearing_mag_;
	utils::optional<units::nautical_miles> distance_;
	utils::optional<waypoint> waypoint_id_;
	utils::optional<mode_indicator> mode_ind_;

public:
	utils::optional<nmea::time> get_time_utc() const { return time_utc_; }
	utils::optional<double> get_bearing_true() const { return bearing_true_; }
	utils::optional<double> get_bearing_mag() const { return bearing_mag_; }
	utils::optional<units::length> get_distance() const;
	utils::optional<waypoint> get_waypoint_id() const { return waypoint_id_; }
	utils::optional<mode_indicator> get_mode_ind() const { return mode_ind_; }

	utils::optional<geo::longitude> get_lon() const;
	utils::optional<geo::latitude> get_lat() const;

	void set_time_utc(const nmea::time & t) noexcept { time_utc_ = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_bearing_true(double t) noexcept;
	void set_bearing_mag(double t) noexcept;
	void set_distance(units::length t);
	void set_waypoint(const waypoint & id) { waypoint_id_ = id; }
	void set_mode_ind(mode_indicator t) { mode_ind_ = t; }
};
}
}

#endif
