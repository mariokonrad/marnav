#ifndef MARNAV__NMEA__STRING__HPP
#define MARNAV__NMEA__STRING__HPP

#include <string>
#include <marnav/nmea/constants.hpp>
#include <marnav/utils/optional.hpp>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace utils
{
class mmsi; // forward declaration
}

namespace nmea
{
/// @{

MARNAV_EXPORT std::string to_string(char data);
MARNAV_EXPORT std::string to_string(uint64_t data);
MARNAV_EXPORT std::string to_string(uint32_t data);
MARNAV_EXPORT std::string to_string(int32_t data);
MARNAV_EXPORT std::string to_string(double data);
MARNAV_EXPORT std::string to_string(const std::string & data);
MARNAV_EXPORT std::string to_string(side t);
MARNAV_EXPORT std::string to_string(route t);
MARNAV_EXPORT std::string to_string(selection_mode t);
MARNAV_EXPORT std::string to_string(ais_channel t);
MARNAV_EXPORT std::string to_string(type_of_point t);
MARNAV_EXPORT std::string to_string(direction t);
MARNAV_EXPORT std::string to_string(reference t);
MARNAV_EXPORT std::string to_string(mode_indicator t);
MARNAV_EXPORT std::string to_string(status t);
MARNAV_EXPORT std::string to_string(quality t);
MARNAV_EXPORT std::string to_string(target_status t);
MARNAV_EXPORT std::string to_string(unit::distance t);
MARNAV_EXPORT std::string to_string(unit::velocity t);
MARNAV_EXPORT std::string to_string(unit::temperature t);
MARNAV_EXPORT std::string to_string(unit::pressure t);
MARNAV_EXPORT std::string to_string(const utils::mmsi & t);

template <class T> inline std::string to_string(const utils::optional<T> & data)
{
	if (!data)
		return std::string{};

	using namespace std;
	return to_string(data.value());
}

/// @}
}
}

#endif
