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
///                                                    12
///        1 2       3 4        5 6   7   8   9   10  11|
///        | |       | |        | |   |   |   |   |   | |
/// $--RMA,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,x.x,x.x,x.x,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
/// 1.  Blink Warning
/// 2.  Latitude
/// 3.  N or S
/// 4.  Longitude
/// 5.  E or W
/// 6.  Time Difference A, uS
/// 7.  Time Difference B, uS
/// 8.  Speed Over Ground, Knots
/// 9.  Track Made Good, degrees true
/// 10. Magnetic Variation, degrees
/// 11. E or W
/// 12. Checksum
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
	utils::optional<char> lat_hem; // latitude dir, N:north, S:south
	utils::optional<geo::longitude> lon;
	utils::optional<char> lon_hem; // longitude dir, E:east, W:west
	utils::optional<double> time_diff_a; // time difference A in microseconds
	utils::optional<double> time_diff_b; // time difference B in microseconds
	utils::optional<double> sog; // speed over ground in knots
	utils::optional<double> track; // track made good, degrees
	utils::optional<double> magnetic_variation; // magnetic variation in degrees
	utils::optional<char> magnetic_variation_hem; // magnetic variation hemisphere, E:east, W:west

public:
	decltype(blink_warning) get_blink_warning() const { return blink_warning; }
	decltype(lat) get_lat() const { return lat; }
	decltype(lat_hem) get_lat_hem() const { return lat_hem; }
	decltype(lon) get_lon() const { return lon; }
	decltype(lon_hem) get_lon_hem() const { return lon_hem; }
	decltype(time_diff_a) get_time_diff_a() const { return time_diff_a; }
	decltype(time_diff_b) get_time_diff_b() const { return time_diff_b; }
	decltype(sog) get_sog() const { return sog; }
	decltype(track) get_track() const { return track; }
	decltype(magnetic_variation) get_magnetic_variation() const { return magnetic_variation; }
	decltype(magnetic_variation_hem) get_magnetic_variation_hem() const
	{
		return magnetic_variation_hem;
	}

	void set_blink_warning(char t) { blink_warning = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_time_diff_a(double t) { time_diff_a = t; }
	void set_time_diff_b(double t) { time_diff_b = t; }
	void set_sog(double t) { sog = t; }
	void set_track(double t) { track = t; }
	void set_magnetic_variation(double t, char h)
	{
		magnetic_variation = t;
		magnetic_variation_hem = h;
	}
};
}
}

#endif
