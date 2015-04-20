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
- AAM
- BOD
- DBT
- DPT
- GGA
- GLL
- GSA
- GSV
- HDG
- MTW
- MWV
- RMB
- RMC
- RTE
- VHW
- VLW
- VTG
- VWR
- VDM
- VDO
- WNC

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

