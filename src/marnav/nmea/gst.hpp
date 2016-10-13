#ifndef __MARNAV__NMEA__GST__HPP__
#define __MARNAV__NMEA__GST__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(gst)

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
	MARNAV_NMEA_SENTENCE_FRIENDS(gst)

public:
	constexpr static const sentence_id ID = sentence_id::GST;
	constexpr static const char * TAG = "GST";

	gst();
	gst(const gst &) = default;
	gst & operator=(const gst &) = default;
	gst(gst &&) = default;
	gst & operator=(gst &&) = default;

protected:
	gst(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	nmea::time time_utc;
	double total_rms = 0.0;
	double dev_semi_major = 0.0;
	double dev_semi_minor = 0.0;
	double orientation = 0.0;
	double dev_lat = 0.0;
	double dev_lon = 0.0;
	double dev_alt = 0.0;

public:
	decltype(time_utc) get_time_utc() const { return time_utc; }
	decltype(total_rms) get_total_rms() const { return total_rms; }
	decltype(dev_semi_major) get_dev_semi_major() const { return dev_semi_major; }
	decltype(dev_semi_minor) get_dev_semi_minor() const { return dev_semi_minor; }
	decltype(orientation) get_orientation() const { return orientation; }
	decltype(dev_lat) get_dev_lat() const { return dev_lat; }
	decltype(dev_lon) get_dev_lon() const { return dev_lon; }
	decltype(dev_alt) get_dev_alt() const { return dev_alt; }

	void set_time_utc(const nmea::time & t) noexcept { time_utc = t; }
	void set_total_rms(double t) noexcept { total_rms = t; }
	void set_dev_semi_major(double t) noexcept { dev_semi_major = t; }
	void set_dev_semi_minor(double t) noexcept { dev_semi_minor = t; }
	void set_orientation(double t) noexcept { orientation = t; }
	void set_dev_lat(double t) noexcept { dev_lat = t; }
	void set_dev_lon(double t) noexcept { dev_lon = t; }
	void set_dev_alt(double t) noexcept { dev_alt = t; }
};
}
}

#endif
