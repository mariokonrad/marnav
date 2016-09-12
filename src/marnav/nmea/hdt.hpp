#ifndef __MARNAV__NMEA__HDT__HPP__
#define __MARNAV__NMEA__HDT__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(hdt)

/// @brief HDM - Heading - True
///
/// Actual vessel heading in degrees true produced by any device or system producing true heading.
///
/// @code
///        1   2
///        |   |
/// $--HDT,x.x,T*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Heading Degrees true
/// 2. Heading Degrees true reference
///    - T = true
///
class hdt : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(hdt)

public:
	constexpr static const sentence_id ID = sentence_id::HDT;
	constexpr static const char * TAG = "HDT";

	virtual ~hdt() {}

	hdt();
	hdt(const hdt &) = default;
	hdt & operator=(const hdt &) = default;

protected:
	hdt(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> heading;
	utils::optional<reference> heading_true;

public:
	NMEA_GETTER(heading)
	NMEA_GETTER(heading_true)

	void set_heading(double t) noexcept;
};
}
}

#endif

