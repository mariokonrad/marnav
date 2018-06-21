#ifndef MARNAV__GEO__ANGLE__HPP
#define MARNAV__GEO__ANGLE__HPP

#include <cstdint>
#include <string>

namespace marnav
{
namespace geo
{

/// @brief A geographic angle. This is the base class for Latitudes and Longitudes.
class angle
{
public:
	constexpr static double epsilon() noexcept { return 1.0e-8; }

	angle(const angle &) = default;
	angle(angle &&) noexcept = default;

	constexpr angle() noexcept
		: value_(0.0)
	{
	}

	/// Initializes the angle with the specified angle in degrees.
	///
	/// @param[in] degrees Angle in degrees.
	constexpr angle(double degrees) noexcept
		: value_(degrees)
	{
	}

	uint32_t degrees() const noexcept;
	uint32_t minutes() const noexcept;
	double seconds() const noexcept;

	/// Converts an angle to double, units: degrees.
	constexpr operator double() const noexcept { return value_; }

	constexpr double get() const noexcept { return value_; }

	angle & operator=(const angle &) = default;
	angle & operator=(angle &&) noexcept = default;

	friend void swap(angle & a, angle & b) noexcept;

protected:
	/// Sets the angle in degrees.
	///
	/// Not part of the public interface intentionally.
	void set(double degrees) noexcept { value_ = degrees; }

private:
	double value_; // angle in degrees
};

void swap(angle & a, angle & b) noexcept;
bool operator==(const angle & a, const angle & b) noexcept;
bool operator!=(const angle & a, const angle & b) noexcept;

/// @brief Geographic Latitude
///
/// Value ranges between +90.0 (north) to -90.0 (south).
class latitude : public angle
{
public:
	enum class hemisphere { north, south };

	constexpr static double min() noexcept { return -90.0; }
	constexpr static double max() noexcept { return +90.0; }

	constexpr latitude() noexcept
		: angle(0.0)
	{
	}

	latitude(double degrees);
	latitude(double degrees, hemisphere h);
	latitude(uint32_t d, uint32_t m, uint32_t s, hemisphere h);

	latitude(const latitude &) = default;
	latitude(latitude &&) noexcept = default;

	latitude & operator=(const latitude &) = default;
	latitude & operator=(latitude &&) noexcept = default;

	/// Deletion of this operator prevents comparison of apples and oranges.
	bool operator==(const angle &) const = delete;

	/// Deletion of this operator prevents comparison of apples and oranges.
	bool operator!=(const angle &) const = delete;

	/// Returns the corresponding hemisphere.
	constexpr hemisphere hem() const noexcept
	{
		return get() >= 0.0 ? hemisphere::north : hemisphere::south;
	}

private:
	static void check(double a);
};

bool operator==(const latitude & a, const latitude & b) noexcept;
bool operator!=(const latitude & a, const latitude & b) noexcept;
std::string to_string(latitude::hemisphere h);

/// @{
/// User defined literal to construct latitudes.

inline latitude operator"" _lat(long double value)
{
	return latitude{static_cast<double>(value)};
}

inline latitude operator"" _north(long double value)
{
	return latitude{static_cast<double>(value)};
}

inline latitude operator"" _south(long double value)
{
	return latitude{static_cast<double>(-value)};
}

///@}

/// @brief Geographic Longitude
///
/// Value ranges between -180.0 (west) to +180.0 (east).
class longitude : public angle
{
public:
	enum class hemisphere { east, west };

	constexpr static double min() noexcept { return -180.0; }
	constexpr static double max() noexcept { return +180.0; }

	constexpr longitude() noexcept
		: angle(0.0)
	{
	}

	longitude(double degrees);
	longitude(double degrees, hemisphere h);
	longitude(uint32_t d, uint32_t m, uint32_t s, hemisphere h);

	longitude(const longitude &) = default;
	longitude(longitude &&) noexcept = default;

	longitude & operator=(const longitude &) = default;
	longitude & operator=(longitude &&) noexcept = default;

	/// Deletion of this operator prevents comparison of apples and oranges.
	bool operator==(const angle &) const = delete;

	/// Deletion of this operator prevents comparison of apples and oranges.
	bool operator!=(const angle &) const = delete;

	/// Returns the corresponding hemisphere.
	constexpr hemisphere hem() const noexcept
	{
		return get() < 0.0 ? hemisphere::west : hemisphere::east;
	}

private:
	static void check(double a);
};

bool operator==(const longitude & a, const longitude & b) noexcept;
bool operator!=(const longitude & a, const longitude & b) noexcept;
std::string to_string(longitude::hemisphere h);

/// @{
/// User defined literal to construct latitudes.

inline longitude operator"" _lon(long double value)
{
	return longitude{static_cast<double>(value)};
}

inline longitude operator"" _east(long double value)
{
	return longitude{static_cast<double>(value)};
}

inline longitude operator"" _west(long double value)
{
	return longitude{static_cast<double>(-value)};
}

/// @}
}
}

#endif
