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

template <class T> inline std::ostream& operator<<(std::ostream& os, const optional<T>& data)
{
	if (data) {
		using namespace std;
		os << data.value();
	}
	return os;
}

std::ostream& operator<<(std::ostream& os, const optional<double>& data);

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

constexpr const char EAST  = 'E';
constexpr const char WEST  = 'W';
constexpr const char NORTH = 'N';
constexpr const char SOUTH = 'S';

constexpr const char STATUS_OK      = 'A';
constexpr const char STATUS_WARNING = 'V';

constexpr const char SIG_INT_AUTONOMOUS   = 'A';
constexpr const char SIG_INT_DIFFERENTIAL = 'D';
constexpr const char SIG_INT_ESTIMATED    = 'E';
constexpr const char SIG_INT_MANUALINPUT  = 'M';
constexpr const char SIG_INT_SIMULATED    = 'S';
constexpr const char SIG_INT_DATANOTVALID = 'N';

constexpr const int QUALITY_INVALID  = 0;
constexpr const int QUALITY_GPS_FIX  = 1;
constexpr const int QUALITY_DPGS_FIX = 2;
constexpr const int QUALITY_GUESS    = 6;

constexpr const char UNIT_METER   = 'M';
constexpr const char UNIT_FEET    = 'f';
constexpr const char UNIT_NM      = 'N'; // nautical miles
constexpr const char UNIT_FATHOM  = 'F';
constexpr const char UNIT_KNOT    = 'N';
constexpr const char UNIT_KMH     = 'K'; // kilometers per hour
constexpr const char UNIT_MPS     = 'M'; // meters per second
constexpr const char UNIT_CELSIUS = 'C';

constexpr const char TRUE     = 'T';
constexpr const char MAGNETIC = 'M';
constexpr const char RELATIVE = 'R';

constexpr const char LEFT  = 'L';
constexpr const char RIGHT = 'R';

constexpr const char ROUTE_COMPLETE = 'C';
constexpr const char ROUTE_WORKING  = 'W';

constexpr const char SELECTIONMODE_MANUAL    = 'M';
constexpr const char SELECTIONMODE_AUTOMATIC = 'A';

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

	void set_talker(const std::string& talker);

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
