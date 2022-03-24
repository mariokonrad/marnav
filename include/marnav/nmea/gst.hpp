#ifndef MARNAV_NMEA_GST_HPP
#define MARNAV_NMEA_GST_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/units/units.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
/// @brief GST - GPS Pseudorange Noise Statistics
///
/// @code
///        1         2 3 4 5 6 7 8
///        |         | | | | | | |
/// $--GST,hhmmss.ss,x,x,x,x,x,x,x*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. TC time of associated GGA fix
/// 2. Total RMS standard deviation of ranges inputs to the navigation solution
/// 3. Standard deviation (meters) of semi-major axis of error ellipse
/// 4. Standard deviation (meters) of semi-minor axis of error ellipse
/// 5. Orientation of semi-major axis of error ellipse (true north degrees)
/// 6. Standard deviation (meters) of latitude error
/// 7. Standard deviation (meters) of longitude error
/// 8. Standard deviation (meters) of altitude error
///
class gst : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::GST;
	constexpr static const char * TAG = "GST";

	gst();
	gst(const gst &) = default;
	gst & operator=(const gst &) = default;
	gst(gst &&) = default;
	gst & operator=(gst &&) = default;

protected:
	gst(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	nmea::time time_utc_;
	double total_rms_ = 0.0;
	units::meters dev_semi_major_;
	units::meters dev_semi_minor_;
	double orientation_ = 0.0;
	units::meters dev_lat_;
	units::meters dev_lon_;
	units::meters dev_alt_;

public:
	nmea::time get_time_utc() const { return time_utc_; }
	double get_total_rms() const { return total_rms_; }
	units::length get_dev_semi_major() const { return {dev_semi_major_}; }
	units::length get_dev_semi_minor() const { return {dev_semi_minor_}; }
	double get_orientation() const { return orientation_; }
	units::length get_dev_lat() const { return {dev_lat_}; }
	units::length get_dev_lon() const { return {dev_lon_}; }
	units::length get_dev_alt() const { return {dev_alt_}; }

	void set_time_utc(const nmea::time & t) noexcept { time_utc_ = t; }
	void set_total_rms(double t) noexcept { total_rms_ = t; }
	void set_dev_semi_major(units::length t) noexcept
	{
		dev_semi_major_ = t.get<units::meters>();
	}
	void set_dev_semi_minor(units::length t) noexcept
	{
		dev_semi_minor_ = t.get<units::meters>();
	}
	void set_orientation(double t) noexcept { orientation_ = t; }
	void set_dev_lat(units::length t) noexcept { dev_lat_ = t.get<units::meters>(); }
	void set_dev_lon(units::length t) noexcept { dev_lon_ = t.get<units::meters>(); }
	void set_dev_alt(units::length t) noexcept { dev_alt_ = t.get<units::meters>(); }
};
}
}

#endif
