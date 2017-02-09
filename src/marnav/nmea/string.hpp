#ifndef MARNAV__NMEA__STRING__HPP
#define MARNAV__NMEA__STRING__HPP

#include <string>
#include <marnav/nmea/constants.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace utils
{
class mmsi; // forward declaration
}

namespace nmea
{
/// @{

std::string to_string(char data);
std::string to_string(uint64_t data);
std::string to_string(uint32_t data);
std::string to_string(int32_t data);
std::string to_string(double data);
std::string to_string(const std::string & data);
std::string to_string(side t);
std::string to_string(route t);
std::string to_string(selection_mode t);
std::string to_string(ais_channel t);
std::string to_string(type_of_point t);
std::string to_string(direction t);
std::string to_string(reference t);
std::string to_string(mode_indicator t);
std::string to_string(status t);
std::string to_string(quality t);
std::string to_string(target_status t);
std::string to_string(unit::distance t);
std::string to_string(unit::velocity t);
std::string to_string(unit::temperature t);
std::string to_string(unit::pressure t);
std::string to_string(const utils::mmsi & t);

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
