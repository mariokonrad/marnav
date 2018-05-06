#ifndef MARNAV__UTILS__MMSI_COUNTRY__HPP
#define MARNAV__UTILS__MMSI_COUNTRY__HPP

#include <string>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace utils
{
class mmsi; // forward

struct MARNAV_EXPORT mmsi_country_info {
	uint32_t mid;
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
	std::string code;
	std::string name;
#ifdef _MSC_VER
#pragma warning(pop)
#endif
};

MARNAV_EXPORT mmsi_country_info mmsi_country(const mmsi & m);
}
}

#endif
