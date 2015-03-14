#include <iostream>
#include <string>
#include <nmea/nmea.hpp>
#include <nmea/dbt.hpp>
#include <nmea/dpt.hpp>
#include <nmea/gga.hpp>
#include <nmea/gll.hpp>
#include <nmea/gsa.hpp>
#include <nmea/gsv.hpp>
#include <nmea/mtw.hpp>
#include <nmea/rmb.hpp>
#include <nmea/rmc.hpp>
#include <nmea/rte.hpp>
#include <nmea/vtg.hpp>

template <class T>
static void test(const std::string& text)
{
	using std::cout;
	using namespace nmea;

	auto s = make_sentence(text);
	cout << "tag=" << s->tag() << "  talker=" << s->talker() << "\n";

	auto tmp = nmea::sentence_cast<T>(s);
	if (tmp) {
		cout << "org: " << text << "\n";
		cout << "new: " << to_string(*tmp) << "\n";
	}
	cout << "\n";
}

template <class T>
static void empty_test()
{
	T s{};
	std::cout << "sizeof(" << s.tag() << ") = " << sizeof(T) << "\n";
	std::cout << nmea::to_string(s) << "\n";
	std::cout << "\n";
}

int main(int, char**)
{
	test<nmea::rte>("$GPRTE,1,1,c,*37"),
	test<nmea::mtw>("$IIMTW,9.5,C*2F");
	test<nmea::rmc>("$GPRMC,,V,,,,,,,300510,0.6,E,N*39");
	test<nmea::rmc>("$GPRMC,201034,A,4702.4040,N,00818.3281,E,0.0,328.4,260807,0.6,E,A*17");
	test<nmea::gsv>("$GPGSV,3,1,11,03,03,111,00,04,15,270,00,06,01,010,00,13,06,292,00*74");
	test<nmea::gsv>("$GPGSV,3,2,11,14,25,170,00,16,57,208,39,18,67,296,40,19,40,246,00*74");
	test<nmea::gsv>("$GPGSV,3,3,11,22,42,067,42,24,14,311,43,27,05,244,00,,,,*4D");

	std::cout << "sizeof(sentence) = " << sizeof(nmea::sentence) << "\n";

	empty_test<nmea::dbt>();
	empty_test<nmea::dpt>();
	empty_test<nmea::gll>();
	empty_test<nmea::gll>();
	empty_test<nmea::gsa>();
	empty_test<nmea::gsv>();
	empty_test<nmea::mtw>();
	empty_test<nmea::rmb>();
	empty_test<nmea::rmc>();
	empty_test<nmea::rte>();
	empty_test<nmea::vtg>();

	std::cout << nmea::to_string(nmea::rmc{}) << "\n";

	{
		nmea::rmc rmc{};
		rmc.set_time_utc(nmea::time{12, 34, 56, 678});
		rmc.set_status(nmea::status::OK);
		std::cout << nmea::to_string(rmc) << "\n";
	}
	{
		nmea::rmc rmc{};
		rmc.set_lat(nmea::latitude{12, 34, 56, nmea::latitude::hemisphere::NORTH});
		rmc.set_lon(nmea::longitude{123, 45, 67, nmea::longitude::hemisphere::EAST});
		std::cout << nmea::to_string(rmc) << "\n";
	}
	{
		nmea::mtw mtw{};
		mtw.set_temperature(22.5);
		std::cout << nmea::to_string(mtw) << "\n";
	}
	{
		nmea::mtw mtw{};
		mtw.set_temperature(9.5);
		std::cout << nmea::to_string(mtw) << "\n";
	}
	{
		nmea::gll gll{};
		gll.set_lat(nmea::latitude{12, 34, 56, nmea::latitude::hemisphere::NORTH});
		gll.set_lon(nmea::longitude{123, 45, 67, nmea::longitude::hemisphere::EAST});
		std::cout << nmea::to_string(gll) << "\n";
	}
	{
		nmea::dbt dbt{};
		dbt.set_depth_feet(10.56);
		std::cout << nmea::to_string(dbt) << "\n";
		dbt.set_depth_meter(4.9);
		std::cout << nmea::to_string(dbt) << "\n";
	}
	{
		nmea::dpt dpt{};
		dpt.set_depth_meter(10.56);
		std::cout << nmea::to_string(dpt) << "\n";
		dpt.set_transducer_offset(2.1);
		std::cout << nmea::to_string(dpt) << "\n";
	}
	{
		nmea::rmb rmb{};
		rmb.set_lat(nmea::latitude{12, 34, 56, nmea::latitude::hemisphere::NORTH});
		rmb.set_lon(nmea::longitude{123, 45, 67, nmea::longitude::hemisphere::EAST});
		rmb.set_waypoint_to("P1");
		rmb.set_waypoint_from("P2");
		std::cout << nmea::to_string(rmb) << "\n";
	}
	{
		nmea::gga gga{};
		std::cout << nmea::to_string(gga) << "\n";
	}
	{
		nmea::vtg vtg{};
		vtg.set_speed_kn(10.4);
		std::cout << nmea::to_string(vtg) << "\n";
	}
	{
		nmea::gsv gsv{};
		gsv.set_sat_0(1, 2, 3, 4);
		std::cout << nmea::to_string(gsv) << "\n";
	}
	{
		nmea::rte rte{};
		rte.set_n_messages(1);
		rte.set_message_number(1);
		rte.set_message_mode('c');
		rte.set_waypoint_id(0, "abc");
		std::cout << nmea::to_string(rte) << "\n";
	}

	{
		nmea::rte rte{};
		rte.set_n_messages(1);
		rte.set_message_number(1);
		rte.set_message_mode('c');
		rte.set_waypoint_id(0, "");
		std::cout << nmea::to_string(rte) << "\n";
	}

/*
	std::cout << "leap years:\n";
	for (uint32_t year = 1980; year < 2020; ++year) {
		std::cout << year << " : " << nmea::date::is_leap_year(year) << "\n";
	}
*/

	return 0;
}

