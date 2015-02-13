#ifndef __NMEA__SENTENCE__HPP__
#define __NMEA__SENTENCE__HPP__

#include <functional>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include "optional.hpp"

namespace nmea
{

class latitude;
class longitude;
class time;
class date;

std::ostream& operator<<(std::ostream& os, const latitude& p);
std::istream& operator>>(std::istream& is, latitude& t);
std::ostream& operator<<(std::ostream& os, const longitude& p);
std::istream& operator>>(std::istream& is, longitude& t);
std::ostream& operator<<(std::ostream& os, const time& t);
std::istream& operator>>(std::istream& is, time& t);
std::ostream& operator<<(std::ostream& os, const date& d);
std::istream& operator>>(std::istream& is, date& d);

template <class T> std::ostream& operator<<(std::ostream& os, const optional<T>& data)
{
	if (data) {
		using namespace std;
		os << data.value();
	}
	return os;
}

template <> std::ostream& operator<<(std::ostream& os, const optional<double>& data)
{
	if (data) {
		char buf[32];
		snprintf(buf, sizeof(buf), "%.1f", data.value());
		os << buf;
	}
	return os;
}

enum class SentenceID : uint32_t {
	NONE = 0x00000000,
	RMC = 0x00000001,
	MTW = 0x00003006,
};

/// @note This class behaves like a POD, no complex data with memory operations.
class sentence
{
public:
	using parse_func = std::function<std::unique_ptr<sentence>(const std::string&,
															   const std::vector<std::string>&)>;

	constexpr static char START_TOKEN = '$';
	constexpr static char END_TOKEN = '*';

	SentenceID id() const;
	const char* tag() const;
	const char* talker() const;

	friend std::string to_string(const sentence&);

protected:
	sentence(SentenceID id, const std::string& tag, const std::string& talker);

	template <class T>
	static void read(const std::string& s, T& value)
	{
		if (s.empty()) {
			value = T{};
			return;
		}

		std::istringstream{s} >> value;
	}

	template <class T>
	static void read(const std::string& s, optional<T>& value)
	{
		if (s.empty()) {
			value.reset();
			return;
		}

		T tmp;
		std::istringstream{s} >> tmp;
		value = tmp;
	}

	virtual void append_data(std::ostream& os, const std::string& delimiter) const = 0;

private:
	const SentenceID id_;
	char tag_[4];
	char talker_[3];
};

}

#endif
