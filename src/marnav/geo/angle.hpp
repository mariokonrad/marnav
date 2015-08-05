#ifndef __GEO__ANGLE__HPP__
#define __GEO__ANGLE__HPP__

#include <string>
#include <stdexcept>
#include <limits>

namespace marnav
{
namespace geo
{
class angle
{
public:
	static constexpr double epsilon = 1.0e-8;

	angle(const angle &) = default;
	angle(angle &&) = default;

	angle();
	explicit angle(double value);

	uint32_t degrees() const;
	uint32_t minutes() const;
	double seconds() const;

	operator double() const;
	double get() const;

	friend bool operator==(const angle & a, const angle & b) noexcept;
	friend bool operator!=(const angle & a, const angle & b) noexcept;

	angle & operator=(const angle &) = default;
	angle & operator=(angle &&) = default;

	friend void swap(angle & a, angle & b)
	{
		using namespace std;
		swap(a.value, b.value);
	}

protected:
	void set(double);

private:
	double value; // angle in degrees
};

bool operator==(const angle & a, const angle & b) noexcept;
bool operator!=(const angle & a, const angle & b) noexcept;

/// Latitude.
///
/// Value ranges between +90.0 (north) to -90.0 (south).
class latitude : public angle
{
public:
	enum class hemisphere { NORTH, SOUTH };
	constexpr static const double min = -90.0;
	constexpr static const double max = +90.0;

	latitude();
	latitude(double value) throw(std::invalid_argument);
	latitude(uint32_t d, uint32_t m, uint32_t s, hemisphere hem) throw(std::invalid_argument);

	latitude(const latitude &) = default;
	latitude(latitude &&) = default;

	latitude & operator=(const latitude &) = default;
	latitude & operator=(latitude &&) = default;

	friend bool operator==(const latitude & a, const latitude & b) noexcept;
	friend bool operator!=(const latitude & a, const latitude & b) noexcept;

	/// Deletion of this operator prevents comparison of apples and oranges.
	bool operator==(const angle &) const = delete;

	/// Deletion of this operator prevents comparison of apples and oranges.
	bool operator!=(const angle &) const = delete;

	/// Returns the corresponding hemisphere.
	hemisphere hem() const;

	void correct_hemisphere(hemisphere h);

private:
	static void check(double a) throw(std::invalid_argument);
};

bool operator==(const latitude & a, const latitude & b) noexcept;
bool operator!=(const latitude & a, const latitude & b) noexcept;

/// User defined literal to construct latitudes.
inline latitude operator "" _lat(long double value)
{
	return latitude{static_cast<double>(value)};
}

/// Longitude.
///
/// Value ranges between +180.0 (west) to -180.0 (east).
class longitude : public angle
{
public:
	enum class hemisphere { EAST, WEST };
	constexpr static const double min = -180.0;
	constexpr static const double max = +180.0;

	longitude();
	longitude(double value) throw(std::invalid_argument);
	longitude(uint32_t d, uint32_t m, uint32_t s, hemisphere hem) throw(std::invalid_argument);

	longitude(const longitude &) = default;
	longitude(longitude &&) = default;

	longitude & operator=(const longitude &) = default;
	longitude & operator=(longitude &&) = default;

	friend bool operator==(const longitude & a, const longitude & b) noexcept;
	friend bool operator!=(const longitude & a, const longitude & b) noexcept;

	/// Deletion of this operator prevents comparison of apples and oranges.
	bool operator==(const angle &) const = delete;

	/// Deletion of this operator prevents comparison of apples and oranges.
	bool operator!=(const angle &) const = delete;

	/// Returns the corresponding hemisphere.
	hemisphere hem() const;

	void correct_hemisphere(hemisphere h);

private:
	static void check(double a) throw(std::invalid_argument);
};

bool operator==(const longitude & a, const longitude & b) noexcept;
bool operator!=(const longitude & a, const longitude & b) noexcept;

/// User defined literal to construct latitudes.
inline longitude operator "" _lon(long double value)
{
	return longitude{static_cast<double>(value)};
}

}
}

#endif
