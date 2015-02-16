#ifndef __NMEA__ANGLE__HPP__
#define __NMEA__ANGLE__HPP__

#include <string>
#include <stdexcept>

namespace nmea
{
class angle
{
public:
	static constexpr double EPSILON = 1.0e-8;

	angle(const angle&) = default;

	angle();
	explicit angle(double value);

	/// Returns the degrees of this angle. This value is always positive.
	uint32_t degrees() const;

	/// Returns the minutes of this angle. This value is always positive
	/// and is between 0 and 59.
	uint32_t minutes() const;

	/// Returns the seconds of this angle.
	double seconds() const;

	/// Converts an angle to double, units: degrees.
	operator double() const;

	friend bool operator==(const angle& a, const angle& b) noexcept;

	angle& operator=(const angle&) = default;

	static angle parse(const std::string& s) throw(std::invalid_argument);

protected:
	double get() const;

private:
	double value; // angle in degrees
};

bool operator==(const angle& a, const angle& b) noexcept;

class latitude : public angle
{
public:
	enum class hemisphere { NORTH, SOUTH };

	latitude();
	latitude(double value) throw(std::invalid_argument);
	latitude(uint32_t d, uint32_t m, uint32_t s, hemisphere hem) throw(std::invalid_argument);

	/// Returns the corresponding hemisphere.
	hemisphere hem() const;

	static latitude parse(const std::string& s) throw(std::invalid_argument);

private:
	static void check(double a) throw(std::invalid_argument);
};

std::string to_string(const latitude& v);
std::ostream& operator<<(std::ostream& os, const latitude& p);
std::istream& operator>>(std::istream& is, latitude& t);

class longitude : public angle
{
public:
	enum class hemisphere { EAST, WEST };

	longitude();
	longitude(double value) throw(std::invalid_argument);
	longitude(uint32_t d, uint32_t m, uint32_t s, hemisphere hem) throw(std::invalid_argument);

	/// Returns the corresponding hemisphere.
	hemisphere hem() const;

	static longitude parse(const std::string& s) throw(std::invalid_argument);

private:
	static void check(double a) throw(std::invalid_argument);
};

std::string to_string(const longitude& v);
std::ostream& operator<<(std::ostream& os, const longitude& p);
std::istream& operator>>(std::istream& is, longitude& t);

}

#endif
