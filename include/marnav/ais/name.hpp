#ifndef MARNAV_AIS_NAME_HPP
#define MARNAV_AIS_NAME_HPP

#include <marnav/ais/message.hpp>

namespace marnav::ais
{
std::string to_name(message_id t);
std::string to_name(ship_type t);
std::string to_name(epfd_fix_type t);
std::string to_name(navigation_status t);
std::string to_name(virtual_aid t);
std::string to_name(off_position_indicator t);
std::string to_name(aid_type_id t);
std::string to_name(maneuver_indicator_id t);
std::string to_name(data_terminal t);
}

#endif
