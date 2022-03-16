#ifndef MARNAV_NMEA_RMC_HPP
#define MARNAV_NMEA_RMC_HPP

#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/date.hpp>
#include <marnav/nmea/magnetic.hpp>
#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/units/units.hpp>
#include <optional>

namespace marnav::nmea
{
/// @brief RMC - Recommended Minimum Navigation Information
///
/// @code
///                                                            12
///        1         2 3       4 5        6 7   8   9    10  11|
///        |         | |       | |        | |   |   |    |   | |
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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<nmea::time> time_utc_;
	std::optional<char> status_;
	std::optional<geo::latitude> lat_;
	std::optional<direction> lat_hem_;
	std::optional<geo::longitude> lon_;
	std::optional<direction> lon_hem_;
	std::optional<units::knots> sog_;
	std::optional<double> heading_;
	std::optional<nmea::date> date_;
	std::optional<double> mag_;
	std::optional<direction> mag_hem_;
	std::optional<mode_indicator> mode_ind_;

public:
	std::optional<nmea::time> get_time_utc() const { return time_utc_; }
	std::optional<char> get_status() const { return status_; }
	std::optional<units::velocity> get_sog() const;
	std::optional<double> get_heading() const { return heading_; }
	std::optional<nmea::date> get_date() const { return date_; }
	std::optional<magnetic> get_mag() const;
	std::optional<mode_indicator> get_mode_ind() const { return mode_ind_; }

	std::optional<geo::longitude> get_lon() const;
	std::optional<geo::latitude> get_lat() const;

	void set_time_utc(const time & t) noexcept { time_utc_ = t; }
	void set_status(char t) noexcept { status_ = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_sog(units::velocity t);
	void set_heading(double t) noexcept { heading_ = t; }
	void set_date(const nmea::date & t) noexcept { date_ = t; }
	void set_mag(const magnetic & m);
	void set_mode_indicator(mode_indicator t) noexcept { mode_ind_ = t; }
};
}

#endif
