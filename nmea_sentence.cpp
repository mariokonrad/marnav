#include <iostream>
#include <sstream>
#include <string>
#include <exception>
#include <memory>
#include <algorithm>
#include <regex>
#include <vector>

namespace std
{
/// This is part of the C++14 standard.
template <class T, class... Args> std::unique_ptr<T> make_unique(Args&&... args)
{
	return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
}

namespace nmea
{

template <class T> class optional //{{{
{
public:
	using value_type = T;

	constexpr optional()
		: flag(false)
		, data()
	{
	}

	constexpr optional(const T& data)
		: flag(true)
		, data(data)
	{
	}

	constexpr optional(T&& data)
		: flag(true)
		, data(std::move(data))
	{
	}

	optional(optional&&) = default;
	optional(const optional&) = default;

	void reset()
	{
		data = T{};
		flag = false;
	}

	bool available() const { return flag; }
	explicit operator bool() const { return flag; }

	constexpr const T& value() const { return data; }
	T& value() { return data; }

	optional& operator=(const optional& other)
	{
		this->data = other.data;
		this->flag = other.flag;
		return *this;
	}

	optional& operator=(optional&& other)
	{
		this->data = std::move(other.data);
		this->flag = std::move(other.flag);
		return *this;
	}

	template <class U>
	optional& operator=(U&& data)
	{
		this->data = std::move(data);
		flag = true;
		return *this;
	}

	constexpr const T* operator->() const { return &data; }
	T* operator->() { return &data; }
	constexpr const T& operator*() const { return data; }
	T& operator*() { return data; }

private:
	bool flag;
	T data;
};

template <class T>
std::ostream& operator<<(std::ostream& os, const optional<T>& data)
{
	if (data) {
		using namespace std;
		os << data.value();
	}
	return os;
}

template <>
std::ostream& operator<<(std::ostream& os, const optional<double>& data)
{
	if (data) {
		char buf[32];
		snprintf(buf, sizeof(buf), "%.1f", data.value());
		os << buf;
	}
	return os;
}

//}}}

class angle //{{{
{
public:
	static constexpr double EPSILON = 1.0e-8;

	angle(const angle&) = default;

	angle()
		: value(0.0)
	{
	}

	explicit angle(double value)
		: value(value)
	{
	}

	/// This constructs an angle from the specified string.
	/// If the string is not readable, an exception is thrown.
	angle(const std::string& s) throw(std::runtime_error);

	/// Returns the degrees of this angle. This value is always positive.
	uint32_t degrees() const
	{
		auto a = fabs(get());
		a = floor(a);
		return static_cast<uint32_t>(a);
	}

	/// Returns the minutes of this angle. This value is always positive
	/// and is between 0 and 59.
	uint32_t minutes() const
	{
		auto a = fabs(get());
		a -= floor(a);
		a *= 60.0;
		a += EPSILON;
		return static_cast<uint32_t>(a);
	}

	/// Returns the seconds of this angle.
	double seconds() const
	{
		auto a = fabs(get());
		a -= floor(a);
		a *= 60.0;
		a += EPSILON;
		a -= floor(a);
		a *= 60.0;
		return a;
	}

	/// Converts an angle to double, units: degrees.
	operator double() const { return value; }

	friend bool operator==(const angle& a, const angle& b) noexcept;

	angle& operator=(const angle&) = default;

	static angle parse(const std::string& s) throw(std::invalid_argument);

protected:
	double get() const { return value; }

private:
	double value; // angle in degrees
};

bool operator==(const angle& a, const angle& b) noexcept
{
	return (&a == &b) || (a.value == b.value);
}

angle angle::parse(const std::string& s) throw(std::invalid_argument)
{
	if (s.empty())
		return angle{0.0};
	std::size_t pos = 0;
	auto tmp = std::stod(s, &pos);
	if (pos != s.size())
		throw std::invalid_argument{"invalid string for conversion to nmea::angle"};

	// adoption of NMEA angle DDDMM.SSS to the one that is used here
	const double deg = (tmp - fmod(tmp, 100.0)) / 100.0;
	const double min = (tmp - (deg * 100.0)) / 60.0;

	if (fabs(min) >= 1.0)
		throw std::invalid_argument{"invalid format for minutes in nmea::angle"};

	return angle{deg + min};
}

class latitude : public angle
{
public:
	enum class hemisphere { NORTH, SOUTH };

