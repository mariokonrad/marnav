#ifndef __NMEA__GNS__HPP__
#define __NMEA__GNS__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(gns)

/// @brief GNS - Fix data
///
/// @code
///        1         2       3 4        5 6    7  8   9   10  11  12
///        |         |       | |        | |    |  |   |   |   |   |
/// $--GNS,hhmmss.ss,llll.ll,a,yyyyy.yy,a,c--c,xx,x.x,x.x,x.x,x.x,x.x*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  UTC
/// 2.  Latitude
/// 3.  Latitude hemisphere
///     - N = North
///     - S = South
/// 4.  Longitude
/// 5.  Longitude hemisphere
///     - E = East
///     - W = West
/// 6.  Mode indicator
/// 7.  Total number of satelites in use,00-99
/// 8.  HDROP
/// 9.  Antenna altitude, meters, re:mean-sea-level(geoid.)
/// 10. Geoidal separation meters
/// 11. Age of diferential data
/// 12. Differential reference station ID
///
class gns : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(gns)

public:
	constexpr static const sentence_id ID = sentence_id::GNS;
	constexpr static const char * TAG = "GNS";

	gns();
	gns(const gns &) = default;
	gns & operator=(const gns &) = default;

protected:
	gns(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<nmea::time> time_utc;
	utils::optional<geo::latitude> lat;
	utils::optional<direction> lat_hem;
	utils::optional<geo::longitude> lon;
	utils::optional<direction> lon_hem;
	utils::optional<std::string> mode_indicator;
	utils::optional<uint32_t> number_of_satellites;
	utils::optional<double> hdrop;
	utils::optional<double> antenna_altitude; // meters
	utils::optional<double> geodial_sepration; // meters
	utils::optional<double> age_of_differential_data;
	utils::optional<double> differential_ref_station_id;

public:
	NMEA_GETTER(time_utc)
	NMEA_GETTER(lat)
	NMEA_GETTER(lat_hem)
	NMEA_GETTER(lon)
	NMEA_GETTER(lon_hem)
	NMEA_GETTER(mode_indicator)
	NMEA_GETTER(number_of_satellites)
	NMEA_GETTER(hdrop)
	NMEA_GETTER(antenna_altitude)
	NMEA_GETTER(geodial_sepration)
	NMEA_GETTER(age_of_differential_data)
	NMEA_GETTER(differential_ref_station_id)

	void set_time_utc(const nmea::time & t) noexcept { time_utc = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_mode_indicator(const std::string & t);
	void set_number_of_satellites(uint32_t t) noexcept { number_of_satellites = t; }
	void set_hdrop(double t) noexcept { hdrop = t; }
	void set_antenna_altitude(double t) noexcept { antenna_altitude = t; }
	void set_geodial_sepration(double t) noexcept { geodial_sepration = t; }
	void set_age_of_differential_data(double t) noexcept { age_of_differential_data = t; }
	void set_differential_ref_station_id(double t) noexcept { differential_ref_station_id = t; }
};
}
}

#endif
