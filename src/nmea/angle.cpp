#include "angle.hpp"
#include <cmath>

namespace nmea
{
geo::angle parse_angle(const std::string& s) throw(std::invalid_argument)
{
	if (s.empty())
		return geo::angle{0.0};
	std::size_t pos = 0;
	auto tmp = std::stod(s, &pos);
	if (pos != s.size())
		throw std::invalid_argument{"invalid string for conversion to geo::angle for NMEA"};

	// adoption of NMEA angle DDDMM.SSS to the one that is used here
	const double deg = (tmp - fmod(tmp, 100.0)) / 100.0;
	const double min = (tmp - (deg * 100.0)) / 60.0;

	if (fabs(min) >= 1.0)
		throw std::invalid_argument{"invalid format for minutes in geo::angle for NMEA"};

	return geo::angle{deg + min};
}

geo::latitude parse_latitude(const std::string& s) throw(std::invalid_argument)
{
	return geo::latitude{parse_angle(s)};
}

std::string to_string(const geo::latitude& v)
{
	char buf[32];
	snprintf(buf, sizeof(buf), "%02u%02u.%04u", v.degrees(), v.minutes(),
			 static_cast<uint32_t>((v.seconds() / 60) * 10000));
	return buf;
}

geo::longitude parse_longitude(const std::string& s) throw(std::invalid_argument)
{
	return geo::longitude{parse_angle(s)};
}

std::string to_string(const geo::longitude& v)
{
	char buf[32];
	snprintf(buf, sizeof(buf), "%03u%02u.%04u", v.degrees(), v.minutes(),
			 static_cast<uint32_t>(10000 * v.seconds() / 60));
	return buf;
}

}
