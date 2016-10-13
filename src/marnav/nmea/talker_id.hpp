#ifndef __MARNAV__NMEA__TALKER_ID__HPP__
#define __MARNAV__NMEA__TALKER_ID__HPP__

#include <string>

namespace marnav
{
namespace nmea
{
/// This class represents a talker. Its purpose is to have a strong
/// type for talkers, instead of simply representing it with a string.
class talker
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

private:
	const char * id_;
};

talker make_talker(const std::string & s);

namespace talker_id
{
constexpr const talker none{""}; ///< used for vendor extensions
constexpr const talker autopilot_general{"AG"};
constexpr const talker autopilot_magnetic{"AP"};
constexpr const talker beidou_2{"BD"}; ///< Beidou (China)
constexpr const talker computer_calculator{"CC"}; ///< programmed calculator (obsolete)
constexpr const talker communications_dsc{"CD"}; ///< digital selective calling (DSC)
constexpr const talker computer_memory{"CM"}; ///< memory data (obsolete)
constexpr const talker communications_satellite{"CS"};
constexpr const talker communications_mfhf{"CT"}; ///< Radio-Telephone (MF/HF)
constexpr const talker communications_vhf{"CV"}; ///< Radio-Telephone (VHF)
constexpr const talker communications_scanning_receiver{"CX"}; ///< Scanning Receiver
constexpr const talker decca_navigation{"DE"}; ///< DECCA Navigation (obsolete)
constexpr const talker direction_finder{"DF"}; ///< Direction Finder
constexpr const talker electronic_chart_display{
	"EC"}; ///< Electronic Chart Display & Information System (ECDIS)
constexpr const talker emergency_position_indicating_beacon{
	"EP"}; ///< Emergency Position Indicating Beacon (EPIRB)
constexpr const talker engine_room_monitoring_systems{"ER"}; ///< Engine Room Monitoring Systems
constexpr const talker galileo{"GA"}; ///< Galileo (Europe)
constexpr const talker beidou_1{"GB"}; ///< Beidou (China)
constexpr const talker global_positioning_system{"GP"}; ///< Global Positioning System (GPS)
constexpr const talker glonass{"GL"}; ///< GLONASS
constexpr const talker mixed_gps_glonass{"GN"}; ///< Mixed GPS and GLONASS
constexpr const talker magnetic_compass{"HC"}; ///< Heading - Magnetic Compass
constexpr const talker north_seeking_gyro{"HE"}; ///< Heading - North Seeking Gyro
constexpr const talker non_north_seeking_gyro{"HN"}; ///< Heading - Non North Seeking Gyro
constexpr const talker integrated_instrumentation{"II"}; ///< Integrated Instrumentation
constexpr const talker integrated_navigation{"IN"}; ///< Integrated Navigation
constexpr const talker loran_a{"LA"}; ///< Loran A (obsolete)
constexpr const talker loran_c{"LC"}; ///< Loran C (obsolete)
constexpr const talker microwave_positioning_system{
	"MP"}; ///< Microwave Positioning System (obsolete)
constexpr const talker omega_navigation_system{"OM"}; ///< OMEGA Navigation System (obsolete)
constexpr const talker distress_alarm_system{"OS"}; ///< Distress Alarm System (obsolete)
constexpr const talker qzss_gps_augmentation_system{
	"QZ"}; ///< QZSS GPS augmentation system (Japan)
constexpr const talker radar{"RA"}; ///< RADAR and/or ARPA
constexpr const talker sounder_depth{"SD"}; ///< Sounder, Depth
constexpr const talker electronic_positioning_system{
	"SN"}; ///< Electronic Positioning System, other/general
constexpr const talker sounder_scanning{"SS"}; ///< Sounder, Scanning
constexpr const talker turn_rate_indicator{"TI"}; ///< Turn Rate Indicator
constexpr const talker transit_navigation_system{"TR"}; ///< TRANSIT Navigation System
constexpr const talker velocity_sensor_doppler{
	"VD"}; ///< Velocity Sensor, Doppler, other/general
constexpr const talker velocity_sensor_water_magnetic{
	"DM"}; ///< Velocity Sensor, Speed Log, Water, Magnetic
constexpr const talker velocity_sensor_water_mechanical{
	"VW"}; ///< Velocity Sensor, Speed Log, Water, Mechanical
constexpr const talker weather_instruments{"WI"}; ///< Weather Instruments
constexpr const talker transducer_temperature{"YC"}; ///< Transducer - Temperature (obsolete)
constexpr const talker transducer_displacement{
	"YD"}; ///< Transducer - Displacement, Angular or Linear (obsolete)
constexpr const talker transducer_frequency{"YF"}; ///< Transducer - Frequency (obsolete)
constexpr const talker transducer_level{"YL"}; ///< Transducer - Level (obsolete)
constexpr const talker transducer_pressure{"YP"}; ///< Transducer - Pressure (obsolete)
constexpr const talker transducer_flow_rate{"YR"}; ///< Transducer - Flow Rate (obsolete)
constexpr const talker transducer_tachometer{"YT"}; ///< Transducer - Tachometer (obsolete)
constexpr const talker transducer_volume{"YV"}; ///< Transducer - Volume (obsolete)
constexpr const talker transducer{"YX"}; ///< Transducer
constexpr const talker timekeeper_atomic_clock{"ZA"}; ///< Timekeeper - Atomic Clock
constexpr const talker timekeeper_chronometer{"ZC"}; ///< Timekeeper - Chronometer
constexpr const talker timekeeper_quartz{"ZQ"}; ///< Timekeeper - Quartz
constexpr const talker timekeeper_radio_update{
	"ZV"}; ///< Timekeeper - Radio Update, WWV or WWVH

// AIS
constexpr const talker ais_base_station{"AB"}; ///< NMEA 4.0 Base AIS station
constexpr const talker ais_dependent_base_station{
	"AD"}; ///< MMEA 4.0 Dependent AIS Base Station
constexpr const talker ais_mobile_station{"AI"}; ///< Mobile AIS station
constexpr const talker ais_aid_to_navigation_station{
	"AN"}; ///< NMEA 4.0 Aid to Navigation AIS station
constexpr const talker ais_receiving_station{"AR"}; ///< NMEA 4.0 AIS Receiving Station
constexpr const talker ais_limited_base_station{"AS"}; ///< NMEA 4.0 Limited Base Station
constexpr const talker ais_transmitting_station{"AT"}; ///< NMEA 4.0 AIS Transmitting Station
constexpr const talker ais_repeater_ais_station{"AX"}; ///< NMEA 4.0 Repeater AIS station
constexpr const talker ais_base_station_obsolete{
	"BS"}; ///< Base AIS station (deprecated in NMEA 4.0)
constexpr const talker ais_physical_shore_station{
	"SA"}; ///< NMEA 4.0 Physical Shore AIS Station
}
}
}

#endif
