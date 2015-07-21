#include "angle.hpp"
#include <cmath>

namespace marnav
{
namespace ais
{

// used only with static constant values, therefore compile time computation.
template <unsigned int n> double exp_10() { return 10.0 * exp_10<n - 1>(); }
template <> double exp_10<0>() { return 1.0; }

template <unsigned int n> double round_n(double value)
{
	const double factor = exp_10<n>();
	return std::round(value * factor) / factor;
}

/// Convertes the specified value (commin in AIS data) to latitude.
marnav::geo::latitude to_geo_latitude(uint32_t latitude_minutes)
{
	double angle = (1.0 / 60000.0) * latitude_minutes;
	angle = round_n<6>(angle);
	return geo::latitude{angle};
}

/// Converts a latitude to latitude minutes, which is commonly used in AIS data.
uint32_t to_latitude_minutes(const marnav::geo::latitude & lat) { return floor(60000.0 * lat); }

/// Convertes the specified value (commin in AIS data) to longitude.
marnav::geo::longitude to_geo_longitude(uint32_t longitude_minutes)
{
	double angle = (1.0 / 60000.0) * longitude_minutes;
	angle = round_n<6>(angle);
	return geo::longitude{angle};
}

/// Converts a longitude to longitude minutes, which is commonly used in AIS data.
uint32_t to_longitude_minutes(const marnav::geo::longitude & lon)
{
	return floor(60000.0 * lon);
}
}
}
