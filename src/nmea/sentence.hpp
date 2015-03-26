#ifndef __NMEA__SENTENCE__HPP__
#define __NMEA__SENTENCE__HPP__

#include <functional>
#include <memory>
#include <vector>
#include <string>
#include "constants.hpp"

namespace nmea
{

/// Enumeration of NMEA-0183 sentence IDs.
///
/// @note Not all are currently supported.
enum class sentence_id : uint32_t {
	NONE = 0,

	// standard sentences

	AAM, ///< Waypoint Arrival Alarm
	ALM, ///< GPS Almanac Data
	APA, ///< Autopilot Sentence "A"
	APB, ///< Autopilot Sentence "B"
	BOD, ///< Bearing - Waypoint to Waypoint
	BWC, ///< Bearing & Distance to Waypoint - Geat Circle
	BWR, ///< Bearing and Distance to Waypoint - Rhumb Line
	BWW, ///< Bearing - Waypoint to Waypoint
	DBK, ///< Depth Below Keel
	DBS, ///< Depth Below Surface
	DBT, ///< Depth below transducer (II)
	DCN, ///< Decca Position
	DPT, ///< Depth of Water
	DTM, ///< Datum Reference
	FSI, ///< Frequency Set Information
	GBS, ///< GPS Satellite Fault Detection
	GGA, ///< Global Positioning System Fix Data
	GLC, ///< Geographic Position, Loran-C
	GLL, ///< Geographic Position - Latitude/Longitude
	GNS, ///< Fix data
	GRS, ///< GPS Range Residuals
	GST, ///< GPS Pseudorange Noise Statistics
	GSA, ///< GPS DOP and active satellites
	GSV, ///< Satellites in view
	GTD, ///< Geographic Location in Time Differences
	GXA, ///< TRANSIT Position - Latitude/Longitude
	HDG, ///< Heading - Deviation & Variation (vendor extension)
	HDM, ///< Heading - Magnetic
	HDT, ///< Heading - True
	HFB, ///< Trawl Headrope to Footrope and Bottom
	HSC, ///< Heading Steering Command
	ITS, ///< Trawl Door Spread 2 Distance
	LCD, ///< Loran-C Signal Data
	MSK, ///< Control for a Beacon Receiver
	MSS, ///< Beacon Receiver Status
	MTW, ///< Mean Temperature of Water (II)
	MWV, ///< Wind Speed and Angle (II)
	OLN, ///< Omega Lane Numbers
	OSD, ///< Own Ship Data
	R00, ///< Waypoints in active route
	RMA, ///< Recommended Minimum Navigation Information
	RMB, ///< Recommended Minimum Navigation Information
	RMC, ///< Recommended Minimum Navigation Information
	ROT, ///< Rate Of Turn
	RPM, ///< Revolutions
	RSA, ///< Rudder Sensor Angle
	RSD, ///< RADAR System Data
	RTE, ///< Routes
	SFI, ///< Scanning Frequency Information
	STN, ///< Multiple Data ID
	TDS, ///< Trawl Door Spread Distance
	TFI, ///< Trawl Filling Indicator
	TPC, ///< Trawl Position Cartesian Coordinates
	TPR, ///< Trawl Position Relative Vessel
	TPT, ///< Trawl Position True
	TRF, ///< TRANSIT Fix Data
	TTM, ///< Tracked Target Message
	VBW, ///< Dual Ground/Water Speed
	VDR, ///< Set and Drift
	VHW, ///< Water speed and heading (II)
	VLW, ///< Distance Traveled through Water (II)
	VPW, ///< Speed - Measured Parallel to Wind
	VTG, ///< Track made good and Ground speed
	VWR, ///< Relative Wind Speed and Angle (II)
	WCV, ///< Waypoint Closure Velocity
	WNC, ///< Distance - Waypoint to Waypoint
	WPL, ///< Waypoint Location
	XDR, ///< Transducer Measurement
	XTE, ///< Cross-Track Error, Measured
	XTR, ///< Cross Track Error - Dead Reckoning
	ZDA, ///< Time & Date - UTC, day, month, year and local time zone
	ZFO, ///< UTC & Time from origin Waypoint
	ZTG, ///< UTC & Time to Destination Waypoint

