#ifndef MARNAV__NMEA__RMC__HPP
#define MARNAV__NMEA__RMC__HPP

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
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::RMC;
	constexpr static const char * TAG = "RMC";

	rmc();
	rmc(const rmc &) = default;
	rmc & operator=(const rmc &) = default;
	rmc(rmc &&) = default;
	rmc & operator=(rmc &&) = default;

protected:
	rmc(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<nmea::time> time_utc_;
	utils::optional<char> status_;
	utils::optional<geo::latitude> lat_;
	utils::optional<direction> lat_hem_;
	utils::optional<geo::longitude> lon_;
	utils::optional<direction> lon_hem_;
	utils::optional<double> sog_;
	utils::optional<double> heading_;
	utils::optional<nmea::date> date_;
	utils::optional<double> mag_;
	utils::optional<direction> mag_hem_;
	utils::optional<mode_indicator> mode_ind_;

public:
	decltype(time_utc_) get_time_utc() const { return time_utc_; }
	decltype(status_) get_status() const { return status_; }
	decltype(sog_) get_sog() const { return sog_; }
	decltype(heading_) get_heading() const { return heading_; }
	decltype(date_) get_date() const { return date_; }
	decltype(mag_) get_mag() const { return mag_; }
	decltype(mag_hem_) get_mag_hem() const { return mag_hem_; }
	decltype(mode_ind_) get_mode_ind() const { return mode_ind_; }

	utils::optional<geo::longitude> get_longitude() const;
	utils::optional<geo::latitude> get_latitude() const;

	void set_time_utc(const time & t) noexcept { time_utc_ = t; }
	void set_status(char t) noexcept { status_ = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_sog(double t) noexcept { sog_ = t; }
	void set_heading(double t) noexcept { heading_ = t; }
	void set_date(const nmea::date & t) noexcept { date_ = t; }
	void set_mag(double t, direction h);
	void set_mode_indicator(mode_indicator t) noexcept { mode_ind_ = t; }
};
}
}

#endif
