#ifndef MARNAV__NMEA__GRS__HPP
#define MARNAV__NMEA__GRS__HPP

#include <array>
#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief GRS - GPS Range Residuals
///
/// @code
///         1         2 3  4  5  6  7  8  9 10 11 12 13 14
///         |         | |  |  |  |  |  |  |  |  |  |  |  |
/// $--GRS,hhmmss.ss,m,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  UTC time of associated GGA fix
/// 2.  0 = Residuals used in GGA, 1 = residuals calculated after GGA
/// 3.  Satellite 1 residual in meters
/// 4.  Satellite 2 residual in meters
/// 5.  Satellite 3 residual in meters
/// 6.  Satellite 4 residual in meters (blank if unused)
/// 7.  Satellite 5 residual in meters (blank if unused)
/// 8.  Satellite 6 residual in meters (blank if unused)
/// 9.  Satellite 7 residual in meters (blank if unused)
/// 10. Satellite 8 residual in meters (blank if unused)
/// 11. Satellite 9 residual in meters (blank if unused)
/// 12. Satellite 10 residual in meters (blank if unused)
/// 13. Satellite 11 residual in meters (blank if unused)
/// 14. Satellite 12 residual in meters (blank if unused)
///
/// The order of satellites the same as those in the last GSA.
///
class grs : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::GRS;
	constexpr static const char * TAG = "GRS";

	constexpr static int num_satellite_residuals = 12;

	enum class residual_usage : uint32_t {
		used_in_gga, ///< NMEA representation: 0
		calculated_after_gga, ///< NMEA representation: 1
	};

	grs();
	grs(const grs &) = default;
	grs & operator=(const grs &) = default;
	grs(grs &&) = default;
	grs & operator=(grs &&) = default;

protected:
	grs(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	nmea::time time_utc_;
	residual_usage usage_;
	std::array<utils::optional<double>, num_satellite_residuals> sat_residual_;

	void check_index(int index) const;

public:
	decltype(time_utc_) get_time_utc() const { return time_utc_; }
	decltype(usage_) get_usage() const { return usage_; }
	utils::optional<double> get_sat_residual(int index) const;

	void set_time_utc(const nmea::time & t) noexcept { time_utc_ = t; }
	void set_usage(residual_usage t) noexcept { usage_ = t; }
	void set_sat_residual(int index, double value);
};

std::string to_string(grs::residual_usage value);
}
}

#endif
