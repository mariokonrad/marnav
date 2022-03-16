#ifndef MARNAV_NMEA_RMA_HPP
#define MARNAV_NMEA_RMA_HPP

#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/magnetic.hpp>
#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

namespace marnav::nmea
{
/// @brief RMA - Recommended Minimum Navigation Information
///
/// @code
///        1 2       3 4        5 6   7   8   9   10  11
///        | |       | |        | |   |   |   |   |   |
/// $--RMA,A,llll.ll,a,yyyyy.yy,a,x.x,x.x,x.x,x.x,x.x,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  Blink Warning
/// 2.  Latitude
/// 3.  Latitude hemisphere
///     - N = North
///     - S = South
/// 4.  Longitude
/// 5.  Longitude hemisphere
///     - E = East
///     - W = West
/// 6.  Time Difference A, us
/// 7.  Time Difference B, us
/// 8.  Speed Over Ground, Knots
/// 9.  Track Made Good, degrees true
/// 10. Magnetic Variation, degrees
/// 11. Magnetic Variation, degrees, direction
///     - E = East
///     - W = West
///
class rma : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::RMA;
	constexpr static const char * TAG = "RMA";

	rma();
	rma(const rma &) = default;
	rma & operator=(const rma &) = default;
	rma(rma &&) = default;
	rma & operator=(rma &&) = default;

protected:
	rma(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<char> blink_warning_;
	std::optional<geo::latitude> lat_;
	std::optional<direction> lat_hem_; // latitude dir, N:north, S:south
	std::optional<geo::longitude> lon_;
	std::optional<direction> lon_hem_; // longitude dir, E:east, W:west
	std::optional<double> time_diff_a_; // time difference A in microseconds
	std::optional<double> time_diff_b_; // time difference B in microseconds
	std::optional<units::knots> sog_; // speed over ground in knots
	std::optional<double> track_; // track made good, degrees
	std::optional<double> magnetic_var_; // magnetic variation in degrees
	std::optional<direction> magnetic_var_hem_; // magnetic variation hemisphere, E:east, W:west

public:
	std::optional<char> get_blink_warning() const { return blink_warning_; }
	std::optional<double> get_time_diff_a() const { return time_diff_a_; }
	std::optional<double> get_time_diff_b() const { return time_diff_b_; }
	std::optional<units::velocity> get_sog() const;
	std::optional<double> get_track() const { return track_; }
	std::optional<magnetic> get_magnetic_var() const;

	std::optional<geo::longitude> get_lon() const;
	std::optional<geo::latitude> get_lat() const;

	void set_blink_warning(char t) noexcept { blink_warning_ = t; }
	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_time_diff_a(double t) noexcept { time_diff_a_ = t; }
	void set_time_diff_b(double t) noexcept { time_diff_b_ = t; }
	void set_sog(units::velocity t);
	void set_track(double t) noexcept { track_ = t; }
	void set_magnetic_var(const magnetic & m);
};
}

#endif
