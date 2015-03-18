#include "message.hpp"
#include <algorithm>

namespace ais
{

message::message(message_id type)
	: message_type(type)
{
}

message_id message::type() const { return message_type; }

static const std::vector<std::pair<uint8_t, char>> SIXBIT_ASCII_TABLE = {
	{0, '@'},
	{1, 'A'},
	{2, 'B'},
	{3, 'C'},
	{4, 'D'},
	{5, 'E'},
	{6, 'F'},
	{7, 'G'},
	{8, 'H'},
	{9, 'I'},
	{10, 'J'},
	{11, 'K'},
	{12, 'L'},
	{13, 'M'},
	{14, 'N'},
	{15, 'O'},
	{16, 'P'},
	{17, 'Q'},
	{18, 'R'},
	{19, 'S'},
	{20, 'T'},
	{21, 'U'},
	{22, 'V'},
	{23, 'W'},
	{24, 'X'},
	{25, 'Y'},
	{26, 'Z'},
	{27, '['},
	{28, '\\'},
	{29, ']'},
	{30, '^'},
	{31, '_'},
	{32, ' '},
	{33, '!'},
	{34, '\"'},
	{35, '#'},
	{36, '$'},
	{37, '%'},
	{38, '&'},
	{39, '\''},
	{40, '('},
	{41, ')'},
	{42, '*'},
	{43, '+'},
	{44, ','},
	{45, '-'},
	{46, '.'},
	{47, '/'},
	{48, '0'},
	{49, '1'},
	{50, '2'},
	{51, '3'},
	{52, '4'},
	{53, '5'},
	{54, '6'},
	{55, '7'},
	{56, '8'},
	{57, '9'},
	{58, ':'},
	{59, ';'},
	{60, '<'},
	{61, '='},
	{62, '>'},
	{63, '?'},
};

char decode_sixbit_ascii(uint8_t value)
{
	value &= 0x3f;
	auto i = std::find_if(SIXBIT_ASCII_TABLE.begin(), SIXBIT_ASCII_TABLE.end(),
						  [value](const std::pair<uint8_t, char>& p) { return p.first == value; });
	return i != SIXBIT_ASCII_TABLE.end() ? i->second : 0xff;
}

uint8_t encode_sixbit_ascii(char c)
{
	auto i = std::find_if(SIXBIT_ASCII_TABLE.begin(), SIXBIT_ASCII_TABLE.end(),
						  [c](const std::pair<uint8_t, char>& p) { return p.second == c; });
	return i != SIXBIT_ASCII_TABLE.end() ? i->first : 0xff;
}
}
