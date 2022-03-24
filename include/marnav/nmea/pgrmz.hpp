#ifndef MARNAV_NMEA_PGRMZ_HPP
#define MARNAV_NMEA_PGRMZ_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
/// @brief PGRMZ - Garmin Altitude Information
///
/// @code
///        1   2 3
///        |   | |
/// $PGRMZ,x.x,f,h*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
/// 1. Altitude
/// 2. Altitude Unit
///    - f = feet
/// 3. Fix Type
///    - 1 = no fix
///    - 2 = 2D fix
///    - 3 = 3D fix
///
/// Example: <tt>$PGRMZ,1494,f,*10</tt>
///
class pgrmz : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::PGRMZ;
	constexpr static const char * TAG = "PGRMZ";

	enum class fix_type : char {
		no_fix, ///< NMEA representation: '1'
		d2fix, ///< NMEA representation: '2'
		d3fix ///< NMEA representation: '3'
	};

	pgrmz();
	pgrmz(const pgrmz &) = default;
	pgrmz & operator=(const pgrmz &) = default;
	pgrmz(pgrmz &&) = default;
	pgrmz & operator=(pgrmz &&) = default;

protected:
	pgrmz(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	units::feet altitude_;
	std::optional<fix_type> fix_;

public:
	units::length get_altitude() const { return {altitude_}; }
	std::optional<fix_type> get_fix() const { return fix_; }

	void set_altitude(units::length t) noexcept { altitude_ = t.get<units::feet>(); }
	void set_fix(fix_type t) noexcept { fix_ = t; }
};

std::string to_string(pgrmz::fix_type value);
}
}

#endif
