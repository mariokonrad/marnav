#ifndef __NMEA__GST__HPP__
#define __NMEA__GST__HPP__

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

protected:
	gst(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
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
	NMEA_GETTER(time_utc)
	NMEA_GETTER(total_rms)
	NMEA_GETTER(dev_semi_major)
	NMEA_GETTER(dev_semi_minor)
	NMEA_GETTER(orientation)
	NMEA_GETTER(dev_lat)
	NMEA_GETTER(dev_lon)
	NMEA_GETTER(dev_alt)

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
