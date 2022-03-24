#ifndef MARNAV_NMEA_VTG_HPP
#define MARNAV_NMEA_VTG_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<double> track_true_;
	std::optional<double> track_magn_;
	std::optional<units::knots> speed_kn_;
	std::optional<units::kilometers_per_hour> speed_kmh_;
	std::optional<mode_indicator> mode_ind_; // NMEA 2.3 or newer

public:
	std::optional<double> get_track_true() const { return track_true_; }
	std::optional<double> get_track_magn() const { return track_magn_; }
	std::optional<units::knots> get_speed_kn() const;
	std::optional<units::kilometers_per_hour> get_speed_kmh() const;
	std::optional<mode_indicator> get_mode_ind() const { return mode_ind_; }

	void set_track_true(double t) noexcept;
	void set_track_magn(double t) noexcept;
	void set_speed_kn(units::velocity t) noexcept;
	void set_speed_kmh(units::velocity t) noexcept;
	void set_mode_indicator(mode_indicator t) noexcept { mode_ind_ = t; }
};
}
}

#endif
