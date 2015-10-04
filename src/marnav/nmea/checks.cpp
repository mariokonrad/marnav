#include "checks.hpp"

namespace marnav
{
namespace nmea
{
/// Checks the validity of the specified waypoint ID.
///
/// @param[in] id The waypoint ID to check.
///
/// @exception std::invalid_argument The waypoint ID is invalid.
void check_waypoint_id(const std::string & id)
{
	if (id.size() > 8)
		throw std::invalid_argument{"string size to large, only 8 characters allowed for id"};
}

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
void check_status(const utils::optional<status> & value, const char * name)
{
	if (value)
		check_status(value.value(), name);
}
}
}
