#ifndef __MARNAV__NMEA__HSC__HPP__
#define __MARNAV__NMEA__HSC__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(hsc)

/// @brief HSC - Heading Steering Command
///
/// @code
///        1   2 3   4
///        |   | |   |
/// $--HSC,x.x,T,x.x,M*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Heading Degrees True
/// 2. Heading Degrees True reference
///    - T = True
/// 3. Heading Degrees Magnetic
/// 4. Heading Degrees Magnetic reference
///    - M = Magnetic
///
class hsc : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(hsc)

public:
	constexpr static const sentence_id ID = sentence_id::HSC;
	constexpr static const char * TAG = "HSC";

	hsc();
	hsc(const hsc &) = default;
	hsc & operator=(const hsc &) = default;
	hsc(hsc &&) = default;
	hsc & operator=(hsc &&) = default;

protected:
	hsc(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> heading_true;
	utils::optional<reference> heading_true_ref;
	utils::optional<double> heading_mag;
	utils::optional<reference> heading_mag_ref;

public:
	decltype(heading_true) get_heading_true() const { return heading_true; }
	decltype(heading_true_ref) get_heading_true_ref() const { return heading_true_ref; }
	decltype(heading_mag) get_heading_mag() const { return heading_mag; }
	decltype(heading_mag_ref) get_heading_mag_ref() const { return heading_mag_ref; }

	void set_heading_true(double t) noexcept;
	void set_heading_mag(double t) noexcept;
};
}
}

#endif
