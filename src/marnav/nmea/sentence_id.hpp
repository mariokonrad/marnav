#ifndef MARNAV__NMEA__SENTENCE_ID__HPP
#define MARNAV__NMEA__SENTENCE_ID__HPP

namespace marnav
{
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
	APB, ///< Autopilot Sentence "B"
	BOD, ///< Bearing - Waypoint to Waypoint
	BWC, ///< Bearing & Distance to Waypoint - Geat Circle
	BWR, ///< Bearing and Distance to Waypoint - Rhumb Line
	BWW, ///< Bearing - Waypoint to Waypoint
	DBT, ///< Depth below transducer (II)
	DPT, ///< Depth of Water
	DSC, ///< Digital Selective Calling Information
	DSE, ///< Extended DSC
	DSI, ///< DSC Transponder Initiate
	DSR, ///< DSC Transponder Response
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
	HDG, ///< Heading - Deviation & Variation (vendor extension)
	HFB, ///< Trawl Headrope to Footrope and Bottom
	HSC, ///< Heading Steering Command
	ITS, ///< Trawl Door Spread 2 Distance
	LCD, ///< Loran-C Signal Data
	MSK, ///< Control for a Beacon Receiver
	MSS, ///< Beacon Receiver Status
	MWD, ///< Wind Directinon and Speed
	MTW, ///< Mean Temperature of Water (II)
	MWV, ///< Wind Speed and Angle (II)
	OSD, ///< Own Ship Data
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
	TLL, ///< Target latitude and longitude
	TTM, ///< Tracked Target Message
	VBW, ///< Dual Ground/Water Speed
	VDM, ///< AIS
	VDO, ///< AIS, own ship data
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
	ZDL, ///< Time and Distance to Variable Point
	ZFO, ///< UTC & Time from origin Waypoint
	ZTG, ///< UTC & Time to Destination Waypoint

	// obsolete sentences

	APA, ///< Autopilot Sentence "A"
	BER, ///< Bearing & Distance to Waypoint, Dead Reckoning, Rhumb Line
	BPI, ///< Bearing & Distance to Point of Interest
	DBK, ///< Depth Below Keel
	DBS, ///< Depth Below Surface
	DCN, ///< Decca Position
	DRU, ///< Dual Doppler Auxiliary Data
	GDA, ///< Dead Reckoning Positions
	GLA, ///< Loran-C Positions
	GOA, ///< OMEGA Positions
	GTD, ///< Geographical Position, Loran-C TDs
	GXA, ///< TRANSIT Position
	HCC, ///< Compass Heading
	HCD, ///< Heading and Deviation
	HDM, ///< Heading, Magnetic
	HDT, ///< Heading, True
	HVD, ///< Magnetic Variation, Automatic
	HVM, ///< Magnetic Variation, Manually Set
	IMA, ///< Vessel Identification
	MDA, ///< Meteorological Composite
	MHU, ///< Humidity
	MMB, ///< Barometer
	MTA, ///< Air Temperature
	MWH, ///< Wave Height
	MWS, ///< Wind & Sea State
	OLN, ///< Omega Lane Numbers
	R00, ///< (Rnn) Waypoints in active route
	SBK, ///< Loran-C Blink Status
	SCY, ///< Loran-C Cycle Lock Status
	SCD, ///< Loran-C ECDs
	SDB, ///< Loran-C Signal Strength
	SGD, ///< Position Accuracy Estimate
	SGR, ///< Loran-C Chain Identifier
	SIU, ///< Loran-C Stations in Use
	SLC, ///< Loran-C Status
	SNC, ///< Navigation Calculation Basis
	SNU, ///< Loran-C SNR Status
	SPS, ///< Loran-C Predicted Signal Strength
	SSF, ///< Position Correction Offset
	STC, ///< Time Constant
	STR, ///< Tracking Reference
	SYS, ///< Hybrid System Configuration
	VWT, ///< True Wind Speed and Angle

	// vendor extensions

	PGRME, ///< Estimated Error Information (Garmin Extension)
	PGRMM, ///< Map Datum (Garmin Extension)
	PGRMZ, ///< Altitude (Garmin Extension)
	PMGNST, ///< Magellan Status
	PRWIZCH, ///< Rockwell Channel Status
	PUBX, ///< u-blox (misc formats, depending on first field)
	TMVTD, ///< Transas VTS / SML tracking system report
};
}
}

#endif
