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

template <class T> inline std::ostream& operator<<(std::ostream& os, const optional<T>& data)
{
	if (data) {
		using namespace std;
		os << data.value();
	}
	return os;
}

template <> inline std::ostream& operator<<(std::ostream& os, const optional<double>& data)
{
	if (data) {
		char buf[32];
		snprintf(buf, sizeof(buf), "%.1f", data.value());
		os << buf;
	}
	return os;
}

// TODO: not a complete list
enum class SentenceID : uint32_t {
	NONE = 0x00000000,

	// standard sentences
	RMB,
	RMC,
	GGA,
	GSA,
	GSV,
	GLL,
	RTE,
	VTG,
	BOD,
	DPT,

	// garmin specific
	RME,
	RMM,
	RMZ,

	// vendor extensions
	HDG,

	// integrated instumentation
	MWV, // wind values
	VWR, // wind relative
	VWT, // wind true
	DBT, // water depth
	VLW, // log distance
	VHW, // heading
	MTW, // temperature water
};

constexpr char EAST  = 'E';
constexpr char WEST  = 'W';
constexpr char NORTH = 'N';
constexpr char SOUTH = 'S';

constexpr char STATUS_OK      = 'A';
constexpr char STATUS_WARNING = 'V';

constexpr char SIG_INT_AUTONOMOUS   = 'A';
constexpr char SIG_INT_DIFFERENTIAL = 'D';
constexpr char SIG_INT_ESTIMATED    = 'E';
constexpr char SIG_INT_MANUALINPUT  = 'M';
constexpr char SIG_INT_SIMULATED    = 'S';
constexpr char SIG_INT_DATANOTVALID = 'N';

constexpr int QUALITY_INVALID  = 0;
constexpr int QUALITY_GPS_FIX  = 1;
constexpr int QUALITY_DPGS_FIX = 2;
constexpr int QUALITY_GUESS    = 6;

constexpr char UNIT_METER   = 'M';
constexpr char UNIT_FEET    = 'f';
constexpr char UNIT_NM      = 'N'; // nautical miles
constexpr char UNIT_FATHOM  = 'F';
constexpr char UNIT_KNOT    = 'N';
constexpr char UNIT_KMH     = 'K'; // kilometers per hour
constexpr char UNIT_MPS     = 'M'; // meters per second
constexpr char UNIT_CELSIUS = 'C';

constexpr char TRUE     = 'T';
constexpr char MAGNETIC = 'M';
constexpr char RELATIVE = 'R';

constexpr char LEFT  = 'L';
constexpr char RIGHT = 'R';

constexpr char ROUTE_COMPLETE = 'C';
constexpr char ROUTE_WORKING  = 'W';

constexpr char SELECTIONMODE_MANUAL    = 'M';
constexpr char SELECTIONMODE_AUTOMATIC = 'A';

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

std::string to_string(const sentence& s);

}

#endif
