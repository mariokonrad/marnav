#ifndef __NMEA__NMEA__HPP__
#define __NMEA__NMEA__HPP__

#include <stdexcept>
#include "sentence.hpp"

namespace nmea
{

class checksum_error : public std::exception
{
public:
	checksum_error(uint8_t expected, uint8_t actual)
		: expected(expected)
		, actual(actual)
	{
	}

	virtual const char* what() const noexcept override { return "checksum error"; }

public:
	const uint8_t expected;
	const uint8_t actual;
};

template <class T> std::unique_ptr<T> sentence_cast(std::unique_ptr<sentence>& s)
{
	if (!s)
		return nullptr;
	if (s->id() != T::ID)
		return nullptr;

	return std::unique_ptr<T>{static_cast<T*>(s.release())};
}

std::unique_ptr<sentence> make_sentence(const std::string& s) throw(std::invalid_argument,
																	checksum_error);

}

#endif
