TODO
====

GENERAL
-------

@todo Memory leak checker

@todo Profiling

@todo integration tests


Geodesic Stuff
--------------

@todo Provide means to calculate CPA (closest point of approach) and
      TCPA (time to closest point of approach)

NMEA
----

@todo Implement writer for serial devices

@todo Implement additional checks in sentences, wheather or not the received data is correct.

@todo Implement more sentences:
	- ASD - Autopilot System Data
	- DSC - Digital Selective Calling Information
	- DSE - Extended DSC
	- DSI - DSC Transponder Initiate
	- DSR - DSC Transponder Response
	- DTM - Datum Reference
	- GBS - GPS Satellite Fault Detection
	- GLC - Geographic Position, Loran-C
	- GRS - GPS Range Residuals
	- GST - GPS Pseudorange Noise Statistics
	- GTD - Geographic Location in Time Differences
	- HFB - Trawl Headrope to Footrope and Bottom
	- ITS - Trawl Door Spread 2 Distance
	- LCD - Loran-C Signal Data
	- MSK - Control for a Beacon Receiver
	- MSS - Beacon Receiver Status
	- RPM - Revolutions
	- RSD - RADAR System Data
	- STN - Multiple Data ID
	- TDS - Trawl Door Spread Distance
	- TFI - Trawl Filling Indicator
	- TLL - Target Latitude and Longitude
	- TPC - Trawl Position Cartesian Coordinates
	- TPR - Trawl Position Relative Vessel
	- TPT - Trawl Position True
	- TRF - TRANSIT Fix Data
	- TTM - Tracked Target Message
	- vendor extensions

AIS
---

@todo Implement more messages:
	- Type 06: Binary Addressed Message
	- Type 07: Binary Acknowledge
	- Type 08: Binary Broadcast Message
	- Type 12: Addressed Safety-Related Message
	- Type 13: Safety-Related Acknowledgement
	- Type 14: Safety-Related Broadcast Message
	- Type 15: Interrogation
	- Type 16: Assignment Mode Command
	- Type 17: DGNSS Broadcast Binary Message
	- Type 20: Data Link Management Message
	- Type 21: Aid-to-Navigation Report
	- Type 22: Channel Management
	- Type 23: Group Assignment Command
	- Type 25: Single Slot Binary Message
	- Type 26: Multiple Slot Binary Message
	- Type 27: Long Range AIS Broadcast message

SeaTalk
-------

@todo Implement writer for serial devices

@todo Implement more messages:
	- Type 05: Engine RPM and PITCH
	- Type 24: Display unit for Mileage and Speed
	- Type 26: Speed through Water
	- Type 30: Set lamp Intensity
	- Type 36: Cancel MOB condition
	- Type 38: Codelock data
	- Type 50: LAT Postion
	- Type 51: LON Postion
	- Type 52: Speed over Ground
	- Type 53: Magnetic Course in Degrees
	- Type 54: GMT Time
	- Type 55: TRACK keystroke on GPS unit
	- Type 56: Date
	- Type 57: Sat Info
	- Type 58: LAT/LON
	- Type 59: Set Count Down Timer (sent by ST60)
	- Type 61: (issued by E-80 multifunction display at init)
	- Type 65: Select Fathom display unit for depth display (see message 00)
	- Type 66: Wind Alarm
	- Type 68: Alarm ackknowledgement keystroke (ST80 Masterview, ST40 Wind Instrument)
	- Type 6C: Second equipment-ID
	- Type 6E: MOB
	- Type 70: Keystroke on Raymarine A25006 ST60 Maxiview Remote Control
	- Type 80: Set Lamp Intensity
	- Type 81: Setup of user calibration
	- Type 82: Target waypoint name
	- Type 83: sent by course computer
	- Type 84: Compass heading Autopilot course and rudder position
	- Type 85: navigation to waypoint information
	- Type 86: Keystroke
	- Type 87: Response Level
	- Type 88: Autopilot Parameter
	- Type 89: Compass heading (sent by ST40 compass instrument)

