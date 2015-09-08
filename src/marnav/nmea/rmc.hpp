#ifndef __NMEA__RMC__HPP__
#define __NMEA__RMC__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/date.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief RMC - Recommended Minimum Navigation Information
///
/// @code
///                                                            12
///        1         2 3       4 5        6  7   8   9    10 11|
///        |         | |       | |        |  |   |   |    |  | |
/// $--RMC,hhmmss.ss,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,xxxx,x.x,a,m,*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  UTC Time
/// 2.  Status, V=Navigation receiver warning A=Valid
/// 3.  Latitude
/// 4.  Latitude hemisphere
///     - N = North
///     - S = South
/// 5.  Longitude
/// 6.  Longitude hemisphere
///     - E = East
///     - W = West
/// 7.  Speed over ground, knots
/// 8.  Track made good, degrees true
/// 9.  Date, ddmmyy
/// 10. Magnetic Variation, degrees
/// 11. Magnetic Variation, degrees, direction
///     - E = East
///     - W = West
/// 12. FAA mode indicator (NMEA 2.3 and later)
///
/// A status of V means the GPS has a valid fix that is below an internal quality
/// threshold, e.g. because the dilution of precision is too high or an elevation
/// mask test failed.
///
class rmc : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::RMC;
	constexpr static const char * TAG = "RMC";

	rmc();
	rmc(const rmc &) = default;
	rmc & operator=(const rmc &) = default;

	static std::unique_ptr<sentence> parse(
		const std::string & talker, const std::vector<std::string> & fields);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<nmea::time> time_utc;
	utils::optional<char> status;
	utils::optional<geo::latitude> lat;
	utils::optional<direction> lat_hem;
	utils::optional<geo::longitude> lon;
	utils::optional<direction> lon_hem;
	utils::optional<double> sog;
	utils::optional<double> heading;
	utils::optional<nmea::date> date;
	utils::optional<double> mag;
	utils::optional<direction> mag_hem;
	utils::optional<positioning_system_mode_indicator> mode_indicator;

public:
	NMEA_GETTER(time_utc)
	NMEA_GETTER(status)
	NMEA_GETTER(lat)
	NMEA_GETTER(lat_hem)
	NMEA_GETTER(lon)
	NMEA_GETTER(lon_hem)
	NMEA_GETTER(sog)
	NMEA_GETTER(heading)
	NMEA_GETTER(date)
	NMEA_GETTER(mag)
	NMEA_GETTER(mag_hem)
	NMEA_GETTER(mode_indicator)

	void set_time_utc(const time & t) noexcept { time_utc = t; }
	void set_status(char t) noexcept { status = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_sog(double t) noexcept { sog = t; }
	void set_heading(double t) noexcept { heading = t; }
	void set_date(const nmea::date & t) noexcept { date = t; }
	void set_mag(double t, direction h);
	void set_mode_indicator(positioning_system_mode_indicator t) noexcept
	{
		mode_indicator = t;
	}
};
}
}

#endif
