Features {#page_features}
========

[TOC]

It supports (partially):
- NMEA-0183
- AIS
- SeaTalk (Raymarine device communication)
- Reading data from serial ports (NMEA, SeaTalk)
- Basic geodesic functions, suitable for martime navigation.


NMEA-0183
---------
Supported sentences for NMEA-0183 (read and write):
- AAM: Waypoint Arrival Alarm
- ALM: GPS Almanac Data
- APB: Autopilot Sentence "B"
- BOD: Bearing - Waypoint to Waypoint
- BWC: Bearing & Distance to Waypoint - Geat Circle
- BWR: Bearing and Distance to Waypoint - Rhumb Line
- BWW: Bearing - Waypoint to Waypoint
- DBT: Depth Below Transducer
- DPT: Depth of Water
- FSI: Frequency Set Information
- GGA: Global Positioning System Fix Data
- GLL: Geographic Position - Latitude/Longitude
- GNS: Fix data
- GSA: Geographic Position - Latitude/Longitude
- GSV: Satellites in view
- HDG: Heading - Deviation & Variation
- HSC: Heading Steering Command
- MTW: Mean Temperature of Water
- MWD: Wind Direction and Speed
- MWV: Wind Speed and Angle
- OSD: Own Ship Data
- RMA: Recommended Minimum Navigation Information
- RMB: Recommended Minimum Navigation Information
- RMC: Recommended Minimum Navigation Information
- ROT: Rate Of Turn
- RSA: Rudder Sensor Angle
- RTE: Routes
- SFI: Scanning Frequency Information
- VBW: Dual Ground/Water Speed
- VDM: AIS VHF Data-Link Message
- VDO: AIS VHF Data-Link Own-Vessel Report
- VDR: Set and Drift
- VHW: Water speed and heading
- VLW: Distance Traveled through Water
- VTG: Track made good and Ground speed
- VWR: Relative Wind Speed and Angle.
- VPW: Speed - Measured Parallel to Wind
- WCV: Waypoint Closure Velocity
- WNC: Distance - Waypoint to Waypoint
- WPL: Waypoint Location
- XDR: Transducer Measurement
- XTE: Cross-Track Error, Measured
- XTR: Cross Track Error - Dead Reckoning
- ZDA: Time & Date - UTC, day, month, year and local time zone
- ZDL: Time and Distance to Variable Point
- ZFO: UTC & Time from origin Waypoint
- ZTG: UTC & Time to Destination Waypoint

Obsolete (according to the standard) but implemented:
- DBK: Depth Below Keel
- HDM: Heading - Magnetic (obsolete as of 2009)
- R00: Waypoints in active route

Vendor Extensions:
- PGRME: Garmin Estimated Error


AIS
---
Supported messages for AIS (decode and encode):
- Type 01: Position Report Class A
- Type 02: Position Report Class A (Assigned Schedule)
- Type 03: Position Report Class A (Response to Interrogation)
- Type 04: Base Station Report
- Type 05: Static and Voyage Related Data
- Type 09: Standard SAR Aircraft Position Report
- Type 18: Standard Class B CS Position Report
- Type 19: Extended Class B CS Position Report
- Type 24: Static Data Report (part A and B, norma and auxiliary vessel)


SeaTalk
-------
Suported messages for SeaTalk (decode and encode):
- Type 00: depth below transducer
- Type 01: equipment id
- Type 10: apparent wind angle
- Type 11: apparent wind speed
- Type 20: speed through water
- Type 21: trip mileage
- Type 22: total mileage
- Type 23: water temperature 1
- Type 25: total and trip log
- Type 27: water temperature 2

