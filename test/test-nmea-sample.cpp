#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/name.hpp>
#include <fstream>
#include <iostream>
#include <string>

namespace stackoverflow
{
// source:
// http://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
//
// changes:
// - old-style C type cast changed to c++ cast
// - reformatting
// - renaming and put into the namespace
// - break inserted for the default option of switch
std::istream & getline(std::istream & is, std::string & t)
{
	t.clear();

	// The characters in the stream are read one-by-one using a std::streambuf.
	// That is faster than reading them one-by-one using the std::istream.
	// Code that uses streambuf this way must be guarded by a sentry object.
	// The sentry object performs various tasks,
	// such as thread synchronization and updating the stream state.

	std::istream::sentry se(is, true);
	std::streambuf * sb = is.rdbuf();

	for (;;) {
		int c = sb->sbumpc();
		switch (c) {
			case '\n':
				return is;
			case '\r':
				if (sb->sgetc() == '\n')
					sb->sbumpc();
				return is;
			case EOF:
				// Also handle the case when the last line has no line ending
				if (t.empty())
					is.setstate(std::ios::eofbit);
				return is;
			default:
				t += static_cast<char>(c);
				break;
		}
	}
}
}

int main(int, char **)
{
	using namespace marnav;

	std::ifstream ifs{"nmea-sample.txt"};
	std::string line;

	// this function implements almost the same as examples/read_ais.cpp

	while (stackoverflow::getline(ifs, line)) {
		try {
			if (line.empty())
				continue;

			if (line[0] == '#')
				continue;

			auto sentence = nmea::make_sentence(line);
			std::cout << sentence->tag() << " - " << to_name(sentence->id()) << '\n';
		} catch (nmea::unknown_sentence & e) {
			std::cout << "NMEA unknown: " << e.what() << ": " << line << '\n';
		} catch (std::exception & e) {
			std::cout << "NMEA error: " << e.what() << " in sentence: " << line << '\n';
		}
	}

	return 0;
}
