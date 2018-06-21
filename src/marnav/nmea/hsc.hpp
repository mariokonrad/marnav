#ifndef MARNAV__NMEA__HSC__HPP
#define MARNAV__NMEA__HSC__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
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
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::HSC;
	constexpr static const char * TAG = "HSC";

	hsc();
	hsc(const hsc &) = default;
	hsc & operator=(const hsc &) = default;
	hsc(hsc &&) = default;
	hsc & operator=(hsc &&) = default;

protected:
	hsc(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<double> heading_true_;
	utils::optional<reference> heading_true_ref_;
	utils::optional<double> heading_mag_;
	utils::optional<reference> heading_mag_ref_;

public:
	decltype(heading_true_) get_heading_true() const { return heading_true_; }
	decltype(heading_true_ref_) get_heading_true_ref() const { return heading_true_ref_; }
	decltype(heading_mag_) get_heading_mag() const { return heading_mag_; }
	decltype(heading_mag_ref_) get_heading_mag_ref() const { return heading_mag_ref_; }

	void set_heading_true(double t) noexcept;
	void set_heading_mag(double t) noexcept;
};
}
}

#endif
