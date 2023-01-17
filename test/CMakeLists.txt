cmake_minimum_required(VERSION 3.19)

add_executable(testrunner)

target_sources(testrunner
	PRIVATE
		marnav/ais/Test_ais.cpp
		marnav/ais/Test_ais_angle.cpp
		marnav/ais/Test_ais_binary_001_11.cpp
		marnav/ais/Test_ais_binary_200_10.cpp
		marnav/ais/Test_ais_message.cpp
		marnav/ais/Test_ais_message_01.cpp
		marnav/ais/Test_ais_message_02.cpp
		marnav/ais/Test_ais_message_03.cpp
		marnav/ais/Test_ais_message_04.cpp
		marnav/ais/Test_ais_message_05.cpp
		marnav/ais/Test_ais_message_06.cpp
		marnav/ais/Test_ais_message_07.cpp
		marnav/ais/Test_ais_message_08.cpp
		marnav/ais/Test_ais_message_09.cpp
		marnav/ais/Test_ais_message_10.cpp
		marnav/ais/Test_ais_message_11.cpp
		marnav/ais/Test_ais_message_12.cpp
		marnav/ais/Test_ais_message_13.cpp
		marnav/ais/Test_ais_message_14.cpp
		marnav/ais/Test_ais_message_17.cpp
		marnav/ais/Test_ais_message_18.cpp
		marnav/ais/Test_ais_message_19.cpp
		marnav/ais/Test_ais_message_20.cpp
		marnav/ais/Test_ais_message_21.cpp
		marnav/ais/Test_ais_message_22.cpp
		marnav/ais/Test_ais_message_23.cpp
		marnav/ais/Test_ais_message_24.cpp
		marnav/ais/Test_ais_rate_of_turn.cpp
		marnav/geo/Test_geo_angle.cpp
		marnav/geo/Test_geo_cpa.cpp
		marnav/geo/Test_geo_geodesic.cpp
		marnav/geo/Test_geo_region.cpp
		marnav/math/floatingpoint.cpp
		marnav/math/floatingpoint_ulps.cpp
		marnav/math/Test_math_floatingpoint.cpp
		marnav/math/Test_math_matrix.cpp
		marnav/math/Test_math_quaternion.cpp
		marnav/math/Test_math_vector.cpp
		marnav/nmea/Test_nmea.cpp
		marnav/nmea/Test_nmea_aam.cpp
		marnav/nmea/Test_nmea_ack.cpp
		marnav/nmea/Test_nmea_alm.cpp
		marnav/nmea/Test_nmea_alr.cpp
		marnav/nmea/Test_nmea_angle.cpp
		marnav/nmea/Test_nmea_apa.cpp
		marnav/nmea/Test_nmea_apb.cpp
		marnav/nmea/Test_nmea_bec.cpp
		marnav/nmea/Test_nmea_bod.cpp
		marnav/nmea/Test_nmea_bwc.cpp
		marnav/nmea/Test_nmea_bwr.cpp
		marnav/nmea/Test_nmea_bww.cpp
		marnav/nmea/Test_nmea_checksum.cpp
		marnav/nmea/Test_nmea_date.cpp
		marnav/nmea/Test_nmea_dbk.cpp
		marnav/nmea/Test_nmea_dbt.cpp
		marnav/nmea/Test_nmea_dpt.cpp
		marnav/nmea/Test_nmea_dsc.cpp
		marnav/nmea/Test_nmea_dse.cpp
		marnav/nmea/Test_nmea_dtm.cpp
		marnav/nmea/Test_nmea_duration.cpp
		marnav/nmea/Test_nmea_format.cpp
		marnav/nmea/Test_nmea_fsi.cpp
		marnav/nmea/Test_nmea_gbs.cpp
		marnav/nmea/Test_nmea_gga.cpp
		marnav/nmea/Test_nmea_glc.cpp
		marnav/nmea/Test_nmea_gll.cpp
		marnav/nmea/Test_nmea_gns.cpp
		marnav/nmea/Test_nmea_grs.cpp
		marnav/nmea/Test_nmea_gsa.cpp
		marnav/nmea/Test_nmea_gst.cpp
		marnav/nmea/Test_nmea_gsv.cpp
		marnav/nmea/Test_nmea_gtd.cpp
		marnav/nmea/Test_nmea_hdg.cpp
		marnav/nmea/Test_nmea_hdm.cpp
		marnav/nmea/Test_nmea_hdt.cpp
		marnav/nmea/Test_nmea_hfb.cpp
		marnav/nmea/Test_nmea_hsc.cpp
		marnav/nmea/Test_nmea_io.cpp
		marnav/nmea/Test_nmea_its.cpp
		marnav/nmea/Test_nmea_lcd.cpp
		marnav/nmea/Test_nmea_manufacturer.cpp
		marnav/nmea/Test_nmea_mob.cpp
		marnav/nmea/Test_nmea_msk.cpp
		marnav/nmea/Test_nmea_mss.cpp
		marnav/nmea/Test_nmea_mta.cpp
		marnav/nmea/Test_nmea_mtw.cpp
		marnav/nmea/Test_nmea_mwd.cpp
		marnav/nmea/Test_nmea_mwv.cpp
		marnav/nmea/Test_nmea_osd.cpp
		marnav/nmea/Test_nmea_pgrme.cpp
		marnav/nmea/Test_nmea_pgrmm.cpp
		marnav/nmea/Test_nmea_pgrmz.cpp
		marnav/nmea/Test_nmea_r00.cpp
		marnav/nmea/Test_nmea_rma.cpp
		marnav/nmea/Test_nmea_rmb.cpp
		marnav/nmea/Test_nmea_rmc.cpp
		marnav/nmea/Test_nmea_rot.cpp
		marnav/nmea/Test_nmea_route.cpp
		marnav/nmea/Test_nmea_rpm.cpp
		marnav/nmea/Test_nmea_rsa.cpp
		marnav/nmea/Test_nmea_rsd.cpp
		marnav/nmea/Test_nmea_rte.cpp
		marnav/nmea/Test_nmea_sentence.cpp
		marnav/nmea/Test_nmea_sfi.cpp
		marnav/nmea/Test_nmea_split.cpp
		marnav/nmea/Test_nmea_stalk.cpp
		marnav/nmea/Test_nmea_stn.cpp
		marnav/nmea/Test_nmea_tag_block.cpp
		marnav/nmea/Test_nmea_tds.cpp
		marnav/nmea/Test_nmea_tep.cpp
		marnav/nmea/Test_nmea_tfi.cpp
		marnav/nmea/Test_nmea_time.cpp
		marnav/nmea/Test_nmea_tll.cpp
		marnav/nmea/Test_nmea_tpc.cpp
		marnav/nmea/Test_nmea_tpr.cpp
		marnav/nmea/Test_nmea_tpt.cpp
		marnav/nmea/Test_nmea_ttm.cpp
		marnav/nmea/Test_nmea_vbw.cpp
		marnav/nmea/Test_nmea_vdm.cpp
		marnav/nmea/Test_nmea_vdo.cpp
		marnav/nmea/Test_nmea_vdr.cpp
		marnav/nmea/Test_nmea_version.cpp
		marnav/nmea/Test_nmea_vhw.cpp
		marnav/nmea/Test_nmea_vlw.cpp
		marnav/nmea/Test_nmea_vpw.cpp
		marnav/nmea/Test_nmea_vtg.cpp
		marnav/nmea/Test_nmea_vwe.cpp
		marnav/nmea/Test_nmea_vwr.cpp
		marnav/nmea/Test_nmea_waypoint.cpp
		marnav/nmea/Test_nmea_wcv.cpp
		marnav/nmea/Test_nmea_wdc.cpp
		marnav/nmea/Test_nmea_wdr.cpp
		marnav/nmea/Test_nmea_wnc.cpp
		marnav/nmea/Test_nmea_wpl.cpp
		marnav/nmea/Test_nmea_xdr.cpp
		marnav/nmea/Test_nmea_xte.cpp
		marnav/nmea/Test_nmea_xtr.cpp
		marnav/nmea/Test_nmea_zda.cpp
		marnav/nmea/Test_nmea_zdl.cpp
		marnav/nmea/Test_nmea_zfi.cpp
		marnav/nmea/Test_nmea_zfo.cpp
		marnav/nmea/Test_nmea_zlz.cpp
		marnav/nmea/Test_nmea_zpi.cpp
		marnav/nmea/Test_nmea_zta.cpp
		marnav/nmea/Test_nmea_zte.cpp
		marnav/nmea/Test_nmea_ztg.cpp
		marnav/seatalk/Test_seatalk_message.cpp
		marnav/seatalk/Test_seatalk_message_00.cpp
		marnav/seatalk/Test_seatalk_message_01.cpp
		marnav/seatalk/Test_seatalk_message_05.cpp
		marnav/seatalk/Test_seatalk_message_10.cpp
		marnav/seatalk/Test_seatalk_message_11.cpp
		marnav/seatalk/Test_seatalk_message_20.cpp
		marnav/seatalk/Test_seatalk_message_21.cpp
		marnav/seatalk/Test_seatalk_message_22.cpp
		marnav/seatalk/Test_seatalk_message_23.cpp
		marnav/seatalk/Test_seatalk_message_24.cpp
		marnav/seatalk/Test_seatalk_message_25.cpp
		marnav/seatalk/Test_seatalk_message_26.cpp
		marnav/seatalk/Test_seatalk_message_27.cpp
		marnav/seatalk/Test_seatalk_message_30.cpp
		marnav/seatalk/Test_seatalk_message_36.cpp
		marnav/seatalk/Test_seatalk_message_38.cpp
		marnav/seatalk/Test_seatalk_message_50.cpp
		marnav/seatalk/Test_seatalk_message_51.cpp
		marnav/seatalk/Test_seatalk_message_52.cpp
		marnav/seatalk/Test_seatalk_message_53.cpp
		marnav/seatalk/Test_seatalk_message_54.cpp
		marnav/seatalk/Test_seatalk_message_56.cpp
		marnav/seatalk/Test_seatalk_message_58.cpp
		marnav/seatalk/Test_seatalk_message_59.cpp
		marnav/seatalk/Test_seatalk_message_65.cpp
		marnav/seatalk/Test_seatalk_message_66.cpp
		marnav/seatalk/Test_seatalk_message_6c.cpp
		marnav/seatalk/Test_seatalk_message_86.cpp
		marnav/seatalk/Test_seatalk_message_87.cpp
		marnav/seatalk/Test_seatalk_message_89.cpp
		marnav/units/detail/basic_quantity_cmp.cpp
		marnav/units/detail/basic_quantity.cpp
		marnav/units/detail/basic_quantity_fnc.cpp
		marnav/units/detail/basic_quantity_ops.cpp
		marnav/units/detail/basic_unit_cmp.cpp
		marnav/units/detail/basic_unit.cpp
		marnav/units/detail/basic_unit_fnc.cpp
		marnav/units/detail/basic_unit_ops.cpp
		marnav/units/detail/dimension.cpp
		marnav/units/detail/units.cpp
		marnav/units/Test_basic_unit.cpp
		marnav/units/Test_basic_quantity.cpp
		marnav/units/Test_custom_numeric_type.cpp
		marnav/utils/Test_utils_bitset.cpp
		marnav/utils/Test_utils_mmsi.cpp
		marnav/utils/Test_utils_mmsi_country.cpp
	)

