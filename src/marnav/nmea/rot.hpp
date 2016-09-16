#ifndef __NMEA__ROT__HPP__
#define __NMEA__ROT__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(rot)

/// @brief ROT - Rate Of Turn
///
/// @code
///        1   2
///        |   |
/// $--ROT,x.x,A*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Rate Of Turn, degrees per minute, "-" means bow turns to port
/// 2. Status
///    - A = data is valid
///    - V = invalid
///
class rot : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(rot)

public:
	constexpr static const sentence_id ID = sentence_id::ROT;
	constexpr static const char * TAG = "ROT";

	virtual ~rot() {}

	rot();
	rot(const rot &) = default;
	rot & operator=(const rot &) = default;

protected:
	rot(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> deg_per_minute;
	utils::optional<status> data_valid;

public:
	MARNAV_NMEA_GETTER(deg_per_minute)
	MARNAV_NMEA_GETTER(data_valid)

	void set_deg_per_minute(double t) noexcept { deg_per_minute = t; }
	void set_data_valid(status t) noexcept { data_valid = t; }
};
}
}

#endif
