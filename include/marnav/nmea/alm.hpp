#ifndef MARNAV__NMEA__ALM__HPP
#define MARNAV__NMEA__ALM__HPP

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
/// <tt>$GPALM,1,1,15,1159,00,441d,4e,16be,fd5e,a10c9f,4a2da4,686e81,58cbe1,0a4,001*77</tt>
///
class alm : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::ALM;
	constexpr static const char * TAG = "ALM";

	alm();
	alm(const alm &) = default;
	alm & operator=(const alm &) = default;
	alm(alm &&) = default;
	alm & operator=(alm &&) = default;

protected:
	alm(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	uint32_t number_of_messages_ = 0;
	uint32_t message_number_ = 0;
	uint32_t satellite_prn_ = 0; // 01 .. 32
	uint32_t gps_week_number_ = 0;
	uint32_t sv_health_ = 0;
	uint32_t eccentricity_ = 0;
	uint32_t almanac_reference_time_ = 0;
	uint32_t inclination_angle_ = 0;
	uint32_t rate_of_right_ascension_ = 0;
	uint32_t root_of_semimajor_axis_ = 0;
	uint32_t argument_of_perigee_ = 0;
	uint32_t longitude_of_ascension_node_ = 0;
	uint32_t mean_anomaly_ = 0;
	uint32_t f0_clock_parameter_ = 0;
	uint32_t f1_clock_parameter_ = 0;

	void check() const;

public:
	decltype(number_of_messages_) get_number_of_messages() const { return number_of_messages_; }
	decltype(message_number_) get_message_number() const { return message_number_; }
	decltype(satellite_prn_) get_satellite_prn() const { return satellite_prn_; }
	decltype(gps_week_number_) get_gps_week_number() const { return gps_week_number_; }
	decltype(sv_health_) get_sv_health() const { return sv_health_; }
	decltype(eccentricity_) get_eccentricity() const { return eccentricity_; }
	decltype(almanac_reference_time_) get_almanac_reference_time() const
	{
		return almanac_reference_time_;
	}
	decltype(inclination_angle_) get_inclination_angle() const { return inclination_angle_; }
	decltype(rate_of_right_ascension_) get_rate_of_right_ascension() const
	{
		return rate_of_right_ascension_;
	}
	decltype(root_of_semimajor_axis_) get_root_of_semimajor_axis() const
	{
		return root_of_semimajor_axis_;
	}
	decltype(argument_of_perigee_) get_argument_of_perigee() const
	{
		return argument_of_perigee_;
	}
	decltype(longitude_of_ascension_node_) get_longitude_of_ascension_node() const
	{
		return longitude_of_ascension_node_;
	}
	decltype(mean_anomaly_) get_mean_anomaly() const { return mean_anomaly_; }
	decltype(f0_clock_parameter_) get_f0_clock_parameter() const { return f0_clock_parameter_; }
	decltype(f1_clock_parameter_) get_f1_clock_parameter() const { return f1_clock_parameter_; }

	void set_number_of_messages(uint32_t t) noexcept { number_of_messages_ = t; }
	void set_message_number(uint32_t t) noexcept { message_number_ = t; }
	void set_satellite_prn(uint32_t t) noexcept { satellite_prn_ = t; }
	void set_gps_week_number(uint32_t t) noexcept { gps_week_number_ = t; }
	void set_sv_health(uint32_t t) noexcept { sv_health_ = t; }
	void set_eccentricity(uint32_t t) noexcept { eccentricity_ = t; }
	void set_almanac_reference_time(uint32_t t) noexcept { almanac_reference_time_ = t; }
	void set_inclination_angle(uint32_t t) noexcept { inclination_angle_ = t; }
	void set_rate_of_right_ascension(uint32_t t) noexcept { rate_of_right_ascension_ = t; }
	void set_root_of_semimajor_axis(uint32_t t) noexcept { root_of_semimajor_axis_ = t; }
	void set_argument_of_perigee(uint32_t t) noexcept { argument_of_perigee_ = t; }
	void set_longitude_of_ascension_node(uint32_t t) noexcept
	{
		longitude_of_ascension_node_ = t;
	}
	void set_mean_anomaly(uint32_t t) noexcept { mean_anomaly_ = t; }
	void set_f0_clock_parameter(uint32_t t) noexcept { f0_clock_parameter_ = t; }
	void set_f1_clock_parameter(uint32_t t) noexcept { f1_clock_parameter_ = t; }
};
}
}

#endif
