#ifndef MARNAV__NMEA__R00__HPP
#define MARNAV__NMEA__R00__HPP

#include <array>
#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/waypoint.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief R00 - Waypoints in active route
///
/// @code
///        1
///        |
/// $--R00,c---c,c---c,....*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Waypoint ID
///
class r00 : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::R00;
	constexpr static const char * TAG = "R00";
	constexpr static int max_waypoint_ids = 14;

	r00();
	r00(const r00 &) = default;
	r00 & operator=(const r00 &) = default;
	r00(r00 &&) = default;
	r00 & operator=(r00 &&) = default;

protected:
	r00(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	std::array<utils::optional<waypoint>, max_waypoint_ids> waypoint_id_;

	void check_index(int index) const;

public:
	utils::optional<waypoint> get_waypoint_id(int index) const;

	void set_waypoint_id(int index, const waypoint & id);
};
}
}

#endif