	latitude()
		: angle(0.0)
	{
	}

	latitude(double value)
		: angle(value)
	{
		check(get());
	}

	explicit latitude(uint32_t d, uint32_t m, uint32_t s, hemisphere hem)
		: angle((static_cast<double>(d) + static_cast<double>(m) / 60.0
				 + static_cast<double>(s) / 3600.0) * ((hem == hemisphere::SOUTH) ? -1.0 : 1.0))
	{
		check(get());
	}

	/// Returns the corresponding hemisphere.
	hemisphere hem() const { return get() >= 0.0 ? hemisphere::NORTH : hemisphere::SOUTH; }

	static latitude parse(const std::string& s) throw(std::invalid_argument);

private:
	static void check(double a) throw(std::invalid_argument);
};

void latitude::check(double a) throw(std::invalid_argument)
{
	if ((a < -90.0) || (a > 90.0))
		throw std::invalid_argument{"invalid value for nmea::latitude"};
}

std::string to_string(const latitude& v)
{
	char buf[32];
	snprintf(buf, sizeof(buf), "%02u%02u.%04u", v.degrees(), v.minutes(),
					static_cast<uint32_t>((v.seconds() / 60) * 10000));
	return buf;
}

std::ostream& operator<<(std::ostream& os, const latitude& p)
{
	return os << to_string(p);
}

std::istream& operator>>(std::istream& is, latitude& t)
{
	std::string s;
	is >> s;
	t = latitude::parse(s);
	return is;
}

latitude latitude::parse(const std::string& s) throw(std::invalid_argument)
{
	auto a = angle::parse(s);
	check(a);
	return latitude{a};
}

class longitude : public angle
{
public:
	enum class hemisphere { EAST, WEST };

	longitude()
		: angle(0.0)
	{
	}

	longitude(double value)
		: angle(value)
	{
		check(*this);
	}

	explicit longitude(uint32_t d, uint32_t m, uint32_t s, hemisphere hem)
		: angle((static_cast<double>(d) + static_cast<double>(m) / 60.0
				 + static_cast<double>(s) / 3600.0) * ((hem == hemisphere::EAST) ? -1.0 : 1.0))
	{
		check(*this);
	}

	/// Returns the corresponding hemisphere.
	hemisphere hem() const { return get() >= 0.0 ? hemisphere::WEST : hemisphere::EAST; }

	static longitude parse(const std::string& s) throw(std::invalid_argument);

private:
	static void check(double a) throw(std::invalid_argument);
};

void longitude::check(double a) throw(std::invalid_argument)
{
	if ((a < -180.0) || (a > 180.0))
		throw std::invalid_argument{"invalid value for nmea::longitude"};
}

longitude longitude::parse(const std::string& s) throw(std::invalid_argument)
{
	auto a = angle::parse(s);
	check(a);
	return longitude{a};
}

std::string to_string(const longitude& v)
{
	char buf[32];
	snprintf(buf, sizeof(buf), "%03u%02u.%04u", v.degrees(), v.minutes(),
			 static_cast<uint32_t>(10000 * v.seconds() / 60));
	return buf;
}

std::ostream& operator<<(std::ostream& os, const longitude& p)
{
	return os << to_string(p);
}

std::istream& operator>>(std::istream& is, longitude& t)
{
	std::string s;
	is >> s;
	t = longitude::parse(s);
	return is;
}

//}}}

class time //{{{
{
public:
	time()
		: h(0)
		, m(0)
		, s(0)
		, ms(0)
	{
	}

