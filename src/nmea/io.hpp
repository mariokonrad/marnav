#ifndef __NMEA__IO__HPP__
#define __NMEA__IO__HPP__

#include "optional.hpp"
#include <sstream>
#include <string>

namespace nmea
{

template <class T> inline std::string to_string(const optional<T>& data)
{
	if (!data)
		return std::string{};

	using namespace std;
	return to_string(data.value());
}

template <> inline std::string to_string(const optional<uint32_t>& data)
{
	if (!data)
		return std::string{};

	return std::to_string(data.value());
}

inline std::string to_string(const optional<uint32_t>& data, unsigned int width)
{
	if (!data)
		return std::string{};
	char fmt[8];
	snprintf(fmt, sizeof(fmt), "%%0%uu", width);
	char buf[width + 8];
	snprintf(buf, sizeof(buf), fmt, data.value());
	return buf;
}

template <> inline std::string to_string(const optional<double>& data)
{
	if (!data)
		return std::string{};

	char buf[32];
	snprintf(buf, sizeof(buf), "%.1f", data.value());
	return buf;
}

template <> inline std::string to_string(const optional<char>& data)
{
	if (!data)
		return std::string{};

	char buf[4];
	snprintf(buf, sizeof(buf), "%c", data.value());
	return buf;
}

template <class T> static void read(const std::string& s, T& value)
{
	if (s.empty()) {
		value = T{};
		return;
	}

	using namespace std;
	std::istringstream{s} >> value;
}

template <class T> static void read(const std::string& s, optional<T>& value)
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

}

#endif
