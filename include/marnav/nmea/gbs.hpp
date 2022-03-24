#ifndef MARNAV_NMEA_GBS_HPP
#define MARNAV_NMEA_GBS_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/units/units.hpp>
#include <optional>

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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	nmea::time time_utc_;
	units::meters err_lat_;
	units::meters err_lon_;
	units::meters err_alt_;
	uint32_t satellite_ = 0;
	double probability_ = 0.0;
	units::meters bias_;
	double bias_dev_ = 0.0;

public:
	nmea::time get_time_utc() const { return time_utc_; }
	units::length get_err_lat() const { return {err_lat_}; }
	units::length get_err_lon() const { return {err_lon_}; }
	units::length get_err_alt() const { return {err_alt_}; }
	uint32_t get_satellite() const { return satellite_; }
	double get_probability() const { return probability_; }
	units::length get_bias() const { return {bias_}; }
	double get_bias_dev() const { return bias_dev_; }

	void set_time_utc(const nmea::time & t) noexcept { time_utc_ = t; }
	void set_err_lat(units::length t) noexcept { err_lat_ = t.get<units::meters>(); }
	void set_err_lon(units::length t) noexcept { err_lon_ = t.get<units::meters>(); }
	void set_err_alt(units::length t) noexcept { err_alt_ = t.get<units::meters>(); }
	void set_satellite(uint32_t t) noexcept { satellite_ = t; }
	void set_probability(double t) noexcept { probability_ = t; }
	void set_bias(units::length t) noexcept { bias_ = t.get<units::meters>(); }
	void set_bias_dev(double t) noexcept { bias_dev_ = t; }
};
}
}

#endif
