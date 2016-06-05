#ifndef __NMEA__GRS__HPP__
#define __NMEA__GRS__HPP__

#include <array>
#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(grs)

/// @brief GRS - GPS Range Residuals
///
/// @code
///         1         2 3  4  5  6  7  8  9 10 11 12 13 14
///         |         | |  |  |  |  |  |  |  |  |  |  |  |
/// $--GRS,hhmmss.ss,m,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,xx,*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  TC time of associated GGA fix
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
	MARNAV_NMEA_SENTENCE_FRIENDS(grs)

public:
	constexpr static const sentence_id ID = sentence_id::GRS;
	constexpr static const char * TAG = "GRS";

	enum class residual_usage : uint32_t {
		used_in_gga, ///< NMEA representation: 0
		calculated_after_gga, ///< NMEA representation: 1
	};

	grs();
	grs(const grs &) = default;
	grs & operator=(const grs &) = default;

protected:
	grs(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	nmea::time time_utc;
	residual_usage usage;
	std::array<utils::optional<double>, 12> sat_residual;

	void check_index(int index) const;

public:
	NMEA_GETTER(time_utc)
	NMEA_GETTER(usage)
	utils::optional<double> get_sat_residual(int index) const;

	void set_time_utc(const nmea::time & t) noexcept { time_utc = t; }
	void set_usage(residual_usage t) noexcept { usage = t; }
	void set_sat_residual(int index, double value);
};

std::string to_string(grs::residual_usage value);
}
}

#endif
