#ifndef __MARNAV__AIS__NAME__HPP__
#define __MARNAV__AIS__NAME__HPP__

#include <marnav/ais/message.hpp>

namespace marnav
{
namespace ais
{
std::string to_name(message_id t);
std::string to_name(ship_type t);
std::string to_name(epfd_fix_type t);
std::string to_name(navigation_status t);
std::string to_name(virtual_aid t);
std::string to_name(off_position_indicator t);
std::string to_name(aid_type_id t);
}
}

#endif
