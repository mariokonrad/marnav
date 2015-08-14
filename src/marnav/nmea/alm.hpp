#ifndef __NMEA__ALM__HPP__
#define __NMEA__ALM__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief ALM - GPS Almanac Data
///
/// This sentence expresses orbital data for a specified GPS satellite.
///
/// @code
///        1   2   3  4   5  6    7  8    9    10     11     12     13     14  15
///        |   |   |  |   |  |    |  |    |    |      |      |      |      |   |
/// $--ALM,x.x,x.x,xx,x.x,hh,hhhh,hh,hhhh,hhhh,hhhhhh,hhhhhh,hhhhhh,hhhhhh,hhh,hhh,*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  Total number of messages
/// 2.  Message Number
/// 3.  Satellite PRN number (01 to 32)
/// 4.  GPS Week Number
/// 5.  SV health, bits 17-24 of each almanac page
/// 6.  Eccentricity
/// 7.  Almanac Reference Time
/// 8.  Inclination Angle
/// 9.  Rate of Right Ascension
/// 10. Root of semi-major axis
/// 11. Argument of perigee
/// 12. Longitude of ascension node
/// 13. Mean anomaly
/// 14. F0 Clock Parameter
/// 15. F1 Clock Parameter
///
/// Fields 5 through 15 are dumped as raw hex.
///
/// Example:
/// <tt>$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*5B</tt>
///
class alm : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::ALM;
	constexpr static const char * TAG = "ALM";

	alm();
	alm(const alm &) = default;
	alm & operator=(const alm &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument,
		std::runtime_error);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	uint32_t number_of_messages;
	uint32_t message_number;
	uint32_t satellite_prn; // 01 .. 32
	uint32_t gps_week_number;
	uint32_t sv_health;
	uint32_t eccentricity;
	uint32_t almanac_reference_time;
	uint32_t inclination_angle;
	uint32_t rate_of_right_ascension;
	uint32_t root_of_semimajor_axis;
	uint32_t argument_of_perigee;
	uint32_t longitude_of_ascension_node;
	uint32_t mean_anomaly;
	uint32_t f0_clock_parameter;
	uint32_t f1_clock_parameter;

	void check() const throw(std::invalid_argument);

public:
	NMEA_GETTER(number_of_messages)
	NMEA_GETTER(message_number)
	NMEA_GETTER(satellite_prn)
	NMEA_GETTER(gps_week_number)
	NMEA_GETTER(sv_health)
	NMEA_GETTER(eccentricity)
	NMEA_GETTER(almanac_reference_time)
	NMEA_GETTER(inclination_angle)
	NMEA_GETTER(rate_of_right_ascension)
	NMEA_GETTER(root_of_semimajor_axis)
	NMEA_GETTER(argument_of_perigee)
	NMEA_GETTER(longitude_of_ascension_node)
	NMEA_GETTER(mean_anomaly)
	NMEA_GETTER(f0_clock_parameter)
	NMEA_GETTER(f1_clock_parameter)

	void set_number_of_messages(uint32_t t) { number_of_messages = t; }
	void set_message_number(uint32_t t) { message_number = t; }
	void set_satellite_prn(uint32_t t) { satellite_prn = t; }
	void set_gps_week_number(uint32_t t) { gps_week_number = t; }
	void set_sv_health(uint32_t t) { sv_health = t; }
	void set_eccentricity(uint32_t t) { eccentricity = t; }
	void set_almanac_reference_time(uint32_t t) { almanac_reference_time = t; }
	void set_inclination_angle(uint32_t t) { inclination_angle = t; }
	void set_rate_of_right_ascension(uint32_t t) { rate_of_right_ascension = t; }
	void set_root_of_semimajor_axis(uint32_t t) { root_of_semimajor_axis = t; }
	void set_argument_of_perigee(uint32_t t) { argument_of_perigee = t; }
	void set_longitude_of_ascension_node(uint32_t t) { longitude_of_ascension_node = t; }
	void set_mean_anomaly(uint32_t t) { mean_anomaly = t; }
	void set_f0_clock_parameter(uint32_t t) { f0_clock_parameter = t; }
	void set_f1_clock_parameter(uint32_t t) { f1_clock_parameter = t; }
};
}
}

#endif
