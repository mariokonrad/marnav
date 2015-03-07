#include <iostream>
#include <string>
#include <nmea/nmea.hpp>
#include <nmea/dbt.hpp>
#include <nmea/dpt.hpp>
#include <nmea/gga.hpp>
#include <nmea/gll.hpp>
#include <nmea/mtw.hpp>
#include <nmea/rmb.hpp>
#include <nmea/rmc.hpp>
#include <nmea/vtg.hpp>

static void test(const std::string& text)
{
	using std::cout;
	using namespace nmea;

	auto s = make_sentence(text);
	cout << "tag=" << s->tag() << "  talker=" << s->talker() << "\n";
	{
		auto tmp = nmea::sentence_cast<nmea::mtw>(s);
		if (tmp) {
			cout << "org: " << text << "\n";
			cout << "new: " << to_string(*tmp) << "\n";
		}
	}
	{
		auto tmp = nmea::sentence_cast<nmea::rmc>(s);
		if (tmp) {
			cout << "org: " << text << "\n";
			cout << "new: " << to_string(*tmp) << "\n";
		}
	}

	cout << "\n";
}

int main(int, char**)
{
	test("$IIMTW,9.5,C*2F");
	test("$GPRMC,,V,,,,,,,300510,0.6,E,N*39");
	test("$GPRMC,201034,A,4702.4040,N,00818.3281,E,0.0,328.4,260807,0.6,E,A*17");

	std::cout << "sizeof(sentence) = " << sizeof(nmea::sentence) << "\n";
	std::cout << "sizeof(dbt)      = " << sizeof(nmea::dbt) << "\n";
	std::cout << "sizeof(dpt)      = " << sizeof(nmea::dpt) << "\n";
	std::cout << "sizeof(gll)      = " << sizeof(nmea::gll) << "\n";
	std::cout << "sizeof(gll)      = " << sizeof(nmea::gga) << "\n";
	std::cout << "sizeof(mtw)      = " << sizeof(nmea::mtw) << "\n";
	std::cout << "sizeof(rmb)      = " << sizeof(nmea::rmb) << "\n";
	std::cout << "sizeof(rmc)      = " << sizeof(nmea::rmc) << "\n";
	std::cout << "sizeof(vtg)      = " << sizeof(nmea::vtg) << "\n";
	std::cout << "\n";

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
		rmb.set_waypoint_to(13);
		rmb.set_waypoint_from(12);
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

/*
	std::cout << "leap years:\n";
	for (uint32_t year = 1980; year < 2020; ++year) {
		std::cout << year << " : " << nmea::date::is_leap_year(year) << "\n";
	}
*/

	return 0;
}

