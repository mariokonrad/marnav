#include "binary_data.hpp"
#include <algorithm>

namespace marnav
{
namespace ais
{
/// @cond DEV
namespace
{
static const std::vector<std::pair<uint8_t, char>> SIXBIT_ASCII_TABLE = {
	{0, '@'}, {1, 'A'}, {2, 'B'}, {3, 'C'}, {4, 'D'}, {5, 'E'}, {6, 'F'}, {7, 'G'}, {8, 'H'},
	{9, 'I'}, {10, 'J'}, {11, 'K'}, {12, 'L'}, {13, 'M'}, {14, 'N'}, {15, 'O'}, {16, 'P'},
	{17, 'Q'}, {18, 'R'}, {19, 'S'}, {20, 'T'}, {21, 'U'}, {22, 'V'}, {23, 'W'}, {24, 'X'},
	{25, 'Y'}, {26, 'Z'}, {27, '['}, {28, '\\'}, {29, ']'}, {30, '^'}, {31, '_'}, {32, ' '},
	{33, '!'}, {34, '\"'}, {35, '#'}, {36, '$'}, {37, '%'}, {38, '&'}, {39, '\''}, {40, '('},
	{41, ')'}, {42, '*'}, {43, '+'}, {44, ','}, {45, '-'}, {46, '.'}, {47, '/'}, {48, '0'},
	{49, '1'}, {50, '2'}, {51, '3'}, {52, '4'}, {53, '5'}, {54, '6'}, {55, '7'}, {56, '8'},
	{57, '9'}, {58, ':'}, {59, ';'}, {60, '<'}, {61, '='}, {62, '>'}, {63, '?'},
};
}
/// @endcond

char decode_sixbit_ascii(uint8_t value)
{
	value &= 0x3f;
	auto i = std::find_if(SIXBIT_ASCII_TABLE.begin(), SIXBIT_ASCII_TABLE.end(),
		[value](const std::pair<uint8_t, char> & p) { return p.first == value; });
	return i != SIXBIT_ASCII_TABLE.end() ? i->second : 0xff;
}

uint8_t encode_sixbit_ascii(char c)
{
	auto i = std::find_if(SIXBIT_ASCII_TABLE.begin(), SIXBIT_ASCII_TABLE.end(),
		[c](const std::pair<uint8_t, char> & p) { return p.second == c; });
	return i != SIXBIT_ASCII_TABLE.end() ? i->first : 0xff;
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
