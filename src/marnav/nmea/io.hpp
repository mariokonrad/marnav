#ifndef __NMEA__IO__HPP__
#define __NMEA__IO__HPP__

#include <marnav/utils/optional.hpp>
#include <string>

namespace marnav
{

namespace geo {
class latitude; // forward declaration
class longitude; // forward declaration
}

namespace nmea
{

class date; // forward declaration
class time; // forward declaration
class duration; // forward declaration

enum class data_format { none, dec, hex };

std::string to_string(char data);
std::string to_string(uint32_t data);
std::string to_string(double data);
std::string to_string(const std::string & data);

template <class T> inline std::string to_string(const utils::optional<T> & data)
{
	if (!data)
		return std::string{};

	using namespace std;
	return to_string(data.value());
}

std::string format(int32_t data, unsigned int width, data_format f = data_format::dec);
std::string format(uint32_t data, unsigned int width, data_format f = data_format::dec);
std::string format(double data, unsigned int width, data_format = data_format::none);

template <typename T>
inline std::string format(
	const utils::optional<T> & data, unsigned int width, data_format f = data_format::dec)
{
	if (!data)
		return std::string{};
	return format(data.value(), width, f);
}


void read(const std::string & s, geo::latitude & value, data_format = data_format::none);
void read(const std::string & s, geo::longitude & value, data_format = data_format::none);
void read(const std::string & s, date & value, data_format = data_format::none);
void read(const std::string & s, time & value, data_format = data_format::none);
void read(const std::string & s, duration & value, data_format = data_format::none);
void read(const std::string & s, char & value, data_format = data_format::none);
void read(const std::string & s, uint32_t & value, data_format = data_format::dec);
void read(const std::string & s, int32_t & value, data_format = data_format::dec);
void read(const std::string & s, double & value, data_format = data_format::none);
void read(const std::string & s, std::string & value, data_format = data_format::none);

template <class T>
static void read(
	const std::string & s, utils::optional<T> & value, data_format fmt = data_format::dec)
{
	if (s.empty()) {
		value.reset();
		return;
	}

	T tmp;
	read(s, tmp, fmt);
	value = tmp;
}

}
}

#endif
