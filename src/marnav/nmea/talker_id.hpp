#ifndef __MARNAV__NMEA__TALKER_ID__HPP__
#define __MARNAV__NMEA__TALKER_ID__HPP__

namespace marnav
{
namespace nmea
{
/// Contains all talker IDs as strings.
namespace talker_id
{
constexpr const char * none = ""; ///< used for vendor extensions
constexpr const char * autopilot_general = "AG";
constexpr const char * autopilot_magnetic = "AP";
constexpr const char * computer_calculator = "CC"; ///< programmed calculator (obsolete)
constexpr const char * communications_dsc = "CD"; ///< digital selective calling (DSC)
constexpr const char * computer_memory = "CM"; ///< memory data (obsolete)
constexpr const char * communications_satellite = "CS";
constexpr const char * communications_mfhf = "CT"; ///< Radio-Telephone (MF/HF)
constexpr const char * communications_vhf = "CV"; ///< Radio-Telephone (VHF)
constexpr const char * communications_scanning_receiver = "CX"; ///< Scanning Receiver
constexpr const char * decca_navigation = "DE"; ///< DECCA Navigation (obsolete)
constexpr const char * direction_finder = "DF"; ///< Direction Finder
constexpr const char * electronic_chart_display
	= "EC"; ///< Electronic Chart Display & Information System (ECDIS)
constexpr const char * emergency_position_indicating_beacon
	= "EP"; ///< Emergency Position Indicating Beacon (EPIRB)
constexpr const char * engine_room_monitoring_systems
	= "ER"; ///< Engine Room Monitoring Systems
constexpr const char * global_positioning_system = "GP"; ///< Global Positioning System (GPS)
constexpr const char * magnetic_compass = "HC"; ///< Heading - Magnetic Compass
constexpr const char * north_seeking_gyro = "HE"; ///< Heading - North Seeking Gyro
constexpr const char * non_north_seeking_gyro = "HN"; ///< Heading - Non North Seeking Gyro
constexpr const char * integrated_instrumentation = "II"; ///< Integrated Instrumentation
constexpr const char * integrated_navigation = "IN"; ///< Integrated Navigation
constexpr const char * loran_a = "LA"; ///< Loran A (obsolete)
constexpr const char * loran_c = "LC"; ///< Loran C (obsolete)
constexpr const char * microwave_positioning_system
	= "MP"; ///< Microwave Positioning System (obsolete)
constexpr const char * omega_navigation_system = "OM"; ///< OMEGA Navigation System (obsolete)
constexpr const char * distress_alarm_system = "OS"; ///< Distress Alarm System (obsolete)
constexpr const char * radar = "RA"; ///< RADAR and/or ARPA
constexpr const char * sounder_depth = "SD"; ///< Sounder, Depth
constexpr const char * electronic_positioning_system
	= "SN"; ///< Electronic Positioning System, other/general
constexpr const char * sounder_scanning = "SS"; ///< Sounder, Scanning
constexpr const char * turn_rate_indicator = "TI"; ///< Turn Rate Indicator
constexpr const char * transit_navigation_system = "TR"; ///< TRANSIT Navigation System
constexpr const char * velocity_sensor_doppler
	= "VD"; ///< Velocity Sensor, Doppler, other/general
constexpr const char * velocity_sensor_water_magnetic
	= "DM"; ///< Velocity Sensor, Speed Log, Water, Magnetic
constexpr const char * velocity_sensor_water_mechanical
	= "VW"; ///< Velocity Sensor, Speed Log, Water, Mechanical
constexpr const char * weather_instruments = "WI"; ///< Weather Instruments
constexpr const char * transducer_temperature = "YC"; ///< Transducer - Temperature (obsolete)
constexpr const char * transducer_displacement
	= "YD"; ///< Transducer - Displacement, Angular or Linear (obsolete)
constexpr const char * transducer_frequency = "YF"; ///< Transducer - Frequency (obsolete)
constexpr const char * transducer_level = "YL"; ///< Transducer - Level (obsolete)
constexpr const char * transducer_pressure = "YP"; ///< Transducer - Pressure (obsolete)
constexpr const char * transducer_flow_rate = "YR"; ///< Transducer - Flow Rate (obsolete)
constexpr const char * transducer_tachometer = "YT"; ///< Transducer - Tachometer (obsolete)
constexpr const char * transducer_volume = "YV"; ///< Transducer - Volume (obsolete)
constexpr const char * transducer = "YX"; ///< Transducer
constexpr const char * timekeeper_atomic_clock = "ZA"; ///< Timekeeper - Atomic Clock
constexpr const char * timekeeper_chronometer = "ZC"; ///< Timekeeper - Chronometer
constexpr const char * timekeeper_quartz = "ZQ"; ///< Timekeeper - Quartz
constexpr const char * timekeeper_radio_update
	= "ZV"; ///< Timekeeper - Radio Update, WWV or WWVH

// AIS
constexpr const char * ais_base_station = "AB"; ///< NMEA 4.0 Base AIS station
constexpr const char * ais_dependent_base_station
	= "AD"; ///< MMEA 4.0 Dependent AIS Base Station
constexpr const char * ais_mobile_station = "AI"; ///< Mobile AIS station
constexpr const char * ais_aid_to_navigation_station
	= "AN"; ///< NMEA 4.0 Aid to Navigation AIS station
constexpr const char * ais_receiving_station = "AR"; ///< NMEA 4.0 AIS Receiving Station
constexpr const char * ais_limited_base_station = "AS"; ///< NMEA 4.0 Limited Base Station
constexpr const char * ais_transmitting_station = "AT"; ///< NMEA 4.0 AIS Transmitting Station
constexpr const char * ais_repeater_ais_station = "AX"; ///< NMEA 4.0 Repeater AIS station
constexpr const char * ais_base_station_obsolete
	= "BS"; ///< Base AIS station (deprecated in NMEA 4.0)
constexpr const char * ais_physical_shore_station
	= "SA"; ///< NMEA 4.0 Physical Shore AIS Station
}
}
}

#endif