if(TARGET marnav::marnav-io)
	target_sources(testrunner
		PRIVATE
			marnav-io/Test_io_nmea_reader.cpp
			marnav-io/Test_io_seatalk_reader.cpp
		)
endif()

target_include_directories(testrunner
	PRIVATE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
		$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/../src>
		$<BUILD_INTERFACE:${CMAKE_HOME_DIRECTORY}/src>
	)

target_link_options(testrunner
	PRIVATE
		$<$<STREQUAL:$<UPPER_CASE:${CMAKE_SYSTEM_PROCESSOR}>,ARM>:-static>
		$<$<STREQUAL:$<UPPER_CASE:${CMAKE_SYSTEM_PROCESSOR}>,AARCH64>:-static>
	)

target_link_libraries(testrunner
	marnav::marnav
	$<$<TARGET_EXISTS:marnav::marnav-io>:marnav::marnav-io>
	$<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:GTest::gmock>
	GTest::gtest
	$<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:GTest::gmock_main>
	GTest::gtest_main
	$<$<CXX_COMPILER_ID:GNU,Clang,AppleClang>:pthread>
	)

add_test(
	NAME unittest-testrunner
	COMMAND $<TARGET_FILE:testrunner>
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	)

add_custom_target(testrunner_runtest
	COMMAND $<TARGET_FILE:testrunner> --gtest_shuffle
	DEPENDS testrunner
	WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
	)

