#ifndef __NMEA__RTE__HPP__
#define __NMEA__RTE__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief RTE - Routes
///
/// @code
///        1   2   3 4    5           x
///        |   |   | |    |           |
/// $--RTE,x.x,x.x,a,c--c,c--c, ..... c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Total number of messages being transmitted
/// 2. Message Number
/// 3. Message mode c = complete route, all waypoints w = working route, the waypoint
///    you just left, the waypoint you’re heading to, then all the rest
/// 4. Waypoint ID
///
/// More waypoints follow. Last field is a checksum as usual.
///
/// The Garmin 65 and possibly other units report a <tt>$GPR00</tt> in the same format.
///
class rte : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::RTE;
	constexpr static const char * TAG = "RTE";

	rte();
	rte(const rte &) = default;
	rte & operator=(const rte &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<uint32_t> n_messages;
	utils::optional<uint32_t> message_number;
	utils::optional<route> message_mode; // C:complete route, W:working route
	utils::optional<std::string> waypoint_id[10]; // names or numbers of the active route

public:
	NMEA_GETTER(n_messages)
	NMEA_GETTER(message_number)
	NMEA_GETTER(message_mode)
	utils::optional<std::string> get_waypoint_id(int index) const;

	void set_n_messages(uint32_t t) { n_messages = t; }
	void set_message_number(uint32_t t) { message_number = t; }
	void set_message_mode(route t) { message_mode = t; }
	void set_waypoint_id(int index, const std::string & id);
};
}
}

#endif
