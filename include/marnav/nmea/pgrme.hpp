#ifndef MARNAV_NMEA_PGRME_HPP
#define MARNAV_NMEA_PGRME_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

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
/// 2. HPE Unit
///    - M = meters
/// 3. Estimated vertical position error (VPE)
/// 4. VPE Unit
///    - M = meters
/// 5. Overall spherical equivalent position error
/// 6. Spherical equivalent position error unit
///    - M = meters
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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<units::meters> horizontal_position_error_;
	std::optional<units::meters> vertical_position_error_;
	std::optional<units::meters> overall_spherical_equiv_position_error_;

public:
	std::optional<units::length> get_horizontal_position_error() const;
	std::optional<units::length> get_vertical_position_error() const;
	std::optional<units::length> get_overall_spherical_equiv_position_error() const;

	void set_horizontal_position_error(units::length t) noexcept
	{
		horizontal_position_error_ = t.get<units::meters>();
	}

	void set_vertical_position_error(units::length t) noexcept
	{
		vertical_position_error_ = t.get<units::meters>();
	}

	void set_overall_spherical_equiv_position_error(units::length t) noexcept
	{
		overall_spherical_equiv_position_error_ = t.get<units::meters>();
	}
};
}
}

#endif
