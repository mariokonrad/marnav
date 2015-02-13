#include <iostream>
#include <sstream>
#include <string>
#include <exception>
#include <memory>
#include <algorithm>
#include <regex>
#include <vector>
#include "optional.hpp"
#include "angle.hpp"
#include "time.hpp"
#include "date.hpp"
#include "sentence.hpp"
#include "mtw.hpp"
#include "rmc.hpp"
#include "unique.hpp"

namespace nmea
{

std::ostream& operator<<(std::ostream& os, const latitude& p) { return os << to_string(p); }

std::istream& operator>>(std::istream& is, latitude& t)
{
	std::string s;
	is >> s;
	t = latitude::parse(s);
	return is;
}

std::ostream& operator<<(std::ostream& os, const longitude& p) { return os << to_string(p); }

std::istream& operator>>(std::istream& is, longitude& t)
{
	std::string s;
	is >> s;
	t = longitude::parse(s);
	return is;
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

	cout << "\n";
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

