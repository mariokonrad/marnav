#ifndef __NMEA__RMA__HPP__
#define __NMEA__RMA__HPP__

#include "sentence.hpp"
#include "angle.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

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
public:
	constexpr static const sentence_id ID = sentence_id::RMA;
	constexpr static const char * TAG = "RMA";

	rma();
	rma(const rma &) = default;
	rma & operator=(const rma &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
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
	NMEA_GETTER(blink_warning)
	NMEA_GETTER(lat)
	NMEA_GETTER(lat_hem)
	NMEA_GETTER(lon)
	NMEA_GETTER(lon_hem)
	NMEA_GETTER(time_diff_a)
	NMEA_GETTER(time_diff_b)
	NMEA_GETTER(sog)
	NMEA_GETTER(track)
	NMEA_GETTER(magnetic_var)
	NMEA_GETTER(magnetic_var_hem)

	void set_blink_warning(char t) { blink_warning = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_time_diff_a(double t) { time_diff_a = t; }
	void set_time_diff_b(double t) { time_diff_b = t; }
	void set_sog(double t) { sog = t; }
	void set_track(double t) { track = t; }
	void set_magnetic_var(double t, direction h) throw(std::invalid_argument);
};
}
}

#endif
