#include "tag_block.hpp"
#include <algorithm>
#include <stdexcept>
#include <type_traits>
#include <marnav/nmea/detail.hpp>
#include <marnav/nmea/split.hpp>

namespace marnav
{
namespace nmea
{
/// @cond DEV
namespace
{
static tag_block::sentence_group extract_group(const std::string & s)
{
	static constexpr char DELIMITER = '-';

	tag_block::sentence_group group;

	std::string::size_type first = 2;
	std::string::size_type last = 0;

	last = s.find(DELIMITER, first);
	group.number = std::stoi(s.substr(first, last - first));

	first = last + 1u;
	last = s.find(DELIMITER, first);
	group.total_number = std::stoi(s.substr(first, last - first));

	first = last + 1u;
	last = s.find(DELIMITER, first);
	group.id = std::stoi(s.substr(first, last - first));

	return group;
}

/// Extracts a string of max size 15 characters, ignoring the first two.
static std::string extract_string(const std::string & s)
{
	return s.substr(2, std::min(std::string::size_type{15u}, s.size() - 2u));
}

/// Extracts an int, ignoring the first two.
static int extract_int(const std::string & s)
{
	return std::stoi(s.substr(2, std::string::npos));
}
}
/// @endcond

static_assert(std::is_default_constructible<tag_block>::value, "");

tag_block::tag_block(const std::string & s)
{
	if (s.empty())
		throw std::invalid_argument{"invalid argument in nmea/tag_block"};

	const auto fields = detail::parse_fields(s, 0u);
	if (fields.size() < 1u)
		throw std::invalid_argument{"malformed tag block in nmea/tag_block"};

	detail::ensure_checksum(s, fields.back(), 0u);

	// it is assumed, each field has the form "x:yyy" with 'x' as the field type (1 character),
	// a delimiter of one colon (':', 1 character), followed by the data.

	// all fields, except the checksum
	for (auto i = std::begin(fields); i != std::prev(std::end(fields)); ++i) {
		const std::string & t = *i;
		if (t.size() < 3u)
			continue;
		switch (t[0]) {
			case 'c':
				unix_time = std::stoll(t.substr(2, std::string::npos));
				break;
			case 'd':
				destination = extract_string(t);
				break;
			case 'g':
				group = extract_group(t);
				break;
			case 'n':
				line_count = extract_int(t);
				break;
			case 'r':
				relative_time = extract_int(t);
				break;
			case 's':
				source = extract_string(t);
				break;
			case 't':
				text = extract_string(t);
				break;
			default:
				throw std::invalid_argument{"invalid field in nmea/tag_block"};
		}
	}
}

void tag_block::set_destination(const std::string & t)
{
	destination = (t.size() <= 15u) ? t : t.substr(0, 15);
}

void tag_block::set_source(const std::string & t)
{
	source = (t.size() <= 15u) ? t : t.substr(0, 15);
}

void tag_block::set_text(const std::string & t)
{
	text = (t.size() <= 15u) ? t : t.substr(0, 15);
}

/// Parses the specified string and returns the tag block from it.
tag_block make_tag_block(const std::string & s)
{
	return {s};
}

/// @cond DEV
namespace
{
static std::string & extend(std::string & s, const std::string & t)
{
	if (s.size() > 0u)
		s += ',';
	s += t;
	return s;
}
}
/// @endcond

/// Returns a string representing the group as string, usable directly
/// within the tag block.
std::string to_string(const tag_block::sentence_group & g)
{
	if (!g.is_valid())
		return {};

	return std::string{"g:"} + std::to_string(g.number) + "-" + std::to_string(g.total_number)
		+ "-" + std::to_string(g.id);
}

/// Returns a string representing the tag block. The string does not
/// contain the start and end tokens.
///
/// @param[in] b The tag block to render as string.
/// @return The tag block as string. If the tag block contained no
///   data, the string will be empty.
std::string to_string(const tag_block & b)
{
	std::string result;

	extend(result, to_string(b.get_group()));
	if (b.is_line_count_valid())
		extend(result,  "n:" + std::to_string(b.get_line_count()));
	if (b.is_relative_time_valid())
		extend(result,  "r:" + std::to_string(b.get_relative_time()));
	if (b.is_unix_time_valid())
		extend(result,  "c:" + std::to_string(b.get_unix_time()));
	if (b.is_destination_valid())
		extend(result,  "d:" + b.get_destination());
	if (b.is_source_valid())
		extend(result,  "s:" + b.get_source());
	if (b.is_text_valid())
		extend(result,  "t:" + b.get_text());

	return result;
}
}
}
