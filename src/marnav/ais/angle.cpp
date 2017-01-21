#include "angle.hpp"
#include <limits>
#include <cmath>
#include <cassert>

namespace marnav
{
namespace ais
{
/// @cond DEV
namespace
{
/// Returns the numeric scale for the specified enumeration.
static double scale_value(angle_scale scale)
{
	switch (scale) {
		case angle_scale::I1:
			return 10.0;
		case angle_scale::I3:
			return 1000.0;
		case angle_scale::I4:
			return 10000.0;
	}
	return 1.0;
}

/// Converts the specified value into an angle (unit: degrees) according
/// to the encoded angle in AIS messages. The specified value is a signed value.
///
/// This conversion function is suitable for both, latitudes and longitudes.
///
/// @param[in] value The value from the AIS message to convert.
/// @param[in] bits Number of bits of information.
/// @param[in] scale Angle scaling.
/// @return The converted angle, positive and negative values possible.
static double deg_from(uint32_t value, std::size_t bits, angle_scale scale)
{
	assert(bits > 0);
	assert(bits < 33);

	const uint32_t t = 1u << (bits - 1);
	if (value & t) {
		// treat negative values
		uint32_t mask = std::numeric_limits<uint32_t>::max();
		mask <<= bits;
		value |= mask;
	}
	return (1.0 / (60.0 * scale_value(scale))) * static_cast<int32_t>(value);
}

/// Converts angles in degrees to I4 values, used in AIS messages.
///
/// This conversion function is suitable for both, latitudes and longitudes.
///
/// @param[in] value The angle to convert, may be positive or negative.
/// @param[in] bits Number of bits of information in the AIS message.
/// @param[in] scale Angle scaling.
/// @return The converted angle to be used in AIS messages.
static uint32_t deg_to(double value, std::size_t bits, angle_scale scale)
{
	assert(bits > 0);
	assert(bits < 33);

	uint32_t mask = std::numeric_limits<uint32_t>::max();
	mask <<= bits;
	return static_cast<uint32_t>(floor((60.0 * scale_value(scale)) * value)) & ~mask;
}

// used only with static constant values, therefore compile time computation.
template <unsigned int n> double exp_10()
{
	return 10.0 * exp_10<n - 1>();
}
template <> double exp_10<0>()
{
	return 1.0;
}

template <unsigned int n> double round_n(double value)
{
	const double factor = exp_10<n>();
	return std::round(value * factor) / factor;
}
}
/// @endcond

/// Convertes the specified value (commin in AIS data) to latitude.
marnav::geo::latitude to_geo_latitude(
	uint32_t latitude_minutes, std::size_t bits, angle_scale scale)
{
	return geo::latitude{round_n<6>(deg_from(latitude_minutes, bits, scale))};
}

/// Converts a latitude to latitude minutes, which is commonly used in AIS data.
uint32_t to_latitude_minutes(
	const marnav::geo::latitude & lat, std::size_t bits, angle_scale scale)
{
	return deg_to(lat.get(), bits, scale);
}

/// Convertes the specified value (commin in AIS data) to longitude.
marnav::geo::longitude to_geo_longitude(
	uint32_t longitude_minutes, std::size_t bits, angle_scale scale)
{
	return geo::longitude{round_n<6>(deg_from(longitude_minutes, bits, scale))};
}

/// Converts a longitude to longitude minutes, which is commonly used in AIS data.
uint32_t to_longitude_minutes(
	const marnav::geo::longitude & lon, std::size_t bits, angle_scale scale)
{
	return deg_to(lon.get(), bits, scale);
}
}
}
