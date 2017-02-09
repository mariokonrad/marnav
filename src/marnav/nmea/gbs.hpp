#ifndef MARNAV__NMEA__GBS__HPP
#define MARNAV__NMEA__GBS__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(gbs)

/// @brief GBS - GPS Satellite Fault Detection
///
/// @code
///        1         2   3   4   5   6   7   8
///        |         |   |   |   |   |   |   |
/// $--GBS,hhmmss.ss,x.x,x.x,x.x,x.x,x.x,x.x,x.x*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. UTC time of the GGA or GNS fix associated with this sentence
/// 2. Expected error in latitude (meters)
/// 3. Expected error in longitude (meters)
/// 4. Expected error in altitude (meters)
/// 5. PRN of most likely failed satellite
/// 6. Probability of missed detection for most likely failed satellite
/// 7. Estimate of bias in meters on most likely failed satellite
/// 8. Standard deviation of bias estimate
///
/// @note The 8-field version is in NMEA 3.0
///
class gbs : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(gbs)

public:
	constexpr static const sentence_id ID = sentence_id::GBS;
	constexpr static const char * TAG = "GBS";

	gbs();
	gbs(const gbs &) = default;
	gbs & operator=(const gbs &) = default;
	gbs(gbs &&) = default;
	gbs & operator=(gbs &&) = default;

protected:
	gbs(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	nmea::time time_utc;
	double err_lat = 0.0;
	double err_lon = 0.0;
	double err_alt = 0.0;
	uint32_t satellite = 0;
	double probability = 0.0;
	double bias = 0.0;
	double bias_dev = 0.0;

public:
	decltype(time_utc) get_time_utc() const { return time_utc; }
	decltype(err_lat) get_err_lat() const { return err_lat; }
	decltype(err_lon) get_err_lon() const { return err_lon; }
	decltype(err_alt) get_err_alt() const { return err_alt; }
	decltype(satellite) get_satellite() const { return satellite; }
	decltype(probability) get_probability() const { return probability; }
	decltype(bias) get_bias() const { return bias; }
	decltype(bias_dev) get_bias_dev() const { return bias_dev; }

	void set_time_utc(const nmea::time & t) noexcept { time_utc = t; }
	void set_err_lat(double t) noexcept { err_lat = t; }
	void set_err_lon(double t) noexcept { err_lon = t; }
	void set_err_alt(double t) noexcept { err_alt = t; }
	void set_satellite(uint32_t t) noexcept { satellite = t; }
	void set_probability(double t) noexcept { probability = t; }
	void set_bias(double t) noexcept { bias = t; }
	void set_bias_dev(double t) noexcept { bias_dev = t; }
};
}
}

#endif
