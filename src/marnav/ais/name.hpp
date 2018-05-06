#ifndef MARNAV__AIS__NAME__HPP
#define MARNAV__AIS__NAME__HPP

#include <marnav/ais/message.hpp>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace ais
{
MARNAV_EXPORT std::string to_name(message_id t);
MARNAV_EXPORT std::string to_name(ship_type t);
MARNAV_EXPORT std::string to_name(epfd_fix_type t);
MARNAV_EXPORT std::string to_name(navigation_status t);
MARNAV_EXPORT std::string to_name(virtual_aid t);
MARNAV_EXPORT std::string to_name(off_position_indicator t);
MARNAV_EXPORT std::string to_name(aid_type_id t);
MARNAV_EXPORT std::string to_name(maneuver_indicator_id t);
MARNAV_EXPORT std::string to_name(data_terminal t);
}
}

#endif
