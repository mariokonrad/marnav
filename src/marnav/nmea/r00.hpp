#ifndef __NMEA__R00__HPP__
#define __NMEA__R00__HPP__

#include <array>
#include <marnav/nmea/sentence.hpp>
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
public:
	constexpr static const sentence_id ID = sentence_id::R00;
	constexpr static const char * TAG = "R00";
	constexpr static const int MAX_WAYPOINT_IDS = 14;

	r00();
	r00(const r00 &) = default;
	r00 & operator=(const r00 &) = default;

	static std::unique_ptr<sentence> parse(
		const std::string & talker, const std::vector<std::string> & fields);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	std::array<utils::optional<std::string>, MAX_WAYPOINT_IDS> waypoint_id;

	void check_index(int index) const;

public:
	utils::optional<std::string> get_waypoint_id(int index) const;

	void set_waypoint_id(int index, const std::string & id);
};
}
}

#endif
