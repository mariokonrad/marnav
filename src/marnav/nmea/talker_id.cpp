#include <marnav/nmea/talker_id.hpp>
#include <algorithm>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
namespace detail
{
static constexpr const struct entry {
	talker t;
	const char * id;
} entries[] = {
	// clang-format off
	{talker::none,                                 ""  },
	{talker::autopilot_general,                    "AG"},
	{talker::autopilot_magnetic,                   "AP"},
	{talker::beidou_2,                             "BD"},
	{talker::computer_calculator,                  "CC"},
	{talker::communications_dsc,                   "CD"},
	{talker::computer_memory,                      "CM"},
	{talker::communications_satellite,             "CS"},
	{talker::communications_mfhf,                  "CT"},
	{talker::communications_vhf,                   "CV"},
	{talker::communications_scanning_receiver,     "CX"},
	{talker::decca_navigation,                     "DE"},
	{talker::direction_finder,                     "DF"},
	{talker::electronic_chart_display,             "EC"},
	{talker::emergency_position_indicating_beacon, "EP"},
	{talker::engine_room_monitoring_systems,       "ER"},
	{talker::galileo,                              "GA"},
	{talker::beidou_1,                             "GB"},
	{talker::global_positioning_system,            "GP"},
	{talker::glonass,                              "GL"},
	{talker::mixed_gps_glonass,                    "GN"},
	{talker::magnetic_compass,                     "HC"},
	{talker::north_seeking_gyro,                   "HE"},
	{talker::non_north_seeking_gyro,               "HN"},
	{talker::integrated_instrumentation,           "II"},
	{talker::integrated_navigation,                "IN"},
	{talker::loran_a,                              "LA"},
	{talker::loran_c,                              "LC"},
	{talker::microwave_positioning_system,         "MP"},
	{talker::omega_navigation_system,              "OM"},
	{talker::distress_alarm_system,                "OS"},
	{talker::qzss_gps_augmentation_system,         "QZ"},
	{talker::radar,                                "RA"},
	{talker::sounder_depth,                        "SD"},
	{talker::electronic_positioning_system,        "SN"},
	{talker::sounder_scanning,                     "SS"},
	{talker::turn_rate_indicator,                  "TI"},
	{talker::transit_navigation_system,            "TR"},
	{talker::velocity_sensor_doppler,              "VD"},
	{talker::velocity_sensor_water_magnetic,       "DM"},
	{talker::velocity_sensor_water_mechanical,     "VW"},
	{talker::weather_instruments,                  "WI"},
	{talker::transducer_temperature,               "YC"},
	{talker::transducer_displacement,              "YD"},
	{talker::transducer_frequency,                 "YF"},
	{talker::transducer_level,                     "YL"},
	{talker::transducer_pressure,                  "YP"},
	{talker::transducer_flow_rate,                 "YR"},
	{talker::transducer_tachometer,                "YT"},
	{talker::transducer_volume,                    "YV"},
	{talker::transducer,                           "YX"},
	{talker::timekeeper_atomic_clock,              "ZA"},
	{talker::timekeeper_chronometer,               "ZC"},
	{talker::timekeeper_quartz,                    "ZQ"},
	{talker::timekeeper_radio_update,              "ZV"},
	{talker::ais_base_station,                     "AB"},
	{talker::ais_dependent_base_station,           "AD"},
	{talker::ais_mobile_station,                   "AI"},
	{talker::ais_aid_to_navigation_station,        "AN"},
	{talker::ais_receiving_station,                "AR"},
	{talker::ais_limited_base_station,             "AS"},
	{talker::ais_transmitting_station,             "AT"},
	{talker::ais_repeater_ais_station,             "AX"},
	{talker::ais_base_station_obsolete,            "BS"},
	{talker::ais_physical_shore_station,           "SA"},
	// clang-format on
};
}

std::string to_string(talker t)
{
	auto i = std::find_if(std::begin(detail::entries), std::end(detail::entries),
		[&](const detail::entry & e) { return t == e.t; });
	return (i == std::end(detail::entries)) ? "-" : i->id;
}

/// Returns a talker from the specified string.
///
/// @param[in] s The string to create a talker from. This must be
///   of size 2 and represent a known talker.
/// @return The corresponding talker or talker::none if the specified
///   string does not represent a known talker.
/// @exception invalid_argument This exception is thrown if the specified
///   string is invalid (e.g. wrong size).
///
talker make_talker(const std::string & s)
{
	if (s.size() != 2)
		throw std::invalid_argument{"invalid talker in make_talker: " + s};
	auto i = std::find_if(std::begin(detail::entries), std::end(detail::entries),
		[&](const detail::entry & e) { return s == e.id; });
	return (i == std::end(detail::entries)) ? talker::none : i->t;
}
}
}
