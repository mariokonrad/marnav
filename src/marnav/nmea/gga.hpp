#ifndef __NMEA__GGA__HPP__
#define __NMEA__GGA__HPP__

#include "sentence.hpp"
#include "angle.hpp"
#include "time.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

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
class gga : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::GGA;
	constexpr static const char * TAG = "GGA";

	gga();
	gga(const gga &) = default;
	gga & operator=(const gga &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<nmea::time> time;
	utils::optional<geo::latitude> lat;
	utils::optional<direction> lat_hem; // N:north, S:south
	utils::optional<geo::longitude> lon;
	utils::optional<direction> lon_hem; // E:east, W:west
	utils::optional<uint32_t> quality;
	utils::optional<uint32_t> n_satellites;
	utils::optional<double> hor_dilution; // horizontal dilution of precision
	utils::optional<double> altitude;
	utils::optional<char> altitude_unit; // M:meter
	utils::optional<double>
		geodial_separation; // geodial separation, sea level below the ellipsoid
	utils::optional<char> geodial_separation_unit; // M:meter
	utils::optional<double> dgps_age; // age of dgps data
	utils::optional<uint32_t> dgps_ref; // dgps reference station 0000..1023

public:
	NMEA_GETTER(time)
	NMEA_GETTER(lat)
	NMEA_GETTER(lat_hem)
	NMEA_GETTER(lon)
	NMEA_GETTER(lon_hem)
	NMEA_GETTER(quality)
	NMEA_GETTER(n_satellites)
	NMEA_GETTER(hor_dilution)
	NMEA_GETTER(altitude)
	NMEA_GETTER(altitude_unit)
	NMEA_GETTER(geodial_separation)
	NMEA_GETTER(geodial_separation_unit)
	NMEA_GETTER(dgps_age)
	NMEA_GETTER(dgps_ref)

	void set_time(const nmea::time & t) { time = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_quality(uint32_t t) { quality = t; }
	void set_n_satellites(uint32_t t) { n_satellites = t; }
	void set_hor_dilution(double t) { hor_dilution = t; }
	void set_altitude(double t) { altitude = t; }
	void set_altitude_unit(char t) { altitude_unit = t; }
	void set_geodial_separation(double t, char u)
	{
		geodial_separation = t;
		geodial_separation_unit = u;
	}
	void set_dgps_age(double t) { dgps_age = t; }
	void set_dgps_ref(uint32_t t) { dgps_ref = t; }
};
}
}

#endif
