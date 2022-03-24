#ifndef MARNAV_NMEA_MOB_HPP
#define MARNAV_NMEA_MOB_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/angle.hpp>
#include <marnav/nmea/date.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/units/units.hpp>
#include <marnav/utils/mmsi.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
/// @brief MOB - Man over Board
///
/// @code
///
///        1     2 3         4 5      6         7       8 9       10 11  12  13        14
///        |     | |         | |      |         |       | |        | |   |   |         |
/// $--MOB,hhhhh,a,hhmmss.ss,x,xxxxxx,hhmmss.ss,llll.ll,a,yyyyy.yy,a,x.x,x.x,xxxxxxxxx,x*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  MOB emitter ID, fixed lenth of 5 hex digits with leading zeroes, optional if unknown
/// 2.  MOB status
///     - A = MOB activated
///     - T = Test mode
///     - M = Manual button
///     - V = MOB not in use
///     - E = Error
/// 3.  UTC of MOB activation, decimal points shall not be used
/// 4.  MOB position source
///     - 0 = MOB position estimated by the vessel
///     - 1 = MOB position reported by MOB emitter
///     - 2..5 = Reserved
///     - 6 = Error
/// 5.  Date of position (ddmmyy)
/// 6.  UTC of position, decimal points shall not be used
/// 7.  Latitude
/// 8.  Latitude hemisphere
///     - N = North
///     - S = South
/// 9.  Longitude
/// 10. Longitude hemisphere
///     - E = East
///     - W = West
/// 11. Course over ground, degrees true
/// 12. Speed over ground, unit: knots
/// 13. MMSI of vessel
/// 14. Battery status
///     - 0 = Good
///     - 1 = Low
///     - 2..5 = Reserved
///     - 6 = Error
///
/// Source:
/// https://www.nmea.org/Assets/21030814%20nmea%200183_man%20overboard%20notification_mob_sentence%20amendment.pdf
///
class mob : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::MOB;
	constexpr static const char * TAG = "MOB";

	constexpr static std::string::size_type emitter_id_max = 5u;

	enum class mob_status : char {
		mob_activated, ///< 'A'
		test_mode, ///< 'T'
		manual_button, ///< 'M'
		mob_not_in_use, ///< 'V'
		error ///< 'E'
	};

	enum class mob_position_source : uint32_t {
		position_estimated, ///< 0
		position_reported, ///< 1
		reserved, ///< 2..5
		error ///< 6
	};

	enum class battery_status : uint32_t {
		good, ///< 0
		low, ///< 1
		reserved, ///< 2..5
		error ///< 6
	};

	mob();
	mob(const mob &) = default;
	mob & operator=(const mob &) = default;
	mob(mob &&) = default;
	mob & operator=(mob &&) = default;

protected:
	mob(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<std::string> emitter_id_;
	mob_status mob_status_ = mob_status::error;
	nmea::time mob_activation_utc_;
	mob_position_source mob_position_source_ = mob_position_source::error;
	nmea::date position_date_;
	nmea::time position_utc_;
	geo::latitude lat_;
	direction lat_hem_ = direction::north;
	geo::longitude lon_;
	direction lon_hem_ = direction::east;
	double cog_ = 0.0; // degrees true
	units::knots sog_;
	uint64_t mmsi_ = 0u;
	battery_status battery_status_ = battery_status::error;

public:
	std::optional<std::string> get_emitter_id() const { return emitter_id_; }
	mob_status get_mob_status() const { return mob_status_; }
	nmea::time get_mob_activation_utc() const { return mob_activation_utc_; }
	mob_position_source get_mob_position_source() const { return mob_position_source_; }
	nmea::date get_position_date() const { return position_date_; }
	nmea::time get_position_time() const { return position_utc_; }
	geo::latitude get_lat() const;
	geo::longitude get_lon() const;
	double get_cog() const { return cog_; }
	units::velocity get_sog() const { return {sog_}; }
	utils::mmsi get_mmsi() const;
	battery_status get_battery_status() const { return battery_status_; }

	void set_emitter_id(const std::string &);
	void set_mob_status(mob_status t) noexcept { mob_status_ = t; }
	void set_mob_activation_utc(const nmea::time & t) noexcept { mob_activation_utc_ = t; }
	void set_mob_position_source(mob_position_source t) noexcept { mob_position_source_ = t; }
	void set_position_date(const nmea::date & t) noexcept { position_date_ = t; }
	void set_position_time(const nmea::time & t) noexcept { position_utc_ = t; }
	void set_lat(const geo::latitude &);
	void set_lon(const geo::longitude &);
	void set_cog(double t) noexcept { cog_ = t; }
	void set_sog(units::velocity t) noexcept { sog_ = t.get<units::knots>(); }
	void set_mmsi(const utils::mmsi &);
	void set_battery_status(battery_status t) noexcept { battery_status_ = t; }
};

std::string to_string(mob::mob_status value);
std::string to_string(mob::mob_position_source value);
std::string to_string(mob::battery_status value);
}
}

#endif
