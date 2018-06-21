#ifndef MARNAV__NMEA__GLL__HPP
#define MARNAV__NMEA__GLL__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief GLL - Geographic Position - Latitude/Longitude
///
/// @code
///        1       2 3        4 5         6 7
///        |       | |        | |         | |
/// $--GLL,llll.ll,a,yyyyy.yy,a,hhmmss.ss,a,m*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Latitude
/// 2. Latitude hemipsphere
///    - N = North
///    - S = South
/// 3. Longitude
/// 4. Longitude hemisphere
///    - E = East
///    - W = West
/// 5. Time (UTC) of position
/// 6. Status
///    - A = Data Valid
///    - V = Data Invalid
/// 7. Mode indicator (only in newer versions)
///    - V = Invalid
///    - A = Autonomous
///    - D = Differential
///
class gll : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::GLL;
	constexpr static const char * TAG = "GLL";

	gll();
	gll(const gll &) = default;
	gll & operator=(const gll &) = default;
	gll(gll &&) = default;
	gll & operator=(gll &&) = default;

protected:
	gll(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<geo::latitude> lat_;
	utils::optional<direction> lat_hem_;
	utils::optional<geo::longitude> lon_;
	utils::optional<direction> lon_hem_;
	utils::optional<nmea::time> time_utc_;
	utils::optional<status> data_valid_;
	utils::optional<mode_indicator> mode_ind_;

public:
	decltype(time_utc_) get_time_utc() const { return time_utc_; }
	decltype(data_valid_) get_data_valid() const { return data_valid_; }
	decltype(mode_ind_) get_mode_ind() const { return mode_ind_; }

	utils::optional<geo::longitude> get_longitude() const;
	utils::optional<geo::latitude> get_latitude() const;

	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_time_utc(const nmea::time & t) noexcept { time_utc_ = t; }
	void set_data_valid(status t) noexcept { data_valid_ = t; }
	void set_mode_indicator(mode_indicator t) noexcept { mode_ind_ = t; }
};
}
}

#endif
