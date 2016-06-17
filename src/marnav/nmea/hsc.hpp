#ifndef __NMEA__HSC__HPP__
#define __NMEA__HSC__HPP__

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

	virtual ~hsc() {}

	hsc();
	hsc(const hsc &) = default;
	hsc & operator=(const hsc &) = default;

protected:
	hsc(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> heading_true;
	utils::optional<reference> heading_true_ref;
	utils::optional<double> heading_mag;
	utils::optional<reference> heading_mag_ref;

public:
	NMEA_GETTER(heading_true)
	NMEA_GETTER(heading_true_ref)
	NMEA_GETTER(heading_mag)
	NMEA_GETTER(heading_mag_ref)

	void set_heading_true(double t) noexcept;
	void set_heading_mag(double t) noexcept;
};
}
}

#endif
