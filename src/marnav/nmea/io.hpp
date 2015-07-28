#ifndef __NMEA__IO__HPP__
#define __NMEA__IO__HPP__

#include <marnav/nmea/constants.hpp>
#include <marnav/utils/optional.hpp>
#include <string>
#include <stdexcept>

namespace marnav
{

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

enum class data_format { none, dec, hex };

/// @{

std::string to_string(char data);
std::string to_string(uint32_t data);
std::string to_string(double data);
std::string to_string(const std::string & data);
std::string to_string(side t);
std::string to_string(route t);
std::string to_string(selection_mode t);
std::string to_string(ais_channel t);
std::string to_string(type_of_point t);
std::string to_string(direction t);
std::string to_string(reference t);
std::string to_string(positioning_system_mode_indicator t);
std::string to_string(status t);
std::string to_string(quality t);
std::string to_string(unit::distance t);
std::string to_string(unit::velocity t);
std::string to_string(unit::temperature t);
std::string to_string(unit::pressure t);

template <class T> inline std::string to_string(const utils::optional<T> & data)
{
	if (!data)
		return std::string{};

	using namespace std;
	return to_string(data.value());
}

/// @}

/// @{

/// Returns the data as formatted string.
///
/// @param[in] data The data to format.
/// @param[in] width Minimum number of digits.
/// @param[in] f Base of the data to be rendered in
/// @exception std::invalid_argument Parameter width is too large for the implementation.
///   This is necessary to avoid heap operations and VLA.
std::string format(int32_t data, unsigned int width, data_format f = data_format::dec) throw(
	std::invalid_argument);

/// Returns the data as formatted string.
///
/// @param[in] data The data to format.
/// @param[in] width Minimum number of digits.
/// @param[in] f Base of the data to be rendered in
/// @exception std::invalid_argument Parameter width is too large for the implementation.
///   This is necessary to avoid heap operations and VLA.
std::string format(uint32_t data, unsigned int width, data_format f = data_format::dec) throw(
	std::invalid_argument);

/// Returns the data as formatted string.
///
/// @param[in] data The data to format.
/// @param[in] width Number of decimals.
/// @param[in] f Base of the data to be rendered in
/// @exception std::invalid_argument Parameter width is too large for the implementation.
///   This is necessary to avoid heap operations and VLA.
std::string format(double data, unsigned int width, data_format = data_format::none) throw(
	std::invalid_argument);

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
inline std::string format(const utils::optional<T> & data, unsigned int width,
	data_format f = data_format::dec) throw(std::invalid_argument)
{
	if (!data)
		return std::string{};
	return format(data.value(), width, f);
}

/// @}

/// @{

void read(const std::string & s, geo::latitude & value, data_format = data_format::none);
void read(const std::string & s, geo::longitude & value, data_format = data_format::none);
void read(const std::string & s, date & value, data_format = data_format::none);
void read(const std::string & s, time & value, data_format = data_format::none);
void read(const std::string & s, duration & value, data_format = data_format::none);
void read(const std::string & s, char & value, data_format = data_format::none);
void read(const std::string & s, uint32_t & value, data_format = data_format::dec);
void read(const std::string & s, int32_t & value, data_format = data_format::dec);
void read(const std::string & s, double & value, data_format = data_format::none);
void read(const std::string & s, std::string & value, data_format = data_format::none);
void read(const std::string & s, side & value, data_format = data_format::none);
void read(const std::string & s, route & value, data_format = data_format::none);
void read(const std::string & s, selection_mode & value, data_format = data_format::none);
void read(const std::string & s, ais_channel & value, data_format = data_format::none);
void read(const std::string & s, type_of_point & value, data_format = data_format::none);
void read(const std::string & s, direction & value, data_format = data_format::none);
void read(const std::string & s, reference & value, data_format = data_format::none);
void read(const std::string & s, positioning_system_mode_indicator & value,
	data_format = data_format::none);
void read(const std::string & s, status & value, data_format = data_format::none);
void read(const std::string & s, quality & value, data_format = data_format::none);
void read(const std::string & s, unit::distance & value, data_format = data_format::none);
void read(const std::string & s, unit::velocity & value, data_format = data_format::none);
void read(const std::string & s, unit::temperature & value, data_format = data_format::none);
void read(const std::string & s, unit::pressure & value, data_format = data_format::none);

template <class T>
static void read(
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

/// @}

}
}

#endif
