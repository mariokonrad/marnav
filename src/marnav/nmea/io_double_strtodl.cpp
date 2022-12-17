#include <marnav/nmea/io.hpp>
#include <marnav/utils/unused.hpp>
#include <clocale>
#include <stdexcept>

#if defined(__APPLE__)
	#include <xlocale.h>
#else
	#include <cstdlib>
#endif

#ifdef _WIN32
        #define strtod_l _strtod_l
#endif

namespace marnav
{
namespace nmea
{
void read(const std::string & s, double & value, data_format fmt)
{
	utils::unused(fmt);
	if (s.empty())
		return;

#ifndef _WIN32
	static const locale_t locale = ::newlocale(LC_NUMERIC_MASK, "C", nullptr);
#else
        static const _locale_t locale = ::_create_locale(LC_NUMERIC, "C");
#endif


	char * endptr = nullptr;
	value = ::strtod_l(s.c_str(), &endptr, locale);
	if (endptr != s.c_str() + s.size())
		throw std::runtime_error{"invalid string to convert to double: [" + s + "]"};
}
}
}
