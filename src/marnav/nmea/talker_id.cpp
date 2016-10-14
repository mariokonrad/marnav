#include "talker_id.hpp"
#include <algorithm>
#include <array>
#include <string>

namespace marnav
{
namespace nmea
{
/// Makes a talker object from the specified string.
///
/// @param[in] s The string to create a talker from. This must be
///   of size 2 and represent a known talker.
/// @return The corresponding talker or talker_id::none if the specified
///   string does not represent a known talker.
/// @exception runtime_error This exception is thrown if the specified
///   string is invalid (e.g. wrong size).
///
talker make_talker(const std::string & s)
{
	// clang-format off

	// this container contains all known talkers, the intention is to
	// keep the most used at the front. this is probably an ongoing
	// process to optimize it.
	static constexpr const std::array<talker, talker_id::num_talkers> talkers = {{
		talker_id::none,
		talker_id::integrated_instrumentation,
		talker_id::global_positioning_system,
		talker_id::ais_base_station,
		talker_id::ais_dependent_base_station,
		talker_id::ais_mobile_station,
		talker_id::ais_aid_to_navigation_station,
		talker_id::ais_receiving_station,
		talker_id::ais_limited_base_station,
		talker_id::ais_transmitting_station,
		talker_id::ais_repeater_ais_station,
		talker_id::ais_base_station_obsolete,
		talker_id::ais_physical_shore_station,
		talker_id::autopilot_general,
		talker_id::autopilot_magnetic,
		talker_id::galileo,
		talker_id::glonass,
		talker_id::beidou_1,
		talker_id::beidou_2,
		talker_id::computer_calculator,
		talker_id::communications_dsc,
		talker_id::computer_memory,
		talker_id::communications_satellite,
		talker_id::communications_mfhf,
		talker_id::communications_vhf,
		talker_id::communications_scanning_receiver,
		talker_id::decca_navigation,
		talker_id::direction_finder,
		talker_id::electronic_chart_display,
		talker_id::emergency_position_indicating_beacon,
		talker_id::engine_room_monitoring_systems,
		talker_id::mixed_gps_glonass,
		talker_id::magnetic_compass,
		talker_id::north_seeking_gyro,
		talker_id::non_north_seeking_gyro,
		talker_id::integrated_navigation,
		talker_id::loran_a, talker_id::loran_c,
		talker_id::microwave_positioning_system,
		talker_id::omega_navigation_system,
		talker_id::distress_alarm_system,
		talker_id::qzss_gps_augmentation_system,
		talker_id::radar,
		talker_id::sounder_depth,
		talker_id::electronic_positioning_system,
		talker_id::sounder_scanning,
		talker_id::turn_rate_indicator,
		talker_id::transit_navigation_system,
		talker_id::velocity_sensor_doppler,
		talker_id::velocity_sensor_water_magnetic,
		talker_id::velocity_sensor_water_mechanical,
		talker_id::weather_instruments,
		talker_id::transducer_temperature,
		talker_id::transducer_displacement,
		talker_id::transducer_frequency,
		talker_id::transducer_level,
		talker_id::transducer_pressure,
		talker_id::transducer_flow_rate,
		talker_id::transducer_tachometer,
		talker_id::transducer_volume,
		talker_id::transducer,
		talker_id::timekeeper_atomic_clock,
		talker_id::timekeeper_chronometer,
		talker_id::timekeeper_quartz,
		talker_id::timekeeper_radio_update
	}};
	// clang-format on

	if (s.size() != 2)
		throw std::invalid_argument{"invalid talker in make_talker: " + s};
	const auto i = std::find_if(
		std::begin(talkers), std::end(talkers), [&](const talker & t) { return s == t.str(); });
	return (i == std::end(talkers)) ? talker_id::none : *i;
}
}
}
