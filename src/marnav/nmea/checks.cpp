#include "checks.hpp"

namespace marnav::nmea
{
/// Convinience function to check status.
///
/// @param[in] value The value to check.
/// @param[in] name Optional name, will be included in the exception if the check fails.
/// @exception std::invalid_argument The specified value was invalid.
void check_status(status value, const char * name)
{
	check_value(value, {status::ok, status::warning}, name);
}

/// Convinience function to check status. Check takes place only if
/// the value is set.
///
/// @param[in] value The value to check.
/// @param[in] name Optional name, will be included in the exception if the check fails.
/// @exception std::invalid_argument The specified value was invalid.
void check_status(const std::optional<status> & value, const char * name)
{
	if (value)
		check_status(value.value(), name);
}
}
