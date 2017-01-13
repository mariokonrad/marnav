#ifndef __MARNAV__UTILS__MMSI_COUNTRY__HPP__
#define __MARNAV__UTILS__MMSI_COUNTRY__HPP__

#include <string>

namespace marnav
{
namespace utils
{
class mmsi; // forward

struct mmsi_country_info
{
	uint32_t mid;
	std::string code;
	std::string name;
};

mmsi_country_info mmsi_country(const mmsi & m);
}
}

#endif
