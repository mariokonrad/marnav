#ifndef MARNAV__NMEA__VTG__HPP
#define MARNAV__NMEA__VTG__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief VTG - Track made good and Ground speed
///
/// @code
///         1  2  3  4  5  6  7  8 9
///         |  |  |  |  |  |  |  | |
/// $--VTG,x.x,T,x.x,M,x.x,N,x.x,K,m*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Track Degrees true
/// 2. Track degrees true reference
///    - T = True
/// 3. Track Degrees magnetic
/// 4. Track Degrees magnetic reference
///    - M = Magnetic
/// 5. Speed Knots
/// 6. Speed knots unit
///    - N = Knots
/// 7. Speed Kilometers Per Hour
/// 8. speed Kilometers per hour unit
///    - K = Kilometers Per Hour
/// 9. FAA mode indicator (NMEA 2.3 and later)
///
class vtg : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::VTG;
	constexpr static const char * TAG = "VTG";

	vtg();
	vtg(const vtg &) = default;
	vtg & operator=(const vtg &) = default;
	vtg(vtg &&) = default;
	vtg & operator=(vtg &&) = default;

protected:
	vtg(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<double> track_true_;
	utils::optional<reference> type_true_; // T:true
	utils::optional<double> track_magn_;
	utils::optional<reference> type_magn_; // M:magnetic
	utils::optional<double> speed_kn_;
	utils::optional<unit::velocity> speed_kn_unit_; // N:knots
	utils::optional<double> speed_kmh_;
	utils::optional<unit::velocity> speed_kmh_unit_; // K:kilometers per hour
	utils::optional<mode_indicator> mode_ind_; // NMEA 2.3 or newer

public:
	decltype(track_true_) get_track_true() const { return track_true_; }
	decltype(type_true_) get_type_true() const { return type_true_; }
	decltype(track_magn_) get_track_magn() const { return track_magn_; }
	decltype(type_magn_) get_type_magn() const { return type_magn_; }
	decltype(speed_kn_) get_speed_kn() const { return speed_kn_; }
	decltype(speed_kn_unit_) get_speed_kn_unit() const { return speed_kn_unit_; }
	decltype(speed_kmh_) get_speed_kmh() const { return speed_kmh_; }
	decltype(speed_kmh_unit_) get_speed_kmh_unit() const { return speed_kmh_unit_; }
	decltype(mode_ind_) get_mode_ind() const { return mode_ind_; }

	void set_track_true(double t) noexcept;
	void set_track_magn(double t) noexcept;
	void set_speed_kn(double t) noexcept;
	void set_speed_kmh(double t) noexcept;
	void set_mode_indicator(mode_indicator t) noexcept { mode_ind_ = t; }
};
}
}

#endif
