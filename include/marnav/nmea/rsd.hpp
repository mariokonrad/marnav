#ifndef MARNAV_NMEA_RSD_HPP
#define MARNAV_NMEA_RSD_HPP

#include <marnav/nmea/sentence.hpp>

namespace marnav
{
namespace nmea
{
/// @brief RSD - RADAR System Data
///
/// @code
///        1   2   3   4   5   6   7   8   9   10  11 12 13 14
///        |   |   |   |   |   |   |   |   |   |   |   | |  |
/// $--RSD,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,x.x,a,a*hh<CR><LF>
/// @endcode
///
/// Some fields are missing from this description
///
/// Field Number:
/// 1.  Origin 1 range
/// 2.  Origin 1 bearing
/// 3.  Variable Range Marker 1
/// 4.  Bearing Line 1
/// 5.  Origin 2 range
/// 6.  Origin 2 bearing
/// 7.  Variable Range Marker 2
/// 8.  Bearing Line 2
/// 9.  Cursor Range From Own Ship
/// 10. Cursor Bearing Degrees Clockwise From Zero
/// 11. Range Scale
/// 12. Range Units
/// 13. Display rotation (C = course up, H = heading up, N = North up)
/// 14. Checksum
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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	double origin_range_1 = 0.0;
	double origin_bearing_1 = 0.0;
	double variable_range_marker_1 = 0.0;
	double bearing_line_1 = 0.0;
	double origin_range_2 = 0.0;
	double origin_bearing_2 = 0.0;
	double variable_range_marker_2 = 0.0;
	double bearing_line_2 = 0.0;
	double cursor_range_ = 0.0;
	double cursor_bearing_ = 0.0;
	double range_scale_ = 0.0;
	char range_unit_ = 'V'; // TODO: values?
	char display_rotation_ = 'C'; // TODO: enum

public:
	double get_origin_range_1() const { return origin_range_1; }
	double get_origin_bearing_1() const { return origin_bearing_1; }
	double get_variable_range_marker_1() const { return variable_range_marker_1; }
	double get_bearing_line_1() const { return bearing_line_1; }
	double get_origin_range_2() const { return origin_range_2; }
	double get_origin_bearing_2() const { return origin_bearing_2; }
	double get_variable_range_marker_2() const { return variable_range_marker_2; }
	double get_bearing_line_2() const { return bearing_line_2; }
	double get_cursor_range() const { return cursor_range_; }
	double get_cursor_bearing() const { return cursor_bearing_; }
	double get_range_scale() const { return range_scale_; }
	char get_range_unit() const { return range_unit_; }
	char get_display_rotation() const { return display_rotation_; }

	void set_1(double range, double bearing, double var_range_marker, double bearing_line);
	void set_2(double range, double bearing, double var_range_marker, double bearing_line);
	void set_cursor(double range, double bearing) noexcept;
	void set_range(double scale, char unit) noexcept;
	void set_display_rotation(char t) noexcept { display_rotation_ = t; }
};
}
}

#endif
