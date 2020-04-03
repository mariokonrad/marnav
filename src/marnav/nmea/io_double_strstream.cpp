#include <marnav/nmea/io.hpp>
#include <marnav/utils/unused.hpp>
#include <locale>
#include <sstream>
#include <iomanip>

namespace marnav
{
namespace nmea
{
void read(const std::string & s, double & value, data_format fmt)
{
	utils::unused(fmt);
	if (s.empty())
		return;

	std::istringstream is(s);
	is.imbue(std::locale::classic());
	is >> value;
	if (!is.eof())
		throw std::runtime_error{"invalid string to convert to double: [" + s + "]"};
}
}
}
