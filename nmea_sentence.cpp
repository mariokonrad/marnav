#include <iostream>
#include <string>
#include "nmea.hpp"
#include "mtw.hpp"
#include "rmc.hpp"

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
	std::cout << "sizeof(rmc)      = " << sizeof(nmea::rmc) << "\n";
	std::cout << "sizeof(mtw)      = " << sizeof(nmea::mtw) << "\n";
	std::cout << "\n";

	std::cout << nmea::to_string(nmea::rmc{}) << "\n";

	return 0;
}

