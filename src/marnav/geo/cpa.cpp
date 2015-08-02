#include "cpa.hpp"

namespace marnav
{
namespace geo
{
/// @brief Computes the CPA (closest point of approach)
/// and TCPA (time to closest point of approach).
///
/// @param[in] vessel1 Telemetry about vessel 1.
/// @param[in] vessel2 Telemetry about vessel 2.
/// @return Position of the two vessels at the closest approach
///   and the time until the closest approach is reached.
///
/// @todo Implementation
/// @todo Test
///
std::tuple<position, position, std::chrono::seconds> cpa(
	const vessel & vessel1, const vessel & vessel2)
{
	return std::make_tuple<position, position, std::chrono::seconds>(
		position{0.0, 0.0}, position{0.0, 0.0}, std::chrono::seconds{0});
}
}
}
