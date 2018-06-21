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
	constexpr static sentence_id ID = sentence_id::GNS;
	constexpr static const char * TAG = "GNS";

	gns();
	gns(const gns &) = default;
	gns & operator=(const gns &) = default;
	gns(gns &&) = default;
	gns & operator=(gns &&) = default;

protected:
	gns(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<nmea::time> time_utc_;
	utils::optional<geo::latitude> lat_;
	utils::optional<direction> lat_hem_;
	utils::optional<geo::longitude> lon_;
	utils::optional<direction> lon_hem_;
	std::string mode_ind_ = "AA";
	utils::optional<uint32_t> number_of_satellites_;
	utils::optional<double> hdrop_;
	utils::optional<double> antenna_altitude_; // meters
	utils::optional<double> geodial_sepration_; // meters
	utils::optional<double> age_of_differential_data_;
	utils::optional<double> differential_ref_station_id_;

public:
	decltype(time_utc_) get_time_utc() const { return time_utc_; }
	decltype(mode_ind_) get_mode_ind() const { return mode_ind_; }
	decltype(number_of_satellites_) get_number_of_satellites() const
	{
		return number_of_satellites_;
	}
	decltype(hdrop_) get_hdrop() const { return hdrop_; }
	decltype(antenna_altitude_) get_antenna_altitude() const { return antenna_altitude_; }
	decltype(geodial_sepration_) get_geodial_sepration() const { return geodial_sepration_; }
	decltype(age_of_differential_data_) get_age_of_differential_data() const
	{
		return age_of_differential_data_;
	}
	decltype(differential_ref_station_id_) get_differential_ref_station_id() const
	{
		return differential_ref_station_id_;
	}

	utils::optional<geo::longitude> get_longitude() const;
	utils::optional<geo::latitude> get_latitude() const;

	void set_time_utc(const nmea::time & t) noexcept { time_utc_ = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_mode_indicator(const std::string & t);
	void set_number_of_satellites(uint32_t t) noexcept { number_of_satellites_ = t; }
	void set_hdrop(double t) noexcept { hdrop_ = t; }
	void set_antenna_altitude(double t) noexcept { antenna_altitude_ = t; }
	void set_geodial_sepration(double t) noexcept { geodial_sepration_ = t; }
	void set_age_of_differential_data(double t) noexcept { age_of_differential_data_ = t; }
	void set_differential_ref_station_id(double t) noexcept
	{
		differential_ref_station_id_ = t;
	}
};
}
}

#endif
