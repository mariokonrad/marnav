Features {#page_features}
========

[TOC]

It supports (partially):
- NMEA-0183
- AIS
- SeaTalk (Raymarine device communication)
- Reading data from serial ports (NMEA, SeaTalk)
- Basic geodesic functions, suitable for martime navigation.

Supported sentences for NMEA-0183 (read and write):
- AAM: Waypoint Arrival Alarm
- BOD: Bearing - Waypoint to Waypoint
- DBT: Depth Below Transducer
- DPT: Depth of Water
- GGA: Global Positioning System Fix Data
- GLL: Geographic Position - Latitude/Longitude
- GSA: Geographic Position - Latitude/Longitude
- GSV: Satellites in view
- HDG: Heading - Deviation & Variation
- MTW: Mean Temperature of Water
- MWV: Wind Speed and Angle
- R00: Waypoints in active route
- RMA: Recommended Minimum Navigation Information
- RMB: Recommended Minimum Navigation Information
- RMC: Recommended Minimum Navigation Information
- RTE: Routes
- VHW: Water speed and heading
- VLW: Distance Traveled through Water
- VTG: Track made good and Ground speed
- VWR: Relative Wind Speed and Angle.
- VDM
- VDO
- WNC: Distance - Waypoint to Waypoint
- XDR: Transducer Measurement
- XTE: Cross-Track Error, Measured

Supported messages for AIS (decode and encode):
- type 1: position report class A
- type 2: position report class A (assigned schedule)
- type 3: position report class A (response to interrogation)
- type 5: static and voyage related data

Suported messages for SeaTalk (decode and encode):
- type 00: depth below transducer
- type 01: equipment id
- type 10: apparent wind angle
- type 11: apparent wind speed
- type 20: speed through water
- type 21: trip mileage
- type 22: total mileage
- type 23: water temperature 1
- type 25: total and trip log
- type 27: water temperature 2

