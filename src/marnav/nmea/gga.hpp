#ifndef __MARNAV__NMEA__GGA__HPP__
#define __MARNAV__NMEA__GGA__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(gga)

/// @brief GGA - Global Positioning System Fix Data
///
/// Time, Position and fix related data for a GPS receiver.
///
/// @code
///                                                       11
///         1         2       3 4        5 6 7  8   9  10 |  12 13  14
///         |         |       | |        | | |  |   |   | |   | |   |
///  $--GGA,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x,xx,x.x,x.x,M,x.x,M,x.x,xxxx*hh<CR><LF>
/// @endcode
//
/// Field Number:
/// 1.  Universal Time Coordinated (UTC)
/// 2.  Latitude
/// 3.  Latitude hemisphere
///     - N = North
///     - S = South
/// 4.  Longitude
/// 5.  Longitude hemisphere
///     - E = East
///     - W = West
/// 6.  GPS Quality Indicator,
///     - 0 - fix not available or invalid
///     - 1 - GPS SPS Mode, fix
///     - 2 - Differential GPS, SPS mode fix
///     - 3 - GPS PPS, fix
///     - 4 - Real Time Kinematic
///     - 5 - Float RTK
///     - 6 - Estimated (dead reckoning)
///     - 7 - Manual input mode
///     - 8 - Simulation mode
/// 7.  Number of satellites in use, 00 - 12
/// 8.  Horizontal Dilution of precision (meters)
/// 9.  Altitude above/below mean-sea-level (geoid) (in meters)
/// 10. Altitude unit
///     - M = meters
/// 11. Geoidal separation, the difference between the WGS-84 earth ellipsoid and
///     mean-sea-level (geoid), "-" means mean-sea-level below ellipsoid
/// 12. Geodial Separation unit
///     - M = meters
/// 13. Age of differential GPS data, time in seconds since last SC104 type 1 or 9 update,
///     null field when DGPS is not used
/// 14. Differential reference station ID, 0000-1023
///
/// @note Raytheon RN300 sends an additional value, which is invalid and not supported
///       by the sentence
///
class gga : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(gga)

public:
	constexpr static const sentence_id ID = sentence_id::GGA;
	constexpr static const char * TAG = "GGA";

	gga();
	gga(const gga &) = default;
	gga & operator=(const gga &) = default;
	gga(gga &&) = default;
	gga & operator=(gga &&) = default;

protected:
	gga(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<nmea::time> time;
	utils::optional<geo::latitude> lat;
	utils::optional<direction> lat_hem; // N:north, S:south
	utils::optional<geo::longitude> lon;
	utils::optional<direction> lon_hem; // E:east, W:west
	utils::optional<quality> quality_indicator;
	utils::optional<uint32_t> n_satellites;
	utils::optional<double> hor_dilution; // horizontal dilution of precision
	utils::optional<double> altitude;
	utils::optional<unit::distance> altitude_unit; // M:meter
	utils::optional<double>
		geodial_separation; // geodial separation, sea level below the ellipsoid
	utils::optional<unit::distance> geodial_separation_unit; // M:meter
	utils::optional<double> dgps_age; // age of dgps data
	utils::optional<uint32_t> dgps_ref; // dgps reference station 0000..1023

public:
	decltype(time) get_time() const { return time; }
	decltype(quality_indicator) get_quality_indicator() const { return quality_indicator; }
	decltype(n_satellites) get_n_satellites() const { return n_satellites; }
	decltype(hor_dilution) get_hor_dilution() const { return hor_dilution; }
	decltype(altitude) get_altitude() const { return altitude; }
	decltype(altitude_unit) get_altitude_unit() const { return altitude_unit; }
	decltype(geodial_separation) get_geodial_separation() const { return geodial_separation; }
	decltype(geodial_separation_unit) get_geodial_separation_unit() const
	{
		return geodial_separation_unit;
	}
	decltype(dgps_age) get_dgps_age() const { return dgps_age; }
	decltype(dgps_ref) get_dgps_ref() const { return dgps_ref; }

	utils::optional<geo::longitude> get_longitude() const;
	utils::optional<geo::latitude> get_latitude() const;

	void set_time(const nmea::time & t) noexcept { time = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_quality(quality t) noexcept { quality_indicator = t; }
	void set_n_satellites(uint32_t t) noexcept { n_satellites = t; }
	void set_hor_dilution(double t) noexcept { hor_dilution = t; }
	void set_altitude(double t) noexcept
	{
		altitude = t;
		altitude_unit = unit::distance::meter;
	}
	void set_geodial_separation(double t) noexcept
	{
		geodial_separation = t;
		geodial_separation_unit = unit::distance::meter;
	}
	void set_dgps_age(double t) noexcept { dgps_age = t; }
	void set_dgps_ref(uint32_t t) noexcept { dgps_ref = t; }
};
}
}

#endif
