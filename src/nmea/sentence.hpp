#ifndef __NMEA__SENTENCE__HPP__
#define __NMEA__SENTENCE__HPP__

#include <functional>
#include <memory>
#include <vector>
#include <string>
#include "optional.hpp"

namespace nmea
{

enum class sentence_id : uint32_t {
	NONE = 0,

	// standard sentences
	AAM, // Waypoint Arrival Alarm
	ALM, // GPS Almanac Data
	APA, // Autopilot Sentence "A"
	APB, // Autopilot Sentence "B"
	BOD, // Bearing - Waypoint to Waypoint
	BWC, // Bearing & Distance to Waypoint - Geat Circle
	BWR, // Bearing and Distance to Waypoint - Rhumb Line
	BWW, // Bearing - Waypoint to Waypoint
	DBK, // Depth Below Keel
	DBS, // Depth Below Surface
	DBT, // Depth below transducer (II)
	DCN, // Decca Position
	DPT, // Depth of Water
	DTM, // Datum Reference
	FSI, // Frequency Set Information
	GBS, // GPS Satellite Fault Detection
	GGA, // Global Positioning System Fix Data
	GLC, // Geographic Position, Loran-C
	GLL, // Geographic Position - Latitude/Longitude
	GNS, // Fix data
	GRS, // GPS Range Residuals
	GST, // GPS Pseudorange Noise Statistics
	GSA, // GPS DOP and active satellites
	GSV, // Satellites in view
	GTD, // Geographic Location in Time Differences
	GXA, // TRANSIT Position - Latitude/Longitude
	HDG, // Heading - Deviation & Variation (vendor extension)
	HDM, // Heading - Magnetic
	HDT, // Heading - True
	HFB, // Trawl Headrope to Footrope and Bottom
	HSC, // Heading Steering Command
	ITS, // Trawl Door Spread 2 Distance
	LCD, // Loran-C Signal Data
	MSK, // Control for a Beacon Receiver
	MSS, // Beacon Receiver Status
	MTW, // Mean Temperature of Water (II)
	MWV, // Wind Speed and Angle (II)
	OLN, // Omega Lane Numbers
	OSD, // Own Ship Data
	R00, // Waypoints in active route
	RMA, // Recommended Minimum Navigation Information
	RMB, // Recommended Minimum Navigation Information
	RMC, // Recommended Minimum Navigation Information
	ROT, // Rate Of Turn
	RPM, // Revolutions
	RSA, // Rudder Sensor Angle
	RSD, // RADAR System Data
	RTE, // Routes
	SFI, // Scanning Frequency Information
	STN, // Multiple Data ID
	TDS, // Trawl Door Spread Distance
	TFI, // Trawl Filling Indicator
	TPC, // Trawl Position Cartesian Coordinates
	TPR, // Trawl Position Relative Vessel
	TPT, // Trawl Position True
	TRF, // TRANSIT Fix Data
	TTM, // Tracked Target Message
	VBW, // Dual Ground/Water Speed
	VDR, // Set and Drift
	VHW, // Water speed and heading (II)
	VLW, // Distance Traveled through Water (II)
	VPW, // Speed - Measured Parallel to Wind
	VTG, // Track made good and Ground speed
	VWR, // Relative Wind Speed and Angle (II)
	WCV, // Waypoint Closure Velocity
	WNC, // Distance - Waypoint to Waypoint
	WPL, // Waypoint Location
	XDR, // Transducer Measurement
	XTE, // Cross-Track Error, Measured
	XTR, // Cross Track Error - Dead Reckoning
	ZDA, // Time & Date - UTC, day, month, year and local time zone
	ZFO, // UTC & Time from origin Waypoint
	ZTG, // UTC & Time to Destination Waypoint

	// garmin specific
	RME,
	RMM,
	RMZ,

	// integrated instumentation
	VWT, // wind true
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
};

namespace direction
{
	constexpr const char EAST = 'E';
	constexpr const char WEST = 'W';
	constexpr const char NORTH = 'N';
	constexpr const char SOUTH = 'S';
}

namespace status
{
	constexpr const char OK = 'A';
	constexpr const char WARNING = 'V';
}

namespace signal_integrity
{
	constexpr const char AUTONOMOUS = 'A';
	constexpr const char DIFFERENTIAL = 'D';
	constexpr const char ESTIMATED = 'E';
	constexpr const char MANUALINPUT = 'M';
	constexpr const char SIMULATED = 'S';
	constexpr const char DATANOTVALID = 'N';
}

namespace quality
{
	constexpr const int INVALID = 0;
	constexpr const int GPS_FIX = 1;
	constexpr const int DPGS_FIX = 2;
	constexpr const int GUESS = 6;
}

namespace unit
{
	constexpr const char METER = 'M';
	constexpr const char FEET = 'f';
	constexpr const char NM = 'N'; // nautical miles
	constexpr const char FATHOM = 'F';
	constexpr const char KNOT = 'N';
	constexpr const char KMH = 'K'; // kilometers per hour
	constexpr const char MPS = 'M'; // meters per second
	constexpr const char CELSIUS = 'C';
}

namespace reference
{
	constexpr const char TRUE = 'T';
	constexpr const char MAGNETIC = 'M';
	constexpr const char RELATIVE = 'R';
}

namespace side
{
	constexpr const char LEFT = 'L';
	constexpr const char RIGHT = 'R';
}

namespace route
{
	constexpr const char COMPLETE = 'C';
	constexpr const char WORKING = 'W';
}

namespace selectionmode
{
	constexpr const char MANUAL = 'M';
	constexpr const char AUTOMATIC = 'A';
}

/// @note This class behaves like a POD, no complex data with memory operations.
class sentence
{
public:
	using parse_function = std::function<std::unique_ptr<sentence>(
		const std::string&, const std::vector<std::string>&)>;

	constexpr static int MAX_LENGTH = 82;

	constexpr static char START_TOKEN = '$';
	constexpr static char START_TOKEN_AIVDM = '!';
	constexpr static char END_TOKEN = '*';

	sentence_id id() const;
	const char* tag() const;
	const char* talker() const;

	void set_talker(const std::string& talker);

	friend std::string to_string(const sentence&);

protected:
	sentence(sentence_id id, const std::string& tag, const std::string& talker);
	virtual std::vector<std::string> get_data() const = 0;

private:
	const sentence_id id_;
	char tag_[4];
	char talker_[3];
};

std::string to_string(const sentence& s);

}

#endif
