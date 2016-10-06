#ifndef __MARNAV__NMEA__RMA__HPP__
#define __MARNAV__NMEA__RMA__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(rma)

/// @brief RMA - Recommended Minimum Navigation Information
///
/// @code
///        1 2       3 4        5 6   7   8   9   10  11
///        | |       | |        | |   |   |   |   |   |
/// $--RMA,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,x.x,x.x,x.x,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  Blink Warning
/// 2.  Latitude
/// 3.  Latitude hemisphere
///     - N = North
///     - S = South
/// 4.  Longitude
/// 5.  Longitude hemisphere
///     - E = East
///     - W = West
/// 6.  Time Difference A, uS
/// 7.  Time Difference B, uS
/// 8.  Speed Over Ground, Knots
/// 9.  Track Made Good, degrees true
/// 10. Magnetic Variation, degrees
/// 11. Magnetic Variation, degrees, direction
///     - E = East
///     - W = West
///
class rma : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(rma)

public:
	constexpr static const sentence_id ID = sentence_id::RMA;
	constexpr static const char * TAG = "RMA";

	rma();
	rma(const rma &) = default;
	rma & operator=(const rma &) = default;
	rma(rma &&) = default;
	rma & operator=(rma &&) = default;

protected:
	rma(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<char> blink_warning;
	utils::optional<geo::latitude> lat;
	utils::optional<direction> lat_hem; // latitude dir, N:north, S:south
	utils::optional<geo::longitude> lon;
	utils::optional<direction> lon_hem; // longitude dir, E:east, W:west
	utils::optional<double> time_diff_a; // time difference A in microseconds
	utils::optional<double> time_diff_b; // time difference B in microseconds
	utils::optional<double> sog; // speed over ground in knots
	utils::optional<double> track; // track made good, degrees
	utils::optional<double> magnetic_var; // magnetic variation in degrees
	utils::optional<direction>
		magnetic_var_hem; // magnetic variation hemisphere, E:east, W:west

public:
	decltype(blink_warning) get_blink_warning() const { return blink_warning; }
	decltype(time_diff_a) get_time_diff_a() const { return time_diff_a; }
	decltype(time_diff_b) get_time_diff_b() const { return time_diff_b; }
	decltype(sog) get_sog() const { return sog; }
	decltype(track) get_track() const { return track; }
	decltype(magnetic_var) get_magnetic_var() const { return magnetic_var; }
	decltype(magnetic_var_hem) get_magnetic_var_hem() const { return magnetic_var_hem; }

	utils::optional<geo::longitude> get_longitude() const;
	utils::optional<geo::latitude> get_latitude() const;

	void set_blink_warning(char t) noexcept { blink_warning = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_time_diff_a(double t) noexcept { time_diff_a = t; }
	void set_time_diff_b(double t) noexcept { time_diff_b = t; }
	void set_sog(double t) noexcept { sog = t; }
	void set_track(double t) noexcept { track = t; }
	void set_magnetic_var(double t, direction h);
};
}
}

#endif
