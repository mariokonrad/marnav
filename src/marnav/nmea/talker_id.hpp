#ifndef MARNAV__NMEA__TALKER_ID__HPP
#define MARNAV__NMEA__TALKER_ID__HPP

#include <string>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace nmea
{
/// This class represents a talker. Its purpose is to have a strong
/// type for talkers, instead of simply representing it with a string.
class MARNAV_EXPORT talker
{
public:
	explicit constexpr talker(const char * id)
		: id_(id)
	{
	}

	talker(const talker &) = default;
	talker & operator=(const talker &) = default;

	talker(talker &&) = default;
	talker & operator=(talker &&) = default;

	const char * str() const { return id_; }

	bool operator==(const talker & t) const
	{
		return (this == &t) // same object
			|| (id_ == t.id_) // points to the same constant string
			|| (std::string{id_} == std::string{t.id_}); // most expensive test, luckily SSO
	}

	bool operator!=(const talker & t) const { return !(*this == t); }

private:
	const char * id_;
};

MARNAV_EXPORT talker make_talker(const std::string & s);

/// Namespace contains all defined talkers. For a more descriptive documentation
/// of all entries, see to_name(talker).
namespace talker_id
{
/// Number of known talkers.
constexpr std::size_t num_talkers = 65;

constexpr const talker none{""};
constexpr const talker autopilot_general{"AG"};
constexpr const talker autopilot_magnetic{"AP"};
constexpr const talker beidou_2{"BD"};
constexpr const talker computer_calculator{"CC"};
constexpr const talker communications_dsc{"CD"};
constexpr const talker computer_memory{"CM"};
constexpr const talker communications_satellite{"CS"};
constexpr const talker communications_mfhf{"CT"};
constexpr const talker communications_vhf{"CV"};
constexpr const talker communications_scanning_receiver{"CX"};
constexpr const talker decca_navigation{"DE"};
constexpr const talker direction_finder{"DF"};
constexpr const talker electronic_chart_display{"EC"};
constexpr const talker emergency_position_indicating_beacon{"EP"};
constexpr const talker engine_room_monitoring_systems{"ER"};
constexpr const talker galileo{"GA"};
constexpr const talker beidou_1{"GB"};
constexpr const talker global_positioning_system{"GP"};
constexpr const talker glonass{"GL"};
constexpr const talker mixed_gps_glonass{"GN"};
constexpr const talker magnetic_compass{"HC"};
constexpr const talker north_seeking_gyro{"HE"};
constexpr const talker non_north_seeking_gyro{"HN"};
constexpr const talker integrated_instrumentation{"II"};
constexpr const talker integrated_navigation{"IN"};
constexpr const talker loran_a{"LA"};
constexpr const talker loran_c{"LC"};
constexpr const talker microwave_positioning_system{"MP"};
constexpr const talker omega_navigation_system{"OM"};
constexpr const talker distress_alarm_system{"OS"};
constexpr const talker qzss_gps_augmentation_system{"QZ"};
constexpr const talker radar{"RA"};
constexpr const talker sounder_depth{"SD"};
constexpr const talker electronic_positioning_system{"SN"};
constexpr const talker sounder_scanning{"SS"};
constexpr const talker turn_rate_indicator{"TI"};
constexpr const talker transit_navigation_system{"TR"};
constexpr const talker velocity_sensor_doppler{"VD"};
constexpr const talker velocity_sensor_water_magnetic{"DM"};
constexpr const talker velocity_sensor_water_mechanical{"VW"};
constexpr const talker weather_instruments{"WI"};
constexpr const talker transducer_temperature{"YC"};
constexpr const talker transducer_displacement{"YD"};
constexpr const talker transducer_frequency{"YF"};
constexpr const talker transducer_level{"YL"};
constexpr const talker transducer_pressure{"YP"};
constexpr const talker transducer_flow_rate{"YR"};
constexpr const talker transducer_tachometer{"YT"};
constexpr const talker transducer_volume{"YV"};
constexpr const talker transducer{"YX"};
constexpr const talker timekeeper_atomic_clock{"ZA"};
constexpr const talker timekeeper_chronometer{"ZC"};
constexpr const talker timekeeper_quartz{"ZQ"};
constexpr const talker timekeeper_radio_update{"ZV"};

// AIS
constexpr const talker ais_base_station{"AB"};
constexpr const talker ais_dependent_base_station{"AD"};
constexpr const talker ais_mobile_station{"AI"};
constexpr const talker ais_aid_to_navigation_station{"AN"};
constexpr const talker ais_receiving_station{"AR"};
constexpr const talker ais_limited_base_station{"AS"};
constexpr const talker ais_transmitting_station{"AT"};
constexpr const talker ais_repeater_ais_station{"AX"};
constexpr const talker ais_base_station_obsolete{"BS"};
constexpr const talker ais_physical_shore_station{"SA"};
}
}
}

#endif
