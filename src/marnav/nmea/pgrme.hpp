#ifndef __NMEA__PGRME__HPP__
#define __NMEA__PGRME__HPP__

#include "sentence.hpp"
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
public:
	constexpr static const sentence_id ID = sentence_id::PGRME;
	constexpr static const char * TAG = "PGRME";

	pgrme();
	pgrme(const pgrme &) = default;
	pgrme & operator=(const pgrme &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> horizontal_position_error;
	char horizontal_position_error_unit; // M = meters
	utils::optional<double> vertical_position_error;
	char vertical_position_error_unit; // M = meters
	utils::optional<double> overall_spherical_equiv_position_error;
	char overall_spherical_equiv_position_error_unit; // M = meters

public:
	decltype(horizontal_position_error) get_horizontal_position_error() const
	{
		return horizontal_position_error;
	}
	decltype(horizontal_position_error_unit) get_horizontal_position_error_unit() const
	{
		return horizontal_position_error_unit;
	}
	decltype(vertical_position_error) get_vertical_position_error() const
	{
		return vertical_position_error;
	}
	decltype(vertical_position_error_unit) get_vertical_position_error_unit() const
	{
		return vertical_position_error_unit;
	}
	decltype(overall_spherical_equiv_position_error)
	get_overall_spherical_equiv_position_error() const
	{
		return overall_spherical_equiv_position_error;
	}
	decltype(overall_spherical_equiv_position_error_unit)
	get_overall_spherical_equiv_position_error_unit() const
	{
		return overall_spherical_equiv_position_error_unit;
	}
	void set_horizontal_position_error(double t) { horizontal_position_error = t; }
	void set_vertical_position_error(double t) { vertical_position_error = t; }
	void set_overall_spherical_equiv_position_error(double t)
	{
		overall_spherical_equiv_position_error = t;
	}
};
}
}

#endif
