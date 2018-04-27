#include "rate_of_turn.hpp"
#include <limits>
#include <stdexcept>
#include <cmath>

namespace marnav
{
namespace ais
{
namespace
{
template <class T> constexpr T sqr(T x)
{
	return x * x;
}

template <class T> constexpr int sign(T x)
{
	return (x < 0) ? -1 : +1;
}
}

rate_of_turn::rate_of_turn(double deg_per_minute)
{
	const int x = sign(deg_per_minute)
		* static_cast<int>(std::round(4.733 * std::sqrt(std::abs(deg_per_minute))));
	if ((x > 126) || (x < -126))
		throw std::invalid_argument{"invalid value"};
	value_ = x;
}

double rate_of_turn::value() const
{
	if (!available())
		throw std::domain_error{"not available"};
	if (is_more_5deg30s_right() || is_more_5deg30s_left())
		throw std::domain_error{"value ambiguous"};
	return sign(value_) * sqr(static_cast<double>(value_) / 4.733);
}
}
}
