#ifndef MARNAV__UTILS__BITSET_STRING__HPP
#define MARNAV__UTILS__BITSET_STRING__HPP

/// Copyright (c) 2016 Mario Konrad <mario.konrad@gmx.net>
/// The code is licensed under the BSD License.

#include "bitset.hpp"
#include <string>

namespace marnav
{
namespace utils
{
/// Renders the bitset as string.
///
/// @param[in] bits The bits to render.
/// @return String representing the bitset as continous stream of '0' and '1'.
template <class T> std::string to_string(const bitset<T> & bits)
{
	std::string result;
	result.reserve(bits.size());
	for (auto const & b : bits)
		result += '0' + b;
	return result;
}

/// Renders the bitset as string, packed by specified number of bits.
///
/// @param[in] bits The bits to render.
/// @param[in] pack Number of bits per pack.
/// @param[in] delm Delimitter to separate the packs.
/// @return String representing the bitset as stream of '0' and '1', separated by
///   the delimitter.
template <class T>
std::string to_string(const bitset<T> & bits, std::size_t pack, char delm = ' ')
{
	if ((pack == 0) || (pack >= bits.size()))
		return to_string(bits);

	std::string result;

	// reserve space, wasted space at most: sizeof(delm) characters
	result.reserve(bits.size() + sizeof(delm) * (bits.size() / pack));

	std::size_t i = 1;
	auto begin = bits.begin();
	for (;;) {
		result += '0' + *begin;
		++begin;
		if (begin == bits.end())
			break;
		if (i == pack) {
			result += delm;
			i = 0;
		}
		++i;
	}

	return result;
}
}
}

#endif
