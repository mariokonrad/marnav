TODO
====

GENERAL
-------

@todo integration tests

NMEA
----

@todo Implement writer for serial devices

@todo Implement additional checks in sentences, wheather or not the received data is correct.

@todo Implement sentence: ASD: Autopilot System Data

@todo Implement sentence: DSI: DSC Transponder Initiate

@todo Implement sentence: DSR: DSC Transponder Response

@todo Implement sentence: STN: Multiple Data ID


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
	- Type 22: Channel Management
	- Type 23: Group Assignment Command
	- Type 25: Single Slot Binary Message
	- Type 26: Multiple Slot Binary Message
	- Type 27: Long Range AIS Broadcast message

SeaTalk
-------

@todo Implement writer for serial devices

@todo Implement more messages:
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

