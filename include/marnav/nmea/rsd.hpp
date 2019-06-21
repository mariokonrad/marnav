#ifndef MARNAV__NMEA__RSD__HPP
#define MARNAV__NMEA__RSD__HPP

#include <array>
#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief RSD - RADAR System Data
///
/// @code
///        1   2   3   4   5   6   7   8   9   10  11 12 13
///        |   |   |   |   |   |   |   |   |   |   |   | |
/// $--RSD,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,a,a*hh<CR><LF>
/// @endcode
///
/// Some fields are missing from this description
///
/// Field Number:
/// 1.  Unknown
/// 2.  Unknown
/// 3.  Unknown
/// 4.  Unknown
/// 5.  Unknown
/// 6.  Unknown
/// 7.  Unknown
/// 8.  Unknown
/// 9.  Cursor Range From Own Ship
/// 10. Cursor Bearing Degrees Clockwise From Zero
/// 11. Range Scale
/// 12. Range Units
/// 13. Unknown
///
class rsd : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::RSD;
	constexpr static const char * TAG = "RSD";

	rsd();
	rsd(const rsd &) = default;
	rsd & operator=(const rsd &) = default;
	rsd(rsd &&) = default;
	rsd & operator=(rsd &&) = default;

protected:
	rsd(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	std::array<double, 8> unknowns_;
	double cursor_range_ = 0.0;
	double cursor_bearing_ = 0.0;
	double range_scale_ = 0.0;
	char range_unit_ = 'V';
	char unknown_ = 'V';

public:
	decltype(cursor_range_) get_cursor_range() const { return cursor_range_; }
	decltype(cursor_bearing_) get_cursor_bearing() const { return cursor_bearing_; }
	decltype(range_scale_) get_range_scale() const { return range_scale_; }
	decltype(range_unit_) get_range_unit() const { return range_unit_; }
	decltype(unknown_) get_unknown() const { return unknown_; }

	void set_unknowns(std::array<double, 8> t) noexcept { unknowns_ = t; }
	void set_cursor(double range, double bearing) noexcept;
	void set_range(double scale, char unit) noexcept;
	void set_unknown(char t) noexcept { unknown_ = t; }
};
}
}

#endif
