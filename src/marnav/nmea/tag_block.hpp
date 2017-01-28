#ifndef __MARNAV__NMEA__TAG_BLOCK__HPP__
#define __MARNAV__NMEA__TAG_BLOCK__HPP__

#include <string>

namespace marnav
{
namespace nmea
{
/// This structure holds all possible data, specified by a tag block,
/// preceeding a NMEA sentence.
struct tag_block {
public:
	struct sentence_group {
		int number = 0;
		int total_number = 0;
		int id = 0;
	};

public:
	tag_block() = default;
	tag_block(const std::string & s);

	tag_block(const tag_block &) = default;
	tag_block & operator=(const tag_block &) = default;

	tag_block(tag_block &&) = default;
	tag_block & operator=(tag_block &&) = default;

public:
	int64_t get_unix_time() const { return unix_time; }
	int get_line_count() const { return line_count; }
	int get_relative_time() const { return relative_time; }
	sentence_group get_group() const { return group; }
	std::string get_destination() const { return destination; }
	std::string get_source() const { return source; }
	std::string get_text() const { return text; }

	void set_unix_time(int64_t t) { unix_time = t; }
	void set_line_count(int t) { line_count = t; }
	void set_relative_time(int t) { relative_time = t; }
	void set_group(sentence_group t) { group = t; }
	void set_destination(const std::string & t);
	void set_source(const std::string & t);
	void set_text(const std::string & t);

private:
	/// Unix time stamp.
	/// Integral value greater than zero.
	int64_t unix_time = 0;

	/// Destination, max. 15 characters.
	std::string destination;

	sentence_group group;

	/// Integral value greater than zero.
	int line_count = 0;

	/// Integral value greater than zero.
	int relative_time = 0;

	std::string source;

	/// Text string, max. 15 characters.
	std::string text;
};

tag_block make_tag_block(const std::string & s);
}
}

#endif
