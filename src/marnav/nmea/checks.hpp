#ifndef __NMEA__CHECKS__HPP__
#define __NMEA__CHECKS__HPP__

#include <marnav/utils/optional.hpp>
#include <string>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
void check_waypoint_id(const std::string & id) throw(std::invalid_argument);

void check_value(char value, std::initializer_list<char> options,
	const char * name = nullptr) throw(std::invalid_argument);

template <class T>
void check_value(const utils::optional<T> & value, std::initializer_list<T> options,
	const char * name = nullptr) throw(std::invalid_argument)
{
	if (value)
		check_value(value.value(), options, name);
}

void check_status(char value, const char * name = nullptr) throw(std::invalid_argument);

void check_status(const utils::optional<char> & value, const char * name = nullptr) throw(
	std::invalid_argument);
}
}

#endif
