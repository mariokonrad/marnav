#ifndef MARNAV__NMEA__GNS__HPP
#define MARNAV__NMEA__GNS__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
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
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::GNS;
	constexpr static const char * TAG = "GNS";

	gns();
	gns(const gns &) = default;
	gns & operator=(const gns &) = default;
	gns(gns &&) = default;
	gns & operator=(gns &&) = default;

protected:
	gns(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<nmea::time> time_utc;
	utils::optional<geo::latitude> lat;
	utils::optional<direction> lat_hem;
	utils::optional<geo::longitude> lon;
	utils::optional<direction> lon_hem;
	std::string mode_ind = "AA";
	utils::optional<uint32_t> number_of_satellites;
	utils::optional<double> hdrop;
	utils::optional<double> antenna_altitude; // meters
	utils::optional<double> geodial_sepration; // meters
	utils::optional<double> age_of_differential_data;
	utils::optional<double> differential_ref_station_id;

public:
	decltype(time_utc) get_time_utc() const { return time_utc; }
	decltype(mode_ind) get_mode_ind() const { return mode_ind; }
	decltype(number_of_satellites) get_number_of_satellites() const
	{
		return number_of_satellites;
	}
	decltype(hdrop) get_hdrop() const { return hdrop; }
	decltype(antenna_altitude) get_antenna_altitude() const { return antenna_altitude; }
	decltype(geodial_sepration) get_geodial_sepration() const { return geodial_sepration; }
	decltype(age_of_differential_data) get_age_of_differential_data() const
	{
		return age_of_differential_data;
	}
	decltype(differential_ref_station_id) get_differential_ref_station_id() const
	{
		return differential_ref_station_id;
	}

	utils::optional<geo::longitude> get_longitude() const;
	utils::optional<geo::latitude> get_latitude() const;

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
