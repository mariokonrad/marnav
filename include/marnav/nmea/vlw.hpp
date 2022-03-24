#ifndef MARNAV_NMEA_VLW_HPP
#define MARNAV_NMEA_VLW_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
/// @brief VLW - Distance Traveled through Water
///
/// @code
///        1   2 3   4
///        |   | |   |
/// $--VLW,x.x,N,x.x,N*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Total cumulative distance
/// 2. Total cumulative distance unit
///    - N = Nautical Miles
/// 3. Distance since Reset
/// 4. Distance since Reset unit
///    - N = Nautical Miles
///
class vlw : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::VLW;
	constexpr static const char * TAG = "VLW";

	vlw();
	vlw(const vlw &) = default;
	vlw & operator=(const vlw &) = default;
	vlw(vlw &&) = default;
	vlw & operator=(vlw &&) = default;

protected:
	vlw(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<units::nautical_miles> distance_cum_; // total cumulative distance
	std::optional<units::nautical_miles> distance_reset_; // distance since reset

public:
	std::optional<units::length> get_distance_cum() const;
	std::optional<units::length> get_distance_reset() const;

	void set_distance_cum_nm(units::length t) noexcept;
	void set_distance_reset_nm(units::length t) noexcept;
};
}
}

#endif
