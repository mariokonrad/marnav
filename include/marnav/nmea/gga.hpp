#ifndef MARNAV__NMEA__GGA__HPP
#define MARNAV__NMEA__GGA__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/time.hpp>
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
/// @note Raytheon RN300 sends an additional value, which is invalid and not supported
///       by the sentence
///
class gga : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::GGA;
	constexpr static const char * TAG = "GGA";

	gga();
	gga(const gga &) = default;
	gga & operator=(const gga &) = default;
	gga(gga &&) = default;
	gga & operator=(gga &&) = default;

protected:
	gga(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<nmea::time> time_;
	utils::optional<geo::latitude> lat_;
	utils::optional<direction> lat_hem_; // N:north, S:south
	utils::optional<geo::longitude> lon_;
	utils::optional<direction> lon_hem_; // E:east, W:west
	utils::optional<quality> quality_indicator_;
	utils::optional<uint32_t> n_satellites_;
	utils::optional<double> hor_dilution_; // horizontal dilution of precision
	utils::optional<double> altitude_;
	utils::optional<unit::distance> altitude_unit_; // M:meter
	utils::optional<double>
		geodial_separation_; // geodial separation, sea level below the ellipsoid
	utils::optional<unit::distance> geodial_separation_unit_; // M:meter
	utils::optional<double> dgps_age_; // age of dgps data
	utils::optional<uint32_t> dgps_ref_; // dgps reference station 0000..1023

public:
	decltype(time_) get_time() const { return time_; }
	decltype(quality_indicator_) get_quality_indicator() const { return quality_indicator_; }
	decltype(n_satellites_) get_n_satellites() const { return n_satellites_; }
	decltype(hor_dilution_) get_hor_dilution() const { return hor_dilution_; }
	decltype(altitude_) get_altitude() const { return altitude_; }
	decltype(altitude_unit_) get_altitude_unit() const { return altitude_unit_; }
	decltype(geodial_separation_) get_geodial_separation() const { return geodial_separation_; }
	decltype(geodial_separation_unit_) get_geodial_separation_unit() const
	{
		return geodial_separation_unit_;
	}
	decltype(dgps_age_) get_dgps_age() const { return dgps_age_; }
	decltype(dgps_ref_) get_dgps_ref() const { return dgps_ref_; }

	utils::optional<geo::longitude> get_longitude() const;
	utils::optional<geo::latitude> get_latitude() const;

	void set_time(const nmea::time & t) noexcept { time_ = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_quality(quality t) noexcept { quality_indicator_ = t; }
	void set_n_satellites(uint32_t t) noexcept { n_satellites_ = t; }
	void set_hor_dilution(double t) noexcept { hor_dilution_ = t; }
	void set_altitude(double t) noexcept
	{
		altitude_ = t;
		altitude_unit_ = unit::distance::meter;
	}
	void set_geodial_separation(double t) noexcept
	{
		geodial_separation_ = t;
		geodial_separation_unit_ = unit::distance::meter;
	}
	void set_dgps_age(double t) noexcept { dgps_age_ = t; }
	void set_dgps_ref(uint32_t t) noexcept { dgps_ref_ = t; }
};
}
}

#endif
