#ifndef __NMEA__GBS__HPP__
#define __NMEA__GBS__HPP__

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
public:
	constexpr static const sentence_id ID = sentence_id::GBS;
	constexpr static const char * TAG = "GBS";

	gbs();
	gbs(const gbs &) = default;
	gbs & operator=(const gbs &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument,
		std::runtime_error);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	nmea::time time_utc;
	double err_lat;
	double err_lon;
	double err_alt;
	uint32_t satellite;
	double probability;
	double bias;
	double bias_dev;

public:
	NMEA_GETTER(time_utc)
	NMEA_GETTER(err_lat)
	NMEA_GETTER(err_lon)
	NMEA_GETTER(err_alt)
	NMEA_GETTER(satellite)
	NMEA_GETTER(probability)
	NMEA_GETTER(bias)
	NMEA_GETTER(bias_dev)

	void set_time_utc(const nmea::time & t) { time_utc = t; }
	void set_err_lat(double t) { err_lat = t; }
	void set_err_lon(double t) { err_lon = t; }
	void set_err_alt(double t) { err_alt = t; }
	void set_satellite(uint32_t t) { satellite = t; }
	void set_probability(double t) { probability = t; }
	void set_bias(double t) { bias = t; }
	void set_bias_dev(double t) { bias_dev = t; }
};
}
}

#endif
