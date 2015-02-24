#ifndef __NMEA__IO__HPP__
#define __NMEA__IO__HPP__

#include "optional.hpp"
#include <sstream>

namespace nmea
{

template <class T> inline std::string to_string(const optional<T>& data)
{
	if (data) {
		using namespace std;
		return to_string(data.value());
	}
	return std::string{};
}

inline std::string to_string(const optional<double>& data)
{
	if (data) {
		char buf[32];
		snprintf(buf, sizeof(buf), "%.1f", data.value());
		return buf;
	}
	return std::string{};
}

inline std::string to_string(const optional<char>& data)
{
	if (data) {
		char buf[4];
		snprintf(buf, sizeof(buf), "%c", data.value());
		return buf;
	}
	return std::string{};
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
