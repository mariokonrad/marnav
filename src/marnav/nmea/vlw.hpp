#ifndef MARNAV__NMEA__VLW__HPP
#define MARNAV__NMEA__VLW__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

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
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<double> distance_cum_; // total cumulative distance
	utils::optional<unit::distance> distance_cum_unit_; // N:nautical miles
	utils::optional<double> distance_reset_; // distance since reset
	utils::optional<unit::distance> distance_reset_unit_; // N:nautical miles

public:
	decltype(distance_cum_) get_distance_cum() const { return distance_cum_; }
	decltype(distance_cum_unit_) get_distance_cum_unit() const { return distance_cum_unit_; }
	decltype(distance_reset_) get_distance_reset() const { return distance_reset_; }
	decltype(distance_reset_unit_) get_distance_reset_unit() const
	{
		return distance_reset_unit_;
	}

	void set_distance_cum_nm(double t) noexcept;
	void set_distance_reset_nm(double t) noexcept;
};
}
}

#endif