	time(const time&) = default;

	explicit time(uint32_t h, uint32_t m, uint32_t s, uint32_t ms) throw(std::invalid_argument)
		: h(h)
		, m(m)
		, s(s)
		, ms(ms)
	{
		// TODO: replace this poor mans time check

		if (h > 23)
			throw std::invalid_argument{"invalid hour in nmea::time"};
		if (m > 59)
			throw std::invalid_argument{"invalid minute in nmea::time"};
		if (s > 59)
			throw std::invalid_argument{"invalid second in nmea::time"};
		if (ms > 999)
			throw std::invalid_argument{"invalid milliseconds in nmea::time"};
	}

	/// Returns the hour component.
	uint32_t hour() const { return h; }

	/// Returns the minutes component.
	uint32_t minutes() const { return m; }

	/// Returns the seconds component.
	uint32_t seconds() const { return s; }

	/// Returns the milliseconds component.
	uint32_t milliseconds() const { return ms; }

	friend bool operator==(const time& a, const time& b) noexcept;

	/// Parses the time information within the specified string (start and end of string).
	/// If the string is empty, the result will be initialized to zero.
	/// The time to be parsed must  be in the form: "HHMMSS.mmm" (milliseconds are optional).
	///  - HH  : zero leading hour of the day (00..23)
	///  - MM  : zero leading minute of the hour (00..59)
	///  - SS  : zero leading second of the minute (00..59)
	///  - mmm : milliseconds (000..999)
	///
	/// @param[in] s start of string to parse (inclusive)
	/// @param[in] e end of string to parse (exclusive)
	/// @param[out] endptr Points the end of the parsed string.
	/// @return The parsed time
	static time parse(const std::string& str) throw(std::invalid_argument);

private:
	uint32_t h; // hour: 0..23
	uint32_t m; // minute: 0..59
	uint32_t s; // second: 0..59
	uint32_t ms; // millisecond: 0..999
};

std::string to_string(const time& d)
{
	char buf[7];
	snprintf(buf, sizeof(buf), "%02u%02u%02u", d.hour(), d.minutes(), d.seconds());
	return buf;
}

std::ostream& operator<<(std::ostream& os, const time& t)
{
	return os << to_string(t);
}

std::istream& operator>>(std::istream& is, time& t)
{
	std::string s;
	is >> s;
	t = time::parse(s);
	return is;
}

bool operator==(const time& a, const time& b) noexcept
{
	return (&a == &b) || ((a.h == b.h) && (a.m == b.m) && (a.s == b.s) && (a.ms == b.ms));
}

time time::parse(const std::string& str) throw(std::invalid_argument)
{
	try {
		std::size_t pos = 0;
		double t = std::stod(str, &pos);
		if (pos != str.size())
			throw std::invalid_argument{"invalid format for 'double'"};

		const uint32_t h = static_cast<uint32_t>(t / 10000) % 100;
		const uint32_t m = static_cast<uint32_t>(t / 100) % 100;
		const uint32_t s = static_cast<uint32_t>(t) % 100;
		const uint32_t ms = static_cast<uint32_t>(t * 1000) % 1000;
		return time{h, m, s, ms};
	} catch (std::invalid_argument) {
		throw std::invalid_argument{"invalid time format, 'HHMMSS[.mmm]' expected"};
	}
}

//}}}

class date //{{{
{
public:
	date()
		: y(0)
		, m(0)
		, d(0)
	{
	}

	date(uint32_t y, uint32_t m, uint32_t d) throw(std::invalid_argument)
		: y(y)
		, m(m)
		, d(d)
	{
		// TODO: replace this poor mans date check

		if ((m <= 0) || (m > 12))
			throw std::invalid_argument{"invalid month"};
		if ((m == 2) && (d > 29))
			throw std::invalid_argument{"invalid day"};
		if ((d <= 0) || (d > 31))
			throw std::invalid_argument{"invalid day"};
	}

