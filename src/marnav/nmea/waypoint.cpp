#include <marnav/nmea/waypoint.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
/// Checks the specified ID if it is valid or not.
waypoint::waypoint(const std::string & id)
	: id_(id)
{
	if (id.size() > 8)
		throw std::invalid_argument{"string size to large (max 8)"};
}
}
}
