#ifndef MARNAV_MATH_CONSTATNS_HPP
#define MARNAV_MATH_CONSTATNS_HPP

namespace marnav
{
namespace math
{
/// M_PI is not defined by either the C or C++ standard.
/// One solution would be to use `_USE_MATH_DEFINES`,
/// another to define it ourselfs, either as constant or
/// `std::atan(-1.0)*4` or `std::acos(-1.0)`.
///
/// @todo This should be a variable template (>=C++14)
constexpr double pi = 3.141592653589793238463;
}
}

#endif
