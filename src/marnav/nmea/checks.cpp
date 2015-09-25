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

void check_status(status value, const char * name)
{
	check_value(value, {status::ok, status::warning}, name);
}

void check_status(const utils::optional<status> & value, const char * name)
{
	if (value)
		check_status(value.value(), name);
}
}
}
