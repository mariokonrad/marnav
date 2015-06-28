#ifndef __NMEA__IO__HPP__
#define __NMEA__IO__HPP__

#include "angle.hpp"
#include <marnav/utils/optional.hpp>
#include <sstream>
#include <string>

namespace marnav
{
namespace nmea
{

template <class T> inline std::string to_string(const utils::optional<T> & data)
{
	if (!data)
		return std::string{};

	using namespace std;
	return to_string(data.value());
}

template <> inline std::string to_string(const utils::optional<std::string> & data)
{
	if (!data)
		return std::string{};

	return data.value();
}

inline std::string to_string(char data)
{
	char buf[3];
	snprintf(buf, sizeof(buf), "%c", data);
	return buf;
}

inline std::string to_string(uint32_t data) { return std::to_string(data); }

inline std::string to_string(double data)
{
	char buf[32];
	snprintf(buf, sizeof(buf), "%g", data);
	return buf;
}

inline std::string to_string(const std::string & data) { return data; }

template <> inline std::string to_string(const utils::optional<uint32_t> & data)
{
	if (!data)
		return std::string{};

	return std::to_string(data.value());
}

template <> inline std::string to_string(const utils::optional<double> & data)
{
	if (!data)
		return std::string{};

	char buf[32];
	snprintf(buf, sizeof(buf), "%g", data.value());
	return buf;
}

template <> inline std::string to_string(const utils::optional<char> & data)
{
	if (!data)
		return std::string{};

	char buf[4];
	snprintf(buf, sizeof(buf), "%c", data.value());
	return buf;
}

inline std::string format(int32_t data, unsigned int width)
{
	char fmt[8];
	snprintf(fmt, sizeof(fmt), "%%0%ud", width);
	char buf[width + 8];
	snprintf(buf, sizeof(buf), fmt, data);
	return buf;
}

inline std::string format(uint32_t data, unsigned int width)
{
	char fmt[8];
	snprintf(fmt, sizeof(fmt), "%%0%uu", width);
	char buf[width + 8];
	snprintf(buf, sizeof(buf), fmt, data);
	return buf;
}

inline std::string format(double data, unsigned int width)
{
	char fmt[8];
	snprintf(fmt, sizeof(fmt), "%%.%uf", width);
	char buf[width + 8];
	snprintf(buf, sizeof(buf), fmt, data);
	return buf;
}

template <typename T>
inline std::string format(const utils::optional<T> & data, unsigned int width)
{
	if (!data)
		return std::string{};
	return format(data.value(), width);
}

template <class T> static void read(const std::string & s, T & value)
{
	if (s.empty()) {
		value = T{};
		return;
	}

	using namespace std;
	std::istringstream{s} >> value;
}

inline void read(const std::string & s, geo::latitude & value)
{
	if (s.empty()) {
		value = geo::latitude{};
		return;
	}

	value = parse_latitude(s);
}

inline void read(const std::string & s, geo::longitude & value)
{
	if (s.empty()) {
		value = geo::longitude{};
		return;
	}

	value = parse_longitude(s);
}

template <class T> static void read(const std::string & s, utils::optional<T> & value)
{
	if (s.empty()) {
		value.reset();
		return;
	}

	using namespace std;
	T tmp;
	std::istringstream{s} >> tmp;
	value = tmp;
}

inline void read(const std::string & s, utils::optional<geo::latitude> & value)
{
	if (s.empty()) {
		value.reset();
		return;
	}
	geo::latitude tmp;
	read(s, tmp);
	value = tmp;
}

inline void read(const std::string & s, utils::optional<geo::longitude> & value)
{
	if (s.empty()) {
		value.reset();
		return;
	}
	geo::longitude tmp;
	read(s, tmp);
	value = tmp;
}
}
}

#endif
