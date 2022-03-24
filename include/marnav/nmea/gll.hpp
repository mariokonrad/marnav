#ifndef MARNAV_NMEA_GLL_HPP
#define MARNAV_NMEA_GLL_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/time.hpp>
#include <optional>

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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<geo::latitude> lat_;
	std::optional<direction> lat_hem_;
	std::optional<geo::longitude> lon_;
	std::optional<direction> lon_hem_;
	std::optional<nmea::time> time_utc_;
	std::optional<status> data_valid_;
	std::optional<mode_indicator> mode_ind_;

public:
	std::optional<nmea::time> get_time_utc() const { return time_utc_; }
	std::optional<status> get_data_valid() const { return data_valid_; }
	std::optional<mode_indicator> get_mode_ind() const { return mode_ind_; }

	std::optional<geo::longitude> get_lon() const;
	std::optional<geo::latitude> get_lat() const;

	void set_lat(const geo::latitude & t);
	void set_lon(const geo::longitude & t);
	void set_time_utc(const nmea::time & t) noexcept { time_utc_ = t; }
	void set_data_valid(status t) noexcept { data_valid_ = t; }
	void set_mode_indicator(mode_indicator t) noexcept { mode_ind_ = t; }
};
}
}

#endif