	// garmin specific
	RME, ///< Estimated Error Information (Garmin Extension)
	RMM, ///< Map Datum (Garmin Extension)
	RMZ, ///< Altitude (Garmin Extension)

	// integrated instumentation
	VWT, ///< wind true

	// AIS
	VDM, ///< AIS
	VDO, ///< AIS
};

namespace talker_id
{
	constexpr const char* autopilot_general = "AG";
	constexpr const char* autopilot_magnetic = "AP";
	constexpr const char* computer_calculator = "CC"; // programmed calculator (obsolete)
	constexpr const char* communications_dsc = "CD"; // digital selective calling (DSC)
	constexpr const char* computer_memory = "CM"; // memory data (obsolete)
	constexpr const char* communications_satellite = "CS";
	constexpr const char* communications_mfhf = "CT"; // Radio-Telephone (MF/HF)
	constexpr const char* communications_vhf = "CV"; // Radio-Telephone (VHF)
	constexpr const char* communications_scanning_receiver = "CX"; // Scanning Receiver
	constexpr const char* decca_navigation = "DE"; // DECCA Navigation (obsolete)
	constexpr const char* direction_finder = "DF"; // Direction Finder
	constexpr const char* electronic_chart_display
		= "EC"; // Electronic Chart Display & Information System (ECDIS)
	constexpr const char* emergency_position_indicating_beacon
		= "EP"; // Emergency Position Indicating Beacon (EPIRB)
	constexpr const char* engine_room_monitoring_systems = "ER"; // Engine Room Monitoring Systems
	constexpr const char* global_positioning_system = "GP"; // Global Positioning System (GPS)
	constexpr const char* magnetic_compass = "HC"; // Heading - Magnetic Compass
	constexpr const char* north_seeking_gyro = "HE"; // Heading - North Seeking Gyro
	constexpr const char* non_north_seeking_gyro = "HN"; // Heading - Non North Seeking Gyro
	constexpr const char* integrated_instrumentation = "II"; // Integrated Instrumentation
	constexpr const char* integrated_navigation = "IN"; // Integrated Navigation
	constexpr const char* loran_a = "LA"; // Loran A (obsolete)
	constexpr const char* loran_c = "LC"; // Loran C (obsolete)
	constexpr const char* microwave_positioning_system
		= "MP"; // Microwave Positioning System (obsolete)
	constexpr const char* omega_navigation_system = "OM"; // OMEGA Navigation System (obsolete)
	constexpr const char* distress_alarm_system = "OS"; // Distress Alarm System (obsolete)
	constexpr const char* radar = "RA"; // RADAR and/or ARPA
	constexpr const char* sounder_depth = "SD"; // Sounder, Depth
	constexpr const char* electronic_positioning_system
		= "SN"; // Electronic Positioning System, other/general
	constexpr const char* sounder_scanning = "SS"; // Sounder, Scanning
	constexpr const char* turn_rate_indicator = "TI"; // Turn Rate Indicator
	constexpr const char* transit_navigation_system = "TR"; // TRANSIT Navigation System
	constexpr const char* velocity_sensor_doppler = "VD"; // Velocity Sensor, Doppler, other/general
	constexpr const char* velocity_sensor_water_magnetic
		= "DM"; // Velocity Sensor, Speed Log, Water, Magnetic
	constexpr const char* velocity_sensor_water_mechanical
		= "VW"; // Velocity Sensor, Speed Log, Water, Mechanical
	constexpr const char* weather_instruments = "WI"; // Weather Instruments
	constexpr const char* transducer_temperature = "YC"; // Transducer - Temperature (obsolete)
	constexpr const char* transducer_displacement
		= "YD"; // Transducer - Displacement, Angular or Linear (obsolete)
	constexpr const char* transducer_frequency = "YF"; // Transducer - Frequency (obsolete)
	constexpr const char* transducer_level = "YL"; // Transducer - Level (obsolete)
	constexpr const char* transducer_pressure = "YP"; // Transducer - Pressure (obsolete)
	constexpr const char* transducer_flow_rate = "YR"; // Transducer - Flow Rate (obsolete)
	constexpr const char* transducer_tachometer = "YT"; // Transducer - Tachometer (obsolete)
	constexpr const char* transducer_volume = "YV"; // Transducer - Volume (obsolete)
	constexpr const char* transducer = "YX"; // Transducer
	constexpr const char* timekeeper_atomic_clock = "ZA"; // Timekeeper - Atomic Clock
	constexpr const char* timekeeper_chronometer = "ZC"; // Timekeeper - Chronometer
	constexpr const char* timekeeper_quartz = "ZQ"; // Timekeeper - Quartz
	constexpr const char* timekeeper_radio_update = "ZV"; // Timekeeper - Radio Update, WWV or WWVH

