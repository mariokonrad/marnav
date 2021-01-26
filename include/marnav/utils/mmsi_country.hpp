#ifndef MARNAV_UTILS_MMSI_COUNTRY_HPP
#define MARNAV_UTILS_MMSI_COUNTRY_HPP

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
