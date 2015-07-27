#ifndef __NMEA__CHECKS__HPP__
#define __NMEA__CHECKS__HPP__

#include <marnav/nmea/constants.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/optional.hpp>
#include <string>
#include <stdexcept>
#include <sstream>
#include <algorithm>

namespace marnav
{
namespace nmea
{
template <typename T>
static void throw_elaborated_invalid_argument(T value, std::initializer_list<T> options,
	const char * name = nullptr) throw(std::invalid_argument)
{
	using namespace std;

	ostringstream os;
	os << "invalid argument, value '" << to_string(value) << "' not in options:{";
	for (auto const & opt : options)
		os << " " << to_string(opt);
	os << " }";
	if (name)
		os << " for '" << name << "'";
	throw invalid_argument{os.str()};
}

/// Checks the value agains a list of possible values.
///
/// @param[in] value Value to check.
/// @param[in] options Possible values to check against.
/// @param[in] name Optional name of the value to check. This name will be mentioned
///   in thrown exception, if the value is invalid.
///
/// @exception std::invalid_argument The value is not listed in the options.
template <class T>
void check_value(T value, std::initializer_list<T> options, const char * name = nullptr) throw(
	std::invalid_argument)
{
	using namespace std;
	if (find_if(begin(options), end(options), [value](T opt) { return value == opt; })
		!= end(options))
		return;

	throw_elaborated_invalid_argument(value, options, name);
}

template <class T>
void check_value(const utils::optional<T> & value, std::initializer_list<T> options,
	const char * name = nullptr) throw(std::invalid_argument)
{
	if (value)
		check_value(value.value(), options, name);
}

void check_waypoint_id(const std::string & id) throw(std::invalid_argument);

void check_status(char value, const char * name = nullptr) throw(std::invalid_argument);

void check_status(const utils::optional<char> & value, const char * name = nullptr) throw(
	std::invalid_argument);
}
}

#endif
