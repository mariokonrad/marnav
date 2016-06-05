#ifndef __NMEA__WCV__HPP__
#define __NMEA__WCV__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief WCV - Waypoint Closure Velocity
///
/// @code
///        1   2 3
///        |   | |
/// $--WCV,x.x,N,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Velocity
/// 2. Velocity unit
///    - N = knots
/// 3. Waypoint ID
///
class wcv : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::WCV;
	constexpr static const char * TAG = "WCV";

	wcv();
	wcv(const wcv &) = default;
	wcv & operator=(const wcv &) = default;

	static std::unique_ptr<sentence> parse(
		const std::string & talker, fields::const_iterator first, fields::const_iterator last);

protected:
	wcv(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> speed;
	utils::optional<unit::velocity> speed_unit;
	utils::optional<std::string> waypoint_id;

public:
	NMEA_GETTER(speed)
	NMEA_GETTER(speed_unit)
	NMEA_GETTER(waypoint_id)

	void set_speed(double t) noexcept;
	void set_waypoint(const std::string & id);
};
}
}

#endif
