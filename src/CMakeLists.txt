cmake_minimum_required(VERSION 2.8)
project(nmea)

add_executable(nmeasum
	nmeasum.cpp
	)

add_library(nmea
	nmea/angle.cpp
	nmea/date.cpp
	nmea/time.cpp
	nmea/sentence.cpp
	nmea/nmea.cpp
	nmea/aam.cpp
	nmea/bod.cpp
	nmea/dbt.cpp
	nmea/dpt.cpp
	nmea/gga.cpp
	nmea/gll.cpp
	nmea/gsa.cpp
	nmea/gsv.cpp
	nmea/hdg.cpp
	nmea/mtw.cpp
	nmea/mwv.cpp
	nmea/rmb.cpp
	nmea/rmc.cpp
	nmea/rte.cpp
	nmea/vhw.cpp
	nmea/vlw.cpp
	nmea/vtg.cpp
	nmea/vwr.cpp
	nmea/vdm.cpp
	nmea/vdo.cpp
	nmea/optional.hpp
	utils/unique.hpp
	)

# TODO (first of all sentences):
# vwt
# rme
# rmm
# rmz

# TODO: sentences (obsolete already exluded)
# ALM - GPS Almanac Data
# APB - Autopilot Sentence "B"
# BWC - Bearing & Distance to Waypoint - Geat Circle
# BWR - Bearing and Distance to Waypoint - Rhumb Line
# BWW - Bearing - Waypoint to Waypoint
# DCN - Decca Position
# DTM - Datum Reference
# FSI - Frequency Set Information
# GBS - GPS Satellite Fault Detection
# GLC - Geographic Position, Loran-C
# GNS - Fix data
# GRS - GPS Range Residuals
# GST - GPS Pseudorange Noise Statistics
# GSV - Satellites in view
# GTD - Geographic Location in Time Differences
# HFB - Trawl Headrope to Footrope and Bottom
# HSC - Heading Steering Command
# ITS - Trawl Door Spread 2 Distance
# LCD - Loran-C Signal Data
# MSK - Control for a Beacon Receiver
# MSS - Beacon Receiver Status
# OLN - Omega Lane Numbers
# OSD - Own Ship Data
# RMA - Recommended Minimum Navigation Information
# ROT - Rate Of Turn
# RPM - Revolutions
# RSA - Rudder Sensor Angle
# RSD - RADAR System Data
# SFI - Scanning Frequency Information
# STN - Multiple Data ID
# TDS - Trawl Door Spread Distance
# TFI - Trawl Filling Indicator
# TPC - Trawl Position Cartesian Coordinates
# TPR - Trawl Position Relative Vessel
# TPT - Trawl Position True
# TRF - TRANSIT Fix Data
# TTM - Tracked Target Message
# VBW - Dual Ground/Water Speed
# VDR - Set and Drift
# VLW - Distance Traveled through Water
# VPW - Speed - Measured Parallel to Wind
# VWR - Relative Wind Speed and Angle
# WCV - Waypoint Closure Velocity
# WNC - Distance - Waypoint to Waypoint
# WPL - Waypoint Location
# XDR - Transducer Measurement
# XTE - Cross-Track Error, Measured
# XTR - Cross Track Error - Dead Reckoning
# ZDA - Time & Date - UTC, day, month, year and local time zone
# ZFO - UTC & Time from origin Waypoint
# ZTG - UTC & Time to Destination Waypoint
# AIVDM/AIVDO
# vendor extensions

set_target_properties(nmea
	PROPERTIES VERSION 0.0.1
	SOVERSION 0.0.1
	)

install(
	TARGETS nmea
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	)

install(
	FILES
		nmea/angle.hpp
		nmea/date.hpp
		nmea/time.hpp
		nmea/optional.hpp
		nmea/sentence.hpp
		nmea/nmea.hpp
		nmea/aam.hpp
		nmea/bod.hpp
		nmea/dbt.hpp
		nmea/dpt.hpp
		nmea/gga.hpp
		nmea/gll.hpp
		nmea/gsa.hpp
		nmea/gsv.hpp
		nmea/mtw.hpp
		nmea/rmb.hpp
		nmea/rmc.hpp
		nmea/rte.hpp
		nmea/vtg.hpp
		nmea/vwr.hpp
		nmea/vdm.hpp
		nmea/vdo.hpp
		utils/unique.hpp
	DESTINATION include/nmea
	)

add_library(ais
	ais/ais.cpp
	ais/message.cpp
	ais/message_01.cpp
	utils/unique.hpp
	utils/bitset.hpp
	)

set_target_properties(ais
	PROPERTIES VERSION 0.0.1
	SOVERSION 0.0.1
	)

install(
	TARGETS ais
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	)

install(
	FILES
		ais/ais.hpp
		ais/message.hpp
		ais/message_01.hpp
		utils/unique.hpp
		utils/bitset.hpp
	DESTINATION include/ais
	)

