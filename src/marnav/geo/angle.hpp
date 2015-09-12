#ifndef __GEO__ANGLE__HPP__
#define __GEO__ANGLE__HPP__

#include <cstdint>

namespace marnav
{
namespace geo
{

/// @brief A geographic angle. This is the base class for Latitudes and Longitudes.
class angle
{
public:
	static constexpr double epsilon = 1.0e-8;

	angle(const angle &) = default;
	angle(angle &&) noexcept = default;

	angle() noexcept;
	angle(double degrees);

	uint32_t degrees() const noexcept;
	uint32_t minutes() const noexcept;
	double seconds() const noexcept;

	operator double() const noexcept;
	double get() const noexcept;

	friend bool operator==(const angle & a, const angle & b) noexcept;
	friend bool operator!=(const angle & a, const angle & b) noexcept;

	angle & operator=(const angle &) = default;
	angle & operator=(angle &&) noexcept = default;

	friend void swap(angle & a, angle & b) noexcept;

protected:
	void set(double) noexcept;

private:
	double value; // angle in degrees
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
	enum class hemisphere { NORTH, SOUTH };
	constexpr static const double min = -90.0;
	constexpr static const double max = +90.0;

	latitude() noexcept;
	latitude(double degrees);
	latitude(uint32_t d, uint32_t m, uint32_t s, hemisphere h);

	latitude(const latitude &) = default;
	latitude(latitude &&) noexcept = default;

	latitude & operator=(const latitude &) = default;
	latitude & operator=(latitude &&) noexcept = default;

	friend bool operator==(const latitude & a, const latitude & b) noexcept;
	friend bool operator!=(const latitude & a, const latitude & b) noexcept;

	/// Deletion of this operator prevents comparison of apples and oranges.
	bool operator==(const angle &) const = delete;

	/// Deletion of this operator prevents comparison of apples and oranges.
	bool operator!=(const angle &) const = delete;

	/// Returns the corresponding hemisphere.
	hemisphere hem() const noexcept;

	void change_hemisphere(hemisphere h);

private:
	static void check(double a);
};

bool operator==(const latitude & a, const latitude & b) noexcept;
bool operator!=(const latitude & a, const latitude & b) noexcept;

/// @{
/// User defined literal to construct latitudes.

inline latitude operator "" _lat(long double value)
{
	return latitude{static_cast<double>(value)};
}

inline latitude operator "" _north(long double value)
{
	return latitude{static_cast<double>(value)};
}

inline latitude operator "" _south(long double value)
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
	enum class hemisphere { EAST, WEST };
	constexpr static const double min = -180.0;
	constexpr static const double max = +180.0;

	longitude() noexcept;
	longitude(double degrees);
	longitude(uint32_t d, uint32_t m, uint32_t s, hemisphere h);

	longitude(const longitude &) = default;
	longitude(longitude &&) noexcept = default;

	longitude & operator=(const longitude &) = default;
	longitude & operator=(longitude &&) noexcept = default;

	friend bool operator==(const longitude & a, const longitude & b) noexcept;
	friend bool operator!=(const longitude & a, const longitude & b) noexcept;

	/// Deletion of this operator prevents comparison of apples and oranges.
	bool operator==(const angle &) const = delete;

	/// Deletion of this operator prevents comparison of apples and oranges.
	bool operator!=(const angle &) const = delete;

	/// Returns the corresponding hemisphere.
	hemisphere hem() const noexcept;

	void change_hemisphere(hemisphere h);

private:
	static void check(double a);
};

bool operator==(const longitude & a, const longitude & b) noexcept;
bool operator!=(const longitude & a, const longitude & b) noexcept;

/// @{
/// User defined literal to construct latitudes.

inline longitude operator "" _lon(long double value)
{
	return longitude{static_cast<double>(value)};
}

inline longitude operator "" _east(long double value)
{
	return longitude{static_cast<double>(value)};
}

inline longitude operator "" _west(long double value)
{
	return longitude{static_cast<double>(-value)};
}

/// @}

}
}

#endif
