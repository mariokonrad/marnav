#ifndef __NMEA__VLW__HPP__
#define __NMEA__VLW__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(vlw)

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
	MARNAV_NMEA_SENTENCE_FRIENDS(vlw)

public:
	constexpr static const sentence_id ID = sentence_id::VLW;
	constexpr static const char * TAG = "VLW";

	vlw();
	vlw(const vlw &) = default;
	vlw & operator=(const vlw &) = default;

protected:
	vlw(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> distance_cum; // total cumulative distance
	utils::optional<unit::distance> distance_cum_unit; // N:nautical miles
	utils::optional<double> distance_reset; // distance since reset
	utils::optional<unit::distance> distance_reset_unit; // N:nautical miles

public:
	NMEA_GETTER(distance_cum)
	NMEA_GETTER(distance_cum_unit)
	NMEA_GETTER(distance_reset)
	NMEA_GETTER(distance_reset_unit)

	void set_distance_cum_nm(double t) noexcept;
	void set_distance_reset_nm(double t) noexcept;
};
}
}

#endif
