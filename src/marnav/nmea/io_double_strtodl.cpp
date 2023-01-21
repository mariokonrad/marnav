#include <marnav/nmea/io.hpp>
#include <marnav/utils/unused.hpp>
#include <clocale>
#include <stdexcept>

#if defined(__APPLE__)
	#include <xlocale.h>
#else
	#include <cstdlib>
#endif

namespace marnav::nmea
{
void read(const std::string & s, double & value, data_format fmt)
{
	utils::unused(fmt);
	if (s.empty())
		return;

	static const locale_t locale = ::newlocale(LC_NUMERIC_MASK, "C", nullptr);

	char * endptr = nullptr;
	value = ::strtod_l(s.c_str(), &endptr, locale);
	if (endptr != s.c_str() + s.size())
		throw std::runtime_error{"invalid string to convert to double: [" + s + "]"};
}
}