	// AIS
	constexpr const char* ais_base_station = "AB"; // NMEA 4.0 Base AIS station
	constexpr const char* ais_dependent_base_station = "AD"; // MMEA 4.0 Dependent AIS Base Station
	constexpr const char* ais_mobile_station = "AI"; // Mobile AIS station
	constexpr const char* ais_aid_to_navigation_station = "AN"; // NMEA 4.0 Aid to Navigation AIS station
	constexpr const char* ais_receiving_station = "AR"; // NMEA 4.0 AIS Receiving Station
	constexpr const char* ais_limited_base_station = "AS"; // NMEA 4.0 Limited Base Station
	constexpr const char* ais_transmitting_station = "AT"; // NMEA 4.0 AIS Transmitting Station
	constexpr const char* ais_repeater_ais_station = "AX"; // NMEA 4.0 Repeater AIS station
	constexpr const char* ais_base_station_obsolete = "BS"; // Base AIS station (deprecated in NMEA 4.0)
	constexpr const char* ais_physical_shore_station = "SA"; // NMEA 4.0 Physical Shore AIS Station
};

/// This is the base class for all sentences.
///
/// @note This class behaves like a POD, no complex data with memory operations.
class sentence
{
public:
	/// This signature is used in all subclasses to parse data fields
	/// of a particular sentence.
	using parse_function = std::function<std::unique_ptr<sentence>(
		const std::string&, const std::vector<std::string>&)>;

	constexpr static int MAX_LENGTH = 82;

	constexpr static char START_TOKEN = '$';
	constexpr static char START_TOKEN_AIS = '!';
	constexpr static char END_TOKEN = '*';

	/// Returns the ID of the sentence.
	sentence_id id() const;

	/// Returns the tag.
	const char* tag() const;

	/// Returns the talker.
	const char* talker() const;

	/// Sets the talker of the sentence.
	///
	/// @note All subclasses specify a default talker at construction.
	///   This method is used to override the default or to set the
	///   talker ID explicitly.
	void set_talker(const std::string& talker);

	friend std::string to_string(const sentence&);

protected:
	sentence(sentence_id id, const std::string& tag, const std::string& talker);
	virtual std::vector<std::string> get_data() const = 0;
	virtual char get_start_token() const { return START_TOKEN; }
	virtual char get_end_token() const { return END_TOKEN; }

private:
	const sentence_id id_;
	char tag_[4];
	char talker_[3];
};

/// Renders the specified sentence into a string.
///
/// If the sentence is invalid, the returning string will be empty.
std::string to_string(const sentence& s);

/// Casts the specified sentence to the sentence given by the template parameter.
/// If the cast is performed successfully, the original object is invalidated.
/// The object converted only if it is valid and of the correct type. It is not
/// possible to cast a sentence into a completley different one.
///
/// @param[inout] s The sentence object to convert.
/// @retval nullptr The specified sentence is either invalid or a type mismatch.
///   The specified sentence remains untouched.
/// @return The converted sentence. The specified sentence is now invalid.
///
/// Examples:
/// @code
///   auto s = nmea::make_sentence("$IIMTW,9.5,C*2F");
///   auto mtw = nmea::sentence_cast<nmea::mtw>(s); // OK, but 's' now invalid
/// @endcode
///
/// @code
///   auto s = nmea::make_sentence("$IIMTW,9.5,C*2F");
///   auto rmc = nmea::sentence_cast<nmea::rmc>(s); // Error, result is nullptr
/// @endcode
template <class T> std::unique_ptr<T> sentence_cast(std::unique_ptr<sentence>& s)
{
	if (!s)
		return nullptr;
	if (s->id() != T::ID)
		return nullptr;

	return std::unique_ptr<T>{static_cast<T*>(s.release())};
}

}

#endif
