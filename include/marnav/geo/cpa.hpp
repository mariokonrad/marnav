#ifndef MARNAV_GEO_CPA_HPP
#define MARNAV_GEO_CPA_HPP

#include <marnav/geo/position.hpp>
#include <chrono>
#include <tuple>

namespace marnav
{
namespace geo
{

/// @brief This struct contains data about a vessel, needed to
/// compute CPA and TCPA.
struct vessel {
	position pos; ///< Current position of vessel.
	double sog; ///< Speed over ground in knots.
	double cog; ///< Course over ground in degrees.
};

std::tuple<position, position, std::chrono::seconds, bool> cpa(
	const vessel & vessel1, const vessel & vessel2);
}
}

#endif