add_custom_target(unittest)
add_dependencies(unittest testrunner_runtest)

execute_process(
	COMMAND ${CMAKE_COMMAND} -E tar xzf "${CMAKE_CURRENT_SOURCE_DIR}/marnav/ais/ais-sample.tar.gz"
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	)

add_executable(test-ais-sample
	test-ais-sample.cpp
	)

target_include_directories(test-ais-sample
	PRIVATE $<BUILD_INTERFACE:${CMAKE_HOME_DIRECTORY}/src>)

target_link_libraries(test-ais-sample PRIVATE marnav::marnav)

add_test(
	NAME integrationtest-test-ais-sample
	COMMAND test-ais-sample
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	)

execute_process(
	COMMAND ${CMAKE_COMMAND} -E tar xzf "${CMAKE_CURRENT_SOURCE_DIR}/marnav/nmea/nmea-sample.tar.gz"
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	)

add_executable(test-nmea-sample test-nmea-sample.cpp)

target_include_directories(test-nmea-sample
	PRIVATE $<BUILD_INTERFACE:${CMAKE_HOME_DIRECTORY}/src>)

target_link_libraries(test-nmea-sample PRIVATE marnav::marnav)

add_test(
	NAME integrationtest-test-nmea-sample
	COMMAND test-nmea-sample
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	)

# excluded with coverage builds, does not make sense otherwise
if(NOT CMAKE_BUILD_TYPE MATCHES Coverage AND ENABLE_TESTS_BENCHMARK)
	macro(setup_benchmark NAME SOURCE)
		add_executable(${NAME} ${SOURCE})
		target_include_directories(${NAME}
			PRIVATE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/../src>)
		target_link_libraries(${NAME} marnav::marnav benchmark::benchmark pthread)
	endmacro()

	setup_benchmark(benchmark_nmea_io marnav-io/Benchmark_nmea_io.cpp)
	setup_benchmark(benchmark_nmea_format marnav/nmea/Benchmark_nmea_format.cpp)
	setup_benchmark(benchmark_nmea_split marnav/nmea/Benchmark_nmea_split.cpp)
	setup_benchmark(benchmark_nmea_checksum marnav/nmea/Benchmark_nmea_checksum.cpp)
	setup_benchmark(benchmark_nmea_manufacturer marnav/nmea/Benchmark_nmea_manufacturer.cpp)
	setup_benchmark(benchmark_nmea_sentence marnav/nmea/Benchmark_nmea_sentence.cpp)
	setup_benchmark(benchmark_ais_message marnav/ais/Benchmark_ais_message.cpp)
endif()
