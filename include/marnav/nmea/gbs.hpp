#ifndef MARNAV__NMEA__GBS__HPP
#define MARNAV__NMEA__GBS__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
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
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::GBS;
	constexpr static const char * TAG = "GBS";

	gbs();
	gbs(const gbs &) = default;
	gbs & operator=(const gbs &) = default;
	gbs(gbs &&) = default;
	gbs & operator=(gbs &&) = default;

protected:
	gbs(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	nmea::time time_utc_;
	double err_lat_ = 0.0;
	double err_lon_ = 0.0;
	double err_alt_ = 0.0;
	uint32_t satellite_ = 0;
	double probability_ = 0.0;
	double bias_ = 0.0;
	double bias_dev_ = 0.0;

public:
	decltype(time_utc_) get_time_utc() const { return time_utc_; }
	decltype(err_lat_) get_err_lat() const { return err_lat_; }
	decltype(err_lon_) get_err_lon() const { return err_lon_; }
	decltype(err_alt_) get_err_alt() const { return err_alt_; }
	decltype(satellite_) get_satellite() const { return satellite_; }
	decltype(probability_) get_probability() const { return probability_; }
	decltype(bias_) get_bias() const { return bias_; }
	decltype(bias_dev_) get_bias_dev() const { return bias_dev_; }

	void set_time_utc(const nmea::time & t) noexcept { time_utc_ = t; }
	void set_err_lat(double t) noexcept { err_lat_ = t; }
	void set_err_lon(double t) noexcept { err_lon_ = t; }
	void set_err_alt(double t) noexcept { err_alt_ = t; }
	void set_satellite(uint32_t t) noexcept { satellite_ = t; }
	void set_probability(double t) noexcept { probability_ = t; }
	void set_bias(double t) noexcept { bias_ = t; }
	void set_bias_dev(double t) noexcept { bias_dev_ = t; }
};
}
}

#endif
