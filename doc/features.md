Features {#page_features}
========

It supports (partially):
- NMEA-0183
- AIS
- SeaTalk (Raymarine device communication)
- Reading data from serial ports (NMEA, SeaTalk)
- Basic geodesic functions, suitable for martime navigation.
  - Calculation of CPA (closest point of approach)
    and TCPA (time to closest point of approach)
  - Distance of two points on a sphere
  - Distance of two points on an ellipsoid using formula of Vincenty
  - Distance of two points on an ellipsoid using formula of Lambert


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
- DSC: Digital Selective Calling Information (**experimental**)
- DSE: Extended DSC (**experimental**)
- DTM: Datum Reference
- FSI: Frequency Set Information
- GBS: GPS Satellite Fault Detection
- GGA: Global Positioning System Fix Data
- GLC: Geographic Position, Loran-C
- GLL: Geographic Position - Latitude/Longitude
- GNS: Fix data
- GRS: GPS Range Residuals
- GSA: Geographic Position - Latitude/Longitude
- GST: GPS Pseudorange Noise Statistics
- GSV: Satellites in view
- GTD: Geographic Location in Time Differences
- HDG: Heading - Deviation & Variation
- HFB: Trawl Headrope to Footrope and Bottom
- HSC: Heading Steering Command
- ITS: Trawl Door Spread 2 Distance
- LCD: Loran-C Signal Data
- MSK: Control for a Beacon Receiver
- MSS: Beacon Receiver Status
- MTW: Mean Temperature of Water
- MWD: Wind Direction and Speed
- MWV: Wind Speed and Angle
- OSD: Own Ship Data
- RMA: Recommended Minimum Navigation Information
- RMB: Recommended Minimum Navigation Information
- RMC: Recommended Minimum Navigation Information
- ROT: Rate Of Turn
- RPM: Revolutions
- RSA: Rudder Sensor Angle
- RSD: RADAR System Data (**experimental**)
- RTE: Routes
- SFI: Scanning Frequency Information
- TDS: Trawl Door Spread Distance
- TFI: Trawl Filling Indicator
- TLL: Target Latitude and Longitude
- TPC: Trawl Position Cartesian Coordinates
- TPR: Trawl Position Relative Vessel
- TPT: Trawl Position True
- TTM: Tracked Target Message
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
- Type 10: UTC/Date Inquiry
- Type 11: UTC/Date Response
- Type 18: Standard Class B CS Position Report
- Type 19: Extended Class B CS Position Report
- Type 21: Aid-to-Navigation Report
- Type 22: Channel Management
- Type 23: Group Assignment Command
- Type 24: Static Data Report (part A and B, norma and auxiliary vessel)


SeaTalk
-------
Suported messages for SeaTalk (decode and encode):
- Type 00: depth below transducer
- Type 01: equipment id
- Type 05: Engine RPM and PITCH
- Type 10: apparent wind angle
- Type 11: apparent wind speed
- Type 20: speed through water
- Type 21: trip mileage
- Type 22: total mileage
- Type 23: water temperature 1
- Type 24: Display unit for Mileage and Speed
- Type 25: total and trip log
- Type 26: Speed through Water
- Type 27: water temperature 2
- Type 30: Set Lamp Intensity
- Type 36: Cancel MOB condition
- Type 38: Codelock data (**experimental**)
- Type 50: LAT Postion
- Type 51: LON Postion
- Type 52: Speed over Ground
- Type 53: Magnetic Course in Degrees
- Type 54: GMT Time

