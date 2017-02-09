#ifndef MARNAV__UTILS__MMSI_COUNTRY__HPP
#define MARNAV__UTILS__MMSI_COUNTRY__HPP

#include <string>

namespace marnav
{
namespace utils
{
class mmsi; // forward

struct mmsi_country_info {
	uint32_t mid;
	std::string code;
	std::string name;
};

mmsi_country_info mmsi_country(const mmsi & m);
}
}

#endif
