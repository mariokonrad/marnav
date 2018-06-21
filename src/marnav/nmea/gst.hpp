#ifndef MARNAV__NMEA__GST__HPP
#define MARNAV__NMEA__GST__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/utils/optional.hpp>

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
	virtual void append_data_to(std::string &) const override;

private:
	nmea::time time_utc_;
	double total_rms_ = 0.0;
	double dev_semi_major_ = 0.0;
	double dev_semi_minor_ = 0.0;
	double orientation_ = 0.0;
	double dev_lat_ = 0.0;
	double dev_lon_ = 0.0;
	double dev_alt_ = 0.0;

public:
	decltype(time_utc_) get_time_utc() const { return time_utc_; }
	decltype(total_rms_) get_total_rms() const { return total_rms_; }
	decltype(dev_semi_major_) get_dev_semi_major() const { return dev_semi_major_; }
	decltype(dev_semi_minor_) get_dev_semi_minor() const { return dev_semi_minor_; }
	decltype(orientation_) get_orientation() const { return orientation_; }
	decltype(dev_lat_) get_dev_lat() const { return dev_lat_; }
	decltype(dev_lon_) get_dev_lon() const { return dev_lon_; }
	decltype(dev_alt_) get_dev_alt() const { return dev_alt_; }

	void set_time_utc(const nmea::time & t) noexcept { time_utc_ = t; }
	void set_total_rms(double t) noexcept { total_rms_ = t; }
	void set_dev_semi_major(double t) noexcept { dev_semi_major_ = t; }
	void set_dev_semi_minor(double t) noexcept { dev_semi_minor_ = t; }
	void set_orientation(double t) noexcept { orientation_ = t; }
	void set_dev_lat(double t) noexcept { dev_lat_ = t; }
	void set_dev_lon(double t) noexcept { dev_lon_ = t; }
	void set_dev_alt(double t) noexcept { dev_alt_ = t; }
};
}
}

#endif
