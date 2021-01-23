#include <marnav/nmea/route.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
/// Checks the specified ID if it is valid or not.
route::route(const std::string & id)
	: id_(id)
{
	if (id.size() > 8)
		throw std::invalid_argument{"string size to large (max 8)"};
}
}
}
