#ifndef MARNAV__NMEA__PGRME__HPP
#define MARNAV__NMEA__PGRME__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief PGRME - Garmin Estimated Error
///
/// @code
///        1  2  3  4  5  6  7
///        |  |  |  |  |  |  |
/// $PGRME,hhh,M,vvv,M,ttt,M*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
/// 1. Estimated horizontal position error (HPE)
/// 2. M=meters
/// 3. Estimated vertical position error (VPE)
/// 4. M=meters
/// 5. Overall spherical equivalent position error
/// 6. M=meters
/// 7. Checksum
///
/// Example: <tt>$PGRME,15.0,M,45.0,M,25.0,M*22</tt>
///
class pgrme : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::PGRME;
	constexpr static const char * TAG = "PGRME";

	pgrme();
	pgrme(const pgrme &) = default;
	pgrme & operator=(const pgrme &) = default;
	pgrme(pgrme &&) = default;
	pgrme & operator=(pgrme &&) = default;

protected:
	pgrme(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<double> horizontal_position_error_;
	unit::distance horizontal_position_error_unit_ = unit::distance::meter;
	utils::optional<double> vertical_position_error_;
	unit::distance vertical_position_error_unit_ = unit::distance::meter;
	utils::optional<double> overall_spherical_equiv_position_error_;
	unit::distance overall_spherical_equiv_position_error_unit_ = unit::distance::meter;

public:
	decltype(horizontal_position_error_) get_horizontal_position_error() const
	{
		return horizontal_position_error_;
	}
	decltype(horizontal_position_error_unit_) get_horizontal_position_error_unit() const
	{
		return horizontal_position_error_unit_;
	}
	decltype(vertical_position_error_) get_vertical_position_error() const
	{
		return vertical_position_error_;
	}
	decltype(vertical_position_error_unit_) get_vertical_position_error_unit() const
	{
		return vertical_position_error_unit_;
	}
	decltype(overall_spherical_equiv_position_error_)
	get_overall_spherical_equiv_position_error() const
	{
		return overall_spherical_equiv_position_error_;
	}
	decltype(overall_spherical_equiv_position_error_unit_)
	get_overall_spherical_equiv_position_error_unit() const
	{
		return overall_spherical_equiv_position_error_unit_;
	}

	void set_horizontal_position_error(double t) noexcept { horizontal_position_error_ = t; }
	void set_vertical_position_error(double t) noexcept { vertical_position_error_ = t; }
	void set_overall_spherical_equiv_position_error(double t) noexcept
	{
		overall_spherical_equiv_position_error_ = t;
	}
};
}
}

#endif
