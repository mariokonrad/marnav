#include "binary_data.hpp"
#include <algorithm>

namespace marnav
{
namespace ais
{
/// @cond DEV
namespace
{
struct sixbit_entry {
	uint8_t value;
	char c;
};

class sixbit_span
{
public:
	constexpr sixbit_span(const sixbit_entry * first, const sixbit_entry * last)
		: first_(first)
		, last_(last)
	{
	}

	constexpr const sixbit_entry * begin() const { return first_; }
	constexpr const sixbit_entry * end() const { return last_; }

private:
	const sixbit_entry * first_ = nullptr;
	const sixbit_entry * last_ = nullptr;
};

static sixbit_span sixbit_table()
{
	// construct-on-first-use with static, in this case not a problem on destruction,
	// because // the table contains only primitive types, no complex destruction involved,
	// and access functions (see below) return values not references or pointers.

	static constexpr sixbit_entry SIXBIT_ASCII_TABLE[] = {
		{0, '@'}, {1, 'A'}, {2, 'B'}, {3, 'C'}, {4, 'D'}, {5, 'E'}, {6, 'F'}, {7, 'G'},
		{8, 'H'}, {9, 'I'}, {10, 'J'}, {11, 'K'}, {12, 'L'}, {13, 'M'}, {14, 'N'}, {15, 'O'},
		{16, 'P'}, {17, 'Q'}, {18, 'R'}, {19, 'S'}, {20, 'T'}, {21, 'U'}, {22, 'V'}, {23, 'W'},
		{24, 'X'}, {25, 'Y'}, {26, 'Z'}, {27, '['}, {28, '\\'}, {29, ']'}, {30, '^'}, {31, '_'},
		{32, ' '}, {33, '!'}, {34, '\"'}, {35, '#'}, {36, '$'}, {37, '%'}, {38, '&'},
		{39, '\''}, {40, '('}, {41, ')'}, {42, '*'}, {43, '+'}, {44, ','}, {45, '-'}, {46, '.'},
		{47, '/'}, {48, '0'}, {49, '1'}, {50, '2'}, {51, '3'}, {52, '4'}, {53, '5'}, {54, '6'},
		{55, '7'}, {56, '8'}, {57, '9'}, {58, ':'}, {59, ';'}, {60, '<'}, {61, '='}, {62, '>'},
		{63, '?'},
	};
	return {SIXBIT_ASCII_TABLE,
		SIXBIT_ASCII_TABLE + (sizeof(SIXBIT_ASCII_TABLE) / sizeof(sixbit_entry))};
}
}
/// @endcond

char decode_sixbit_ascii(uint8_t value)
{
	for (const auto p : sixbit_table())
		if (p.value == value)
			return p.c;
	return static_cast<char>(0xff);
}

uint8_t encode_sixbit_ascii(char c)
{
	for (const auto p : sixbit_table())
		if (p.c == c)
			return p.value;
	return 0xffu;
}

std::string trim_ais_string(const std::string & s)
{
	return s.substr(0, s.find_first_of("@"));
}

/// Reads a string from the AIS message at the specified offset.
/// The string is decoded and returned.
///
/// @param[in] bits The AIS message.
/// @param[in] ofs The offset at which the string is being read.
/// @param[in] count_sixbits Number of sixbits to be read.
/// @return The decoded string.
///
/// @todo consider to hide characters after '@'
std::string binary_data::read_string(
	const raw & bits, raw::size_type ofs, raw::size_type count_sixbits)
{
	std::string s;
	s.reserve(count_sixbits);

	for (raw::size_type i = 0; i < count_sixbits; ++i) {
		uint8_t sixbit = 0;
		bits.get(sixbit, ofs + i * 6, 6);
		s += decode_sixbit_ascii(sixbit);
	}

	return s;
}

/// Writes the specified string into the AIS message. If the string does not fill
/// the entire space within the message, fill characters `@` will be written
/// until the specified number of sixbits is reached.
///
/// @param[out] bits The AIS message.
/// @param[in] ofs The offset at which the string is being written within the message.
/// @param[in] count_sixbits Number of sixbits to write into the message.
/// @param[in] s The string to be written.
///
void binary_data::write_string(
	raw & bits, raw::size_type ofs, raw::size_type count_sixbits, const std::string & s)
{
	for (raw::size_type i = 0; i < count_sixbits; ++i) {
		uint8_t value;
		if (i < s.size()) {
			value = encode_sixbit_ascii(s[i]);
		} else {
			value = encode_sixbit_ascii('@');
		}
		bits.set(value, ofs + i * 6, 6);
	}
}
}
}