	/// Returns the year component.
	uint32_t year() const { return y; }

	/// Returns the month component.
	uint32_t month() const { return m; }

	/// Returns the day component.
	uint32_t day() const { return d; }

	friend bool operator==(const date& a, const date& b);

	/// Parses the date within the specified string.
	/// The date to be parsed must be in the form: "DDMMYY"
	static date parse(const std::string& str) throw(std::invalid_argument);

private:
	uint32_t y; // year
	uint32_t m; // month: 1..12
	uint32_t d; // day: 1..31
};

bool operator==(const date& a, const date& b)
{
	return (&a == &b) || ((a.y == b.y) && (a.m == b.m) && (a.d == b.d));
}

std::string to_string(const date& d)
{
	char buf[7];
	snprintf(buf, sizeof(buf), "%02u%02u%02u", d.day(), d.month(), d.year());
	return buf;
}

std::ostream& operator<<(std::ostream& os, const date& d)
{
	return os << to_string(d);
}

std::istream& operator>>(std::istream& is, date& d)
{
	std::string s;
	is >> s;
	d = date::parse(s);
	return is;
}

date date::parse(const std::string& str) throw(std::invalid_argument)
{
	try {
		std::size_t pos = 0;
		uint32_t t = std::stoul(str, &pos);
		if (pos != str.size())
			throw std::invalid_argument{"invalid format for date"};
		return date{t % 100, (t / 100) % 100, (t / 10000) % 100};
	} catch (std::invalid_argument) {
		throw std::invalid_argument{"invalid date format, 'DDMMYY' expected"};
	}
}

//}}}

enum class SentenceID : uint32_t {
	NONE = 0x00000000,
	RMC = 0x00000001,
	MTW = 0x00003006,
};

std::ostream& operator<<(std::ostream& os, SentenceID id)
{
	switch (id) {
		case SentenceID::NONE:
			os << "NONE";
			break;
		case SentenceID::MTW:
			os << "MTW";
			break;
		case SentenceID::RMC:
			os << "RMC";
			break;
		default:
			os << "<unknown>";
			break;
	}
	return os;
}

class checksum_error : public std::exception
{
};

//{{{sentence

/// @note This class behaves like a POD, no complex data with memory operations.
class sentence
{
public:
	using parse_func = std::function<std::unique_ptr<sentence>(const std::string&,
															   const std::vector<std::string>&)>;

	constexpr static char START_TOKEN = '$';
	constexpr static char END_TOKEN = '*';

	SentenceID id() const { return id_; }
	const char* tag() const { return tag_; }
	const char* talker() const { return talker_; }

	friend std::string to_string(const sentence&);

protected:
	sentence(SentenceID id, const std::string& tag, const std::string& talker)
		: id_(id)
	{
		std::copy_n(tag.c_str(), 3, this->tag_);
		std::copy_n(talker.c_str(), 2, this->talker_);
		this->tag_[3] = 0;
		this->talker_[2] = 0;
	}

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
	static void read(const std::string& s, nmea::optional<T>& value)
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
}; //}}}

class mtw : public sentence //{{{
{
public:
	constexpr static const SentenceID ID = SentenceID::MTW;

	mtw(const std::string& talker) : sentence(ID, "MTW", talker) {}

