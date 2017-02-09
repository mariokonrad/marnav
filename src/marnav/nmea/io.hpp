#ifndef MARNAV__NMEA__IO__HPP
#define MARNAV__NMEA__IO__HPP

#include <string>
#include <functional>
#include <marnav/nmea/constants.hpp>
#include <marnav/nmea/string.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{

namespace utils
{
class mmsi; // forward declaration
}

namespace geo
{
class latitude; // forward declaration
class longitude; // forward declaration
}

namespace nmea
{

class date; // forward declaration
class time; // forward declaration
class duration; // forward declaration
class waypoint; // forward declaration

enum class data_format { none, dec, hex };

/// @{

/// Returns the data as formatted string.
///
/// @param[in] data The data to format.
/// @param[in] width Minimum number of digits.
/// @param[in] f Base of the data to be rendered in
/// @exception std::invalid_argument Parameter width is too large for the implementation.
///   This is necessary to avoid heap operations and VLA.
std::string format(int32_t data, unsigned int width, data_format f = data_format::dec);

/// Returns the data as formatted string.
///
/// @param[in] data The data to format.
/// @param[in] width Minimum number of digits.
/// @param[in] f Base of the data to be rendered in
/// @exception std::invalid_argument Parameter width is too large for the implementation.
///   This is necessary to avoid heap operations and VLA.
std::string format(uint64_t data, unsigned int width, data_format f = data_format::dec);

/// Returns the data as formatted string.
///
/// @param[in] data The data to format.
/// @param[in] width Minimum number of digits.
/// @param[in] f Base of the data to be rendered in
/// @exception std::invalid_argument Parameter width is too large for the implementation.
///   This is necessary to avoid heap operations and VLA.
std::string format(uint32_t data, unsigned int width, data_format f = data_format::dec);

/// Returns the data as formatted string.
///
/// @param[in] data The data to format.
/// @param[in] width Number of decimals.
/// @param[in] f Base of the data to be rendered in
/// @exception std::invalid_argument Parameter width is too large for the implementation.
///   This is necessary to avoid heap operations and VLA.
std::string format(double data, unsigned int width, data_format f = data_format::none);

/// Generic version of the format function, handling the possibility of utils::optional
/// to be not set and returning an empty string. The rendering of the contained type
/// is one of the overloaded funtions of 'format'.
///
/// @param[in] data Data to be rendered if valid.
/// @param[in] width Formatting information.
/// @param[in] f Number base information.
/// @return The string containing the formatted value, an empty string if the optional
///   was not set.
/// @tparam T Inner type of the optional, i.e. the acutal type to format.
/// @exception std::invalid_argument Parameter width is too large for the implementation.
///   This is necessary to avoid heap operations and VLA.
template <typename T>
inline std::string format(
	const utils::optional<T> & data, unsigned int width, data_format f = data_format::dec)
{
	if (!data)
		return std::string{};
	return format(data.value(), width, f);
}

/// @}

/// @{

void read(const std::string & s, geo::latitude & value, data_format fmt = data_format::none);
void read(const std::string & s, geo::longitude & value, data_format fmt = data_format::none);
void read(const std::string & s, date & value, data_format fmt = data_format::none);
void read(const std::string & s, time & value, data_format fmt = data_format::none);
void read(const std::string & s, duration & value, data_format fmt = data_format::none);
void read(const std::string & s, char & value, data_format fmt = data_format::none);
void read(const std::string & s, uint64_t & value, data_format fmt = data_format::dec);
void read(const std::string & s, uint32_t & value, data_format fmt = data_format::dec);
void read(const std::string & s, int32_t & value, data_format fmt = data_format::dec);
void read(const std::string & s, double & value, data_format fmt = data_format::none);
void read(const std::string & s, std::string & value, data_format fmt = data_format::none);
void read(const std::string & s, side & value, data_format fmt = data_format::none);
void read(const std::string & s, route & value, data_format fmt = data_format::none);
void read(const std::string & s, selection_mode & value, data_format fmt = data_format::none);
void read(const std::string & s, ais_channel & value, data_format fmt = data_format::none);
void read(const std::string & s, type_of_point & value, data_format fmt = data_format::none);
void read(const std::string & s, direction & value, data_format fmt = data_format::none);
void read(const std::string & s, reference & value, data_format fmt = data_format::none);
void read(const std::string & s, mode_indicator & value, data_format fmt = data_format::none);
void read(const std::string & s, status & value, data_format fmt = data_format::none);
void read(const std::string & s, quality & value, data_format fmt = data_format::none);
void read(const std::string & s, target_status & value, data_format fmt = data_format::none);
void read(const std::string & s, unit::distance & value, data_format fmt = data_format::none);
void read(const std::string & s, unit::velocity & value, data_format fmt = data_format::none);
void read(
	const std::string & s, unit::temperature & value, data_format fmt = data_format::none);
void read(const std::string & s, unit::pressure & value, data_format fmt = data_format::none);
void read(const std::string & s, utils::mmsi & value, data_format fmt = data_format::none);
void read(const std::string & s, waypoint & value, data_format fmt = data_format::none);

template <class T>
inline void read(
	const std::string & s, utils::optional<T> & value, data_format fmt = data_format::dec)
{
	if (s.empty()) {
		value.reset();
		return;
	}

	T tmp;
	read(s, tmp, fmt);
	value = tmp;
}

/// This variant of read enums from the string using a mapping function.
///
/// @tparam T Enumeration to be read
/// @tparam Map Mapping function to map from enumeatiors underlying type to the enumeration.
///
/// @param[in] s The string to read from.
/// @param[out] value The place where the read data will be stored
/// @param[in] mapping_func The mapping function for the enumerator.
/// @param[in] fmt Format specifier
template <class T, typename Map,
	typename = typename std::enable_if<std::is_enum<T>::value, T>::type>
inline void read(
	const std::string & s, T & value, Map mapping_func, data_format fmt = data_format::dec)
{
	using uT = typename std::underlying_type<T>::type;
	uT t = uT{};
	read(s, t, fmt);
	if (mapping_func) {
		value = mapping_func(t);
	} else {
		value = static_cast<T>(t);
	}
}

/// This variant of read enums from the string using a mapping function. This function
/// applies if the specified value is wrapped in a utils::optional.
///
/// @tparam T Enumeration to be read
/// @tparam Map Mapping function to map from enumeatiors underlying type to the enumeration.
///
/// @param[in] s The string to read from.
/// @param[out] value The place where the read data will be stored
/// @param[in] mapping_func The mapping function for the enumerator.
/// @param[in] fmt Format specifier
template <class T, typename Map,
	typename = typename std::enable_if<std::is_class<utils::optional<T>>::value, T>::type,
	typename = typename std::enable_if<std::is_enum<T>::value, T>::type>
inline void read(const std::string & s, utils::optional<T> & value, Map mapping_func,
	data_format fmt = data_format::dec)
{
	if (s.empty()) {
		value.reset();
		return;
	}

	T tmp;
	read(s, tmp, mapping_func, fmt);
	value = tmp;
}

/// @}
}
}

#endif
