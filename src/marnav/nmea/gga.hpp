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
///         1         2       3 4        5 6 7  8   9  10 |  12 13  14   15
///         |         |       | |        | | |  |   |   | |   | |   |    |
///  $--GGA,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x,xx,x.x,x.x,M,x.x,M,x.x,xxxx*hh<CR><LF>
/// @endcode
//
/// Field Number:
///
///  1.  Universal Time Coordinated (UTC)
///  2.  Latitude
///  3.  N or S (North or South)
///  4.  Longitude
///  5.  E or W (East or West)
///  6.  GPS Quality Indicator,
///      - 0 - fix not available,
///      - 1 - GPS fix,
///      - 2 - Differential GPS fix (values above 2 are 2.3 features)
///      - 3 - PPS fix
///      - 4 - Real Time Kinematic
///      - 5 - Float RTK
///      - 6 - estimated (dead reckoning)
///      - 7 - Manual input mode
///      - 8 - Simulation mode
///  7.  Number of satellites in view, 00 - 12
///  8.  Horizontal Dilution of precision (meters)
///  9.  Antenna Altitude above/below mean-sea-level (geoid) (in meters)
///  10. Units of antenna altitude, meters
///  11. Geoidal separation, the difference between the WGS-84 earth ellipsoid and
///      mean-sea-level (geoid), "-" means mean-sea-level below ellipsoid
///  12. Units of geoidal separation, meters
///  13. Age of differential GPS data, time in seconds since last SC104 type 1 or 9 update,
///      null field when DGPS is not used
///  14. Differential reference station ID, 0000-1023
///  15. Checksum
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
	utils::optional<char> lat_hem; // N:north, S:south
	utils::optional<geo::longitude> lon;
	utils::optional<char> lon_hem; // E:east, W:west
	utils::optional<uint32_t> quality;
	utils::optional<uint32_t> n_satellites;
	utils::optional<double> hor_dilution; // horizontal dilution of precision
	utils::optional<double> height_antenna; // height of antenna over geoid
	utils::optional<char> unit_antenna; // M:meter
	utils::optional<double>
		geodial_separation; // geodial separation, sea level below the ellipsoid
	utils::optional<char> unit_geodial_separation; // M:meter
	utils::optional<double> dgps_age; // age of dgps data
	utils::optional<uint32_t> dgps_ref; // dgps reference station 0000..1023

public:
	decltype(time) get_time() const { return time; }
	decltype(lat) get_lat() const { return lat; }
	decltype(lat_hem) get_lat_hem() const { return lat_hem; }
	decltype(lon) get_lon() const { return lon; }
	decltype(lon_hem) get_lon_hem() const { return lon_hem; }
	decltype(quality) get_quality() const { return quality; }
	decltype(n_satellites) get_n_satellites() const { return n_satellites; }
	decltype(hor_dilution) get_hor_dilution() const { return hor_dilution; }
	decltype(height_antenna) get_height_antenna() const { return height_antenna; }
	decltype(unit_antenna) get_unit_antenna() const { return unit_antenna; }
	decltype(geodial_separation) get_geodial_separation() const { return geodial_separation; }
	decltype(unit_geodial_separation) get_unit_geodial_separation() const
	{
		return unit_geodial_separation;
	}
	decltype(dgps_age) get_dgps_age() const { return dgps_age; }
	decltype(dgps_ref) get_dgps_ref() const { return dgps_ref; }

	void set_time(const nmea::time & t) { time = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_quality(uint32_t t) { quality = t; }
	void set_n_satellites(uint32_t t) { n_satellites = t; }
	void set_hor_dilution(double t) { hor_dilution = t; }
	void set_height_antenna(double t) { height_antenna = t; }
	void set_unit_antenna(char t) { unit_antenna = t; }
	void set_geodial_separation(double t) { geodial_separation = t; }
	void set_unit_geodial_separation(char t) { unit_geodial_separation = t; }
	void set_dgps_age(double t) { dgps_age = t; }
	void set_dgps_ref(uint32_t t) { dgps_ref = t; }
};
}
}

#endif