	static std::unique_ptr<sentence>
	parse(const std::string& talker,
		  const std::vector<std::string>& fields) throw(std::invalid_argument)
	{
		if (fields.size() != 2)
			throw std::invalid_argument{"invalid number of fields in mtw::parse"};

		std::unique_ptr<sentence> result = std::make_unique<mtw>(talker);
		mtw& detail = static_cast<mtw&>(*result);

		read(fields[0], detail.temperature);
		read(fields[1], detail.unit);

		return result;
	}

protected:
	virtual void append_data(std::ostream& os, const std::string& delimiter) const override
	{
		os << delimiter;
		os << temperature;
		os << delimiter;
		os << unit;
	}

private:
	nmea::optional<double> temperature; // water temperature
	nmea::optional<char> unit; // unit degrees, C:celcius

public:
	decltype(temperature) get_temperature() const { return temperature; }
	decltype(unit) get_unit() const { return unit; }
}; //}}}

class rmc : public sentence //{{{
{
public:
	constexpr static const SentenceID ID = SentenceID::RMC;

	rmc(const std::string& talker) : sentence(ID, "RMC", talker) {}

	static std::unique_ptr<sentence>
	parse(const std::string& talker,
		  const std::vector<std::string>& fields) throw(std::invalid_argument)
	{
		// before and after NMEA 2.3
		if ((fields.size() < 11) || (fields.size() > 12))
			throw std::invalid_argument{"invalid number of fields in rmc::parse"};

		std::unique_ptr<sentence> result = std::make_unique<rmc>(talker);
		rmc& detail = static_cast<rmc&>(*result);

		read(fields[0], detail.time_utc);
		read(fields[1], detail.status);
		read(fields[2], detail.lat);
		read(fields[3], detail.lat_hem);
		read(fields[4], detail.lon);
		read(fields[5], detail.lon_hem);
		read(fields[6], detail.sog);
		read(fields[7], detail.heading);
		read(fields[8], detail.date);
		read(fields[9], detail.mag);
		read(fields[10], detail.mag_hem);

		// NMEA 2.3 or newer
		if (fields.size() > 11)
			read(fields[11], detail.faa_mode_indicator);

		return result;
	}

protected:
	virtual void append_data(std::ostream& os, const std::string& delimiter) const override
	{
		os << delimiter;
		os << time_utc;
		os << delimiter;
		os << status;
		os << delimiter;
		os << lat;
		os << delimiter;
		os << lat_hem;
		os << delimiter;
		os << lon;
		os << delimiter;
		os << lon_hem;
		os << delimiter;
		os << sog;
		os << delimiter;
		os << heading;
		os << delimiter;
		os << date;
		os << delimiter;
		os << mag;
		os << delimiter;
		os << mag_hem;
		os << delimiter;
		os << faa_mode_indicator;
	}

private:
	nmea::optional<nmea::time> time_utc;
	nmea::optional<char> status;
	nmea::optional<nmea::latitude> lat;
	nmea::optional<char> lat_hem;
	nmea::optional<nmea::longitude> lon;
	nmea::optional<char> lon_hem;
	nmea::optional<double> sog;
	nmea::optional<double> heading;
	nmea::optional<nmea::date> date;
	nmea::optional<double> mag;
	nmea::optional<char> mag_hem;
	nmea::optional<char> faa_mode_indicator;

public:
	decltype(time_utc) get_time_utc() const { return time_utc; }
	decltype(status) get_status() const { return status; }
	decltype(lat) get_lat() const { return lat; }
	decltype(lat_hem) get_lat_hem() const { return lat_hem; }
	decltype(lon) get_lon() const { return lon; }
	decltype(lon_hem) get_lon_hem() const { return lon_hem; }
	decltype(sog) get_sog() const { return sog; }
	decltype(heading) get_heading() const { return heading; }
	decltype(date) get_date() const { return date; }
	decltype(mag) get_mag() const { return mag; }
	decltype(mag_hem) get_mag_hem() const { return mag_hem; }
	decltype(faa_mode_indicator) get_faa_mode_indicator() const { return faa_mode_indicator; }
}; //}}}

template <class T>
std::unique_ptr<T> sentence_cast(std::unique_ptr<sentence>& s)
{
	if (!s)
		return nullptr;
	if (s->id() != T::ID)
		return nullptr;

	return std::unique_ptr<T>{static_cast<T*>(s.release())};
}

sentence::parse_func instantiate_sentence(const std::string& tag) throw(std::invalid_argument)
{
	using namespace std;

	using entry = std::pair<std::string, sentence::parse_func>;
	static const std::vector<entry> known_sentences = {{"RMC", rmc::parse}, {"MTW", mtw::parse}};

	auto const& i = std::find_if(begin(known_sentences), end(known_sentences),
								 [tag](const entry& e) { return e.first == tag; });

	if (i == end(known_sentences))
		throw std::invalid_argument{"unknown sentence in instantiate_sentence"};

	return i->second;
}

std::unique_ptr<sentence> make_sentence(const std::string& s) throw(std::invalid_argument,
																	checksum_error)
{
	using namespace std;

	// perform various checks

	if (s.empty())
		throw invalid_argument{"empty string in make_sentence"};

	if (s[0] != sentence::START_TOKEN)
		throw invalid_argument{"no start token in make_sentence"};

	auto const end_pos = s.find_first_of(sentence::END_TOKEN, 1);

	if (s.size() != end_pos + 3)
		throw invalid_argument{"invalid format in make_sentence"};

	const string::const_iterator end = begin(s) + end_pos;

	uint8_t checksum = 0x00;
	for_each(begin(s) + 1, end, [&checksum](char c) { checksum ^= c; });
	size_t pos = 0;
	if (checksum != stoul(s.substr(end_pos + 1, 2), &pos, 16))
		throw checksum_error{};

	if (end_pos < 7) // talker id (2), tag (3), first comma (1)
		throw invalid_argument{"malformed sentence in make_sentence"};

	// extract particular data
	const std::string tag = s.substr(3, 3);
	const std::string talker = s.substr(1, 2);
	const std::string data = s.substr(7, end_pos - 7);

	// extract fields from data
	std::regex field_regex{","};
	auto fields_begin = std::sregex_token_iterator{data.begin(), data.end(), field_regex, -1};
	auto fields_end = std::sregex_token_iterator();
	std::vector<std::string> fields{fields_begin, fields_end};

	return instantiate_sentence(tag)(talker, fields);
}

std::string to_string(const sentence& s)
{
	std::ostringstream os;
	os << sentence::START_TOKEN;
	os << s.talker();
	os << s.tag();
	s.append_data(os, ",");
	os << sentence::END_TOKEN;
	std::string result = os.str();

	uint8_t checksum = 0x00;
	for_each(result.begin() + 1, result.end() - 1, [&checksum](char c) { checksum ^= c; });
	char buf[3];
	snprintf(buf, sizeof(buf), "%02X", checksum);

	return result + buf;
}

}

static void test(const std::string& text)
{
	using std::cout;
	using namespace nmea;

	auto s = make_sentence(text);
	cout << "id=" << s->id() << "  tag=" << s->tag() << "  talker=" << s->talker() << "\n";

	{
		auto tmp = nmea::sentence_cast<nmea::mtw>(s);
		if (tmp) {
			cout << "org: " << text << "\n";
			cout << "new: " << to_string(*tmp) << "\n";
		}
	}
	{
		auto tmp = nmea::sentence_cast<nmea::rmc>(s);
		if (tmp) {
			cout << "org: " << text << "\n";
			cout << "new: " << to_string(*tmp) << "\n";
		}
	}
}

int main(int, char**)
{
	test("$IIMTW,9.5,C*2F");
	test("$GPRMC,,V,,,,,,,300510,0.6,E,N*39");
	test("$GPRMC,201034,A,4702.4040,N,00818.3281,E,0.0,328.4,260807,0.6,E,A*17");

	std::cout << "sizeof(sentence) = " << sizeof(nmea::sentence) << "\n";
	std::cout << "sizeof(rmc)      = " << sizeof(nmea::rmc) << "\n";
	std::cout << "sizeof(mtw)      = " << sizeof(nmea::mtw) << "\n";

	return 0;
}

