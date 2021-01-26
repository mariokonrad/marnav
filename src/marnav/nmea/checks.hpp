#ifndef MARNAV_NMEA_CHECKS_HPP
#define MARNAV_NMEA_CHECKS_HPP

#include <marnav/nmea/constants.hpp>
#include <marnav/nmea/string.hpp>
#include <marnav/utils/optional.hpp>
#include <algorithm>
#include <stdexcept>
#include <string>

namespace marnav
{
namespace nmea
{
/// @cond DEV
namespace
{
template <typename T>
static void throw_elaborated_invalid_argument(
	T value, std::initializer_list<T> options, const char * name = nullptr)
{
	std::string text;
	text.reserve(64);
	text += "invalid argument, value '";
	text += to_string(value);
	text += "' not in options:{";
	for (auto const & opt : options) {
		text += ' ';
		text += to_string(opt);
	}
	text += " }";
	if (name) {
		text += " for '";
		text += name;
		text += '\'';
	}
	throw std::invalid_argument{text};
}
}
/// @endcond

/// Checks the value agains a list of possible values.
///
/// @param[in] value Value to check.
/// @param[in] options Possible values to check against.
/// @param[in] name Optional name of the value to check. This name will be mentioned
///   in thrown exception, if the value is invalid.
///
/// @exception std::invalid_argument The value is not listed in the options.
template <class T>
void check_value(T value, std::initializer_list<T> options, const char * name = nullptr)
{
	using namespace std;
	if (find_if(begin(options), end(options), [value](T opt) { return value == opt; })
		!= end(options))
		return;

	throw_elaborated_invalid_argument(value, options, name);
}

template <class T>
void check_value(const utils::optional<T> & value, std::initializer_list<T> options,
	const char * name = nullptr)
{
	if (value)
		check_value(value.value(), options, name);
}

void check_status(status value, const char * name = nullptr);

void check_status(const utils::optional<status> & value, const char * name = nullptr);
}
}

#endif
