#ifndef __MARNAV__NMEA__STN__HPP__
#define __MARNAV__NMEA__STN__HPP__

#include <marnav/nmea/sentence.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(stn)

/// @brief STN - Multiple Data ID
///
/// @code
///        1
///        |
/// $--STN,x.x*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Talker ID Number
///
class stn : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(stn)

public:
	constexpr static const sentence_id ID = sentence_id::STN;
	constexpr static const char * TAG = "STN";

	stn();
	stn(const stn &) = default;
	stn & operator=(const stn &) = default;
	stn(stn &&) = default;
	stn & operator=(stn &&) = default;

protected:
	stn(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	uint32_t number = 0;

public:
	decltype(number) get_number() const { return number; }

	void set_number(uint32_t t) noexcept { number = t; }
};
}
}

#endif
