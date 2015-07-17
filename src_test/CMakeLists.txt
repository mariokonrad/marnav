
include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}
	${CMAKE_CURRENT_SOURCE_DIR}/../src
	${CMAKE_CURRENT_BINARY_DIR}/../src
	)

add_executable(testrunner
	utils/Test_utils_bitset.cpp
	utils/Test_utils_mmsi.cpp
	geo/Test_geo_angle.cpp
	geo/Test_geo_geodesic.cpp
	nmea/Test_nmea.cpp
	nmea/Test_nmea_angle.cpp
	nmea/Test_nmea_date.cpp
	nmea/Test_nmea_time.cpp
	nmea/Test_nmea_sentence.cpp
	nmea/Test_nmea_io.cpp
	nmea/Test_nmea_aam.cpp
	nmea/Test_nmea_alm.cpp
	nmea/Test_nmea_apb.cpp
	nmea/Test_nmea_bod.cpp
	nmea/Test_nmea_bwc.cpp
	nmea/Test_nmea_bwr.cpp
	nmea/Test_nmea_bww.cpp
	nmea/Test_nmea_dbk.cpp
	nmea/Test_nmea_dbt.cpp
	nmea/Test_nmea_dpt.cpp
	nmea/Test_nmea_fsi.cpp
	nmea/Test_nmea_gga.cpp
	nmea/Test_nmea_gll.cpp
	nmea/Test_nmea_gns.cpp
	nmea/Test_nmea_gsa.cpp
	nmea/Test_nmea_gsv.cpp
	nmea/Test_nmea_hdg.cpp
	nmea/Test_nmea_hdm.cpp
	nmea/Test_nmea_hsc.cpp
	nmea/Test_nmea_mtw.cpp
	nmea/Test_nmea_mwd.cpp
	nmea/Test_nmea_mwv.cpp
	nmea/Test_nmea_osd.cpp
	nmea/Test_nmea_r00.cpp
	nmea/Test_nmea_rma.cpp
	nmea/Test_nmea_rmb.cpp
	nmea/Test_nmea_rmc.cpp
	nmea/Test_nmea_rot.cpp
	nmea/Test_nmea_rsa.cpp
	nmea/Test_nmea_rte.cpp
	nmea/Test_nmea_sfi.cpp
	nmea/Test_nmea_vbw.cpp
	nmea/Test_nmea_vdm.cpp
	nmea/Test_nmea_vdo.cpp
	nmea/Test_nmea_vdr.cpp
	nmea/Test_nmea_vhw.cpp
	nmea/Test_nmea_vlw.cpp
	nmea/Test_nmea_vpw.cpp
	nmea/Test_nmea_vwr.cpp
	nmea/Test_nmea_vtg.cpp
	nmea/Test_nmea_wcv.cpp
	nmea/Test_nmea_wnc.cpp
	nmea/Test_nmea_wpl.cpp
	nmea/Test_nmea_xdr.cpp
	nmea/Test_nmea_xte.cpp
	nmea/Test_nmea_xtr.cpp
	nmea/Test_nmea_zda.cpp
	nmea/Test_nmea_zdl.cpp
	nmea/Test_nmea_zfo.cpp
	nmea/Test_nmea_ztg.cpp
	nmea/Test_nmea_pgrme.cpp
	ais/Test_ais.cpp
	ais/Test_ais_message.cpp
	ais/Test_ais_message_01.cpp
	ais/Test_ais_message_02.cpp
	ais/Test_ais_message_03.cpp
	ais/Test_ais_message_04.cpp
	ais/Test_ais_message_05.cpp
	ais/Test_ais_message_18.cpp
	ais/Test_ais_message_19.cpp
	ais/Test_ais_message_24.cpp
	seatalk/Test_seatalk_message.cpp
	seatalk/Test_seatalk_message_00.cpp
	seatalk/Test_seatalk_message_01.cpp
	seatalk/Test_seatalk_message_10.cpp
	seatalk/Test_seatalk_message_11.cpp
	seatalk/Test_seatalk_message_20.cpp
	seatalk/Test_seatalk_message_21.cpp
	seatalk/Test_seatalk_message_22.cpp
	seatalk/Test_seatalk_message_23.cpp
	seatalk/Test_seatalk_message_25.cpp
	seatalk/Test_seatalk_message_27.cpp
	io/Test_io_seatalk_reader.cpp
	io/Test_io_nmea_reader.cpp
	)

target_link_libraries(testrunner
	marnav
	gmock
	pthread
	)

add_test(
	NAME unittest-testrunner
	COMMAND testrunner
	WORKING_DIRECTOR "${CMAKE_CURRENT_BINARY_DIR}"
	)
run_unittest(testrunner)

execute_process(
	COMMAND ${CMAKE_COMMAND} -E tar xzf "${CMAKE_CURRENT_SOURCE_DIR}/ais/ais-sample.tar.gz"
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	)

add_executable(test-ais-sample
	test-ais-sample.cpp
	)

target_link_libraries(test-ais-sample
	marnav
	)

add_test(
	NAME integrationtest-test-ais-sample
	COMMAND test-ais-sample
	WORKING_DIRECTOR "${CMAKE_CURRENT_BINARY_DIR}"
	)

execute_process(
	COMMAND ${CMAKE_COMMAND} -E tar xzf "${CMAKE_CURRENT_SOURCE_DIR}/nmea/nmea-sample.tar.gz"
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	)

add_executable(test-nmea-sample
	test-nmea-sample.cpp
	)

target_link_libraries(test-nmea-sample
	marnav
	)

add_test(
	NAME integrationtest-test-nmea-sample
	COMMAND test-nmea-sample
	WORKING_DIRECTOR "${CMAKE_CURRENT_BINARY_DIR}"
	)

