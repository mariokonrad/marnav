#ifndef __GEO__ANGLE__HPP__
#define __GEO__ANGLE__HPP__

#include <string>
#include <stdexcept>

namespace marnav
{
namespace geo
{
class angle
{
public:
	static constexpr double EPSILON = 1.0e-8;

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

class latitude : public angle
{
public:
	enum class hemisphere { NORTH, SOUTH };

	latitude();
	latitude(double value) throw(std::invalid_argument);
	latitude(uint32_t d, uint32_t m, uint32_t s, hemisphere hem) throw(std::invalid_argument);

	latitude(const latitude &) = default;
	latitude(latitude &&) = default;

	latitude & operator=(const latitude &) = default;
	latitude & operator=(latitude &&) = default;

	/// Returns the corresponding hemisphere.
	hemisphere hem() const;

	void correct_hemisphere(hemisphere h);

private:
	static void check(double a) throw(std::invalid_argument);
};

class longitude : public angle
{
public:
	enum class hemisphere { EAST, WEST };

	longitude();
	longitude(double value) throw(std::invalid_argument);
	longitude(uint32_t d, uint32_t m, uint32_t s, hemisphere hem) throw(std::invalid_argument);

	longitude(const longitude &) = default;
	longitude(longitude &&) = default;

	longitude & operator=(const longitude &) = default;
	longitude & operator=(longitude &&) = default;

	/// Returns the corresponding hemisphere.
	hemisphere hem() const;

	void correct_hemisphere(hemisphere h);

private:
	static void check(double a) throw(std::invalid_argument);
};
}
}

#endif
