#ifndef MARNAV__NMEA__TALKER_ID__HPP
#define MARNAV__NMEA__TALKER_ID__HPP

#include <string>

namespace marnav
{
namespace nmea
{
/// Enumeration of all talkers, i.e. sources of data.
enum class talker {
	none,

	// nmea
	autopilot_general,
	autopilot_magnetic,
	beidou_2,
	computer_calculator,
	communications_dsc,
	computer_memory,
	communications_satellite,
	communications_mfhf,
	communications_vhf,
	communications_scanning_receiver,
	decca_navigation,
	direction_finder,
	electronic_chart_display,
	emergency_position_indicating_beacon,
	engine_room_monitoring_systems,
	galileo,
	beidou_1,
	global_positioning_system,
	glonass,
	mixed_gps_glonass,
	magnetic_compass,
	north_seeking_gyro,
	non_north_seeking_gyro,
	integrated_instrumentation,
	integrated_navigation,
	loran_a,
	loran_c,
	microwave_positioning_system,
	omega_navigation_system,
	distress_alarm_system,
	qzss_gps_augmentation_system,
	radar,
	sounder_depth,
	electronic_positioning_system,
	sounder_scanning,
	turn_rate_indicator,
	transit_navigation_system,
	velocity_sensor_doppler,
	velocity_sensor_water_magnetic,
	velocity_sensor_water_mechanical,
	weather_instruments,
	transducer_temperature,
	transducer_displacement,
	transducer_frequency,
	transducer_level,
	transducer_pressure,
	transducer_flow_rate,
	transducer_tachometer,
	transducer_volume,
	transducer,
	timekeeper_atomic_clock,
	timekeeper_chronometer,
	timekeeper_quartz,
	timekeeper_radio_update,

	// ais
	ais_base_station,
	ais_dependent_base_station,
	ais_mobile_station,
	ais_aid_to_navigation_station,
	ais_receiving_station,
	ais_limited_base_station,
	ais_transmitting_station,
	ais_repeater_ais_station,
	ais_base_station_obsolete,
	ais_physical_shore_station
};

using talker_id = talker; // deprecated

std::string to_string(talker t);
talker make_talker(const std::string & s);
}
}

#endif
