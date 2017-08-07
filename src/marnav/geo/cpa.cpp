#include "cpa.hpp"
#include <cmath>
#include <marnav/math/vector.hpp>

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
///   and the time until the closest approach is reached. Also included
///   in the result, does a CPA exist or not. If both vessels
///   go in the same direction and are parallel to eachother,
///   no CPA exists at all.
///   - Position of vessel 1 at closest point of approach
///   - Position of vessel 2 at closest point of approach
///   - TCPA
///   - CPA exists (true) or not (false)
///
/// @note This function calculates the CPA/TCPA on a plane (not sphere, not geoid).
///       This is precise enough for vessels in intresting vincinity. The farther away
///       the vessels are, the less precise the calculation gets.
///
/// Formulae:
///
/// Position of vessels and in function of time: @f{eqnarray*}{
/// V_1(t) &=& V_1(0) + t \cdot \vec{u} \\
/// V_2(t) &=& V_2(0) + t \cdot \vec{v}
/// @f}
/// with polar coordinates @f{eqnarray*}{
/// \vec{u} = (sog_1, \phi cog_1) \\
/// \vec{v} = (sog_2, \phi cog_2)
/// @f}
///
/// - @f${sog}@f$ : speed over ground
/// - @f${cog}@f$ : course over ground in degrees
///
/// The distance between the two vessels as function of time: @f[
/// \vec{d}_t = V_1(t) - V_2(t)
/// @f]
/// with @f{eqnarray*}{
/// \vec{d}_0 &=& V_1(0) - V_2(0) \\
/// \vec{d}_t &=& V_1(t) - V_2(t) = V_1(0) + t \cdot \vec{u} - V_2(0) + t \cdot \vec{v} \\
///           &=& V_1(0) - V_2(0) + t \cdot \left( \vec{u} - \vec{v} \right) \\
///           &=& \vec{d}_0 + t \cdot \left( \vec{u} - \vec{v} \right)
/// @f}
/// Closest point of approach is reached if the distance @f$\vec{d}_t@f$ is minimal:
/// @f{eqnarray*}{
/// || \vec{d}_t ||^2 &=& \vec{d}_t \cdot \vec{d}_t \\
///                   &=& \left( \vec{d}_0 + t \cdot \left( \vec{u} - \vec{v} \right) \right)^2 \\
///                   &=& {\vec{d}_0}^2 + 2\cdot\vec{d}_0\cdot t\cdot\left(\vec{u}-\vec{v}\right)
///                       + t^2\cdot\left(\vec{u}-\vec{v}\right)^2
/// @f}
/// The minimum is reached, when the first derivation becomes zero. The derivation is:
/// @f{eqnarray*}{
/// \frac{\partial}{\partial t}|| \vec{d}_t ||^2 &=&
/// 2\cdot\vec{d}_0\cdot\left(\vec{u}-\vec{v}\right)
///     + 2\cdot t\cdot\left(\vec{u}-\vec{v}\right)^2
/// @f}
/// Solving for @f$t@f$:
/// @f{eqnarray*}{
/// 0 &=& 2\cdot\vec{d}_0\cdot\left(\vec{u}-\vec{v}\right)
///       + 2\cdot t\cdot\left(\vec{u}-\vec{v}\right)^2 \\
/// -2\cdot\vec{d}_0\cdot\left(\vec{u}-\vec{v}\right) &=& 2\cdot t\cdot\left(\vec{u}-\vec{v}\right)^2 \\
/// \frac{-2\cdot\vec{d}_0\cdot\left(\vec{u}-\vec{v}\right)}{2\cdot\left(\vec{u}-\vec{v}\right)^2} &=& t \\
/// t_{CPA} &=& \frac{-\vec{d}_0\cdot\left(\vec{u}-\vec{v}\right)}{\left(\vec{u}-\vec{v}\right)^2}
/// @f}
/// If the denominator @f$\left(\vec{u}-\vec{v}\right)^2@f$ is zero, there will never be a CPA.
/// If @f$t_{CPA}@f$ is less than zero, it means CPA was reached in the past.
///
/// The location of the vessels at closest approach:
/// @f{eqnarray*}{
/// V_1(t_{CPA}) &=& V_1(0) + t_{CPA} \cdot \vec{u} \\
/// V_2(t_{CPA}) &=& V_2(0) + t_{CPA} \cdot \vec{v}
/// @f}
///
/// Example:
/// @code
/// const vessel vessel1 = {{0.0, 1.0}, 1.0, 90.0}; // being west, going east with 1kn
/// const vessel vessel2 = {{-1.0, 0.0}, 1.0, 0.0}; // being south, going north with 1k
///
/// position p1;
/// position p2;
/// std::chrono::seconds t_cpa;
/// bool cpa_exists;
/// std::tie(p1, p2, t_cpa, cpa_exists) = cpa(vessel1, vessel2);
///
/// if (cpa_exists) {
///     const double d = abs(distance_sphere(p1, p2));
///     if ((d < 3.0 * 1852.0) || (t_cpa < std::chrono::minutes{10})) {
///         // .. warning!?
///     }
/// }
/// @endcode
///
std::tuple<position, position, std::chrono::seconds, bool> cpa(
	const vessel & vessel1, const vessel & vessel2)
{
	using math::vec2;

	const vec2 v1_0{-vessel1.pos.lon(), vessel1.pos.lat()};
	const vec2 v2_0{-vessel2.pos.lon(), vessel2.pos.lat()};

	const vec2 u = vec2::make_from_polar(vessel1.sog, 90.0 - vessel1.cog);
	const vec2 v = vec2::make_from_polar(vessel2.sog, 90.0 - vessel2.cog);

	const vec2 d0 = v1_0 - v2_0;
	const vec2 t = u - v;
	const double den = t * t;
	if (std::abs(den) < 1e-7)
		return std::make_tuple<position, position, std::chrono::seconds>(
			position{0.0, 0.0}, position{0.0, 0.0}, std::chrono::seconds{0}, false);

	const double t_cpa = (-1.0 * (d0 * t)) / den;

	const vec2 v1_t = v1_0 + t_cpa * u;
	const vec2 v2_t = v2_0 + t_cpa * v;

	// we need to convert the time, because the units were nautical miles and knots.
	// there are 60nm per degree and 1kn is 1nm per hour or 3600 seconds.
	const std::chrono::duration<double> t_cpa_seconds{t_cpa * 60 * 3600};

	return std::make_tuple<position, position, std::chrono::seconds>(
		position{v1_t[1], -v1_t[0]}, position{v2_t[1], -v2_t[0]},
		std::chrono::duration_cast<std::chrono::seconds>(t_cpa_seconds), true);
}
}
}
