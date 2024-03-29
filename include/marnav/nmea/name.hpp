#ifndef MARNAV_NMEA_NAME_HPP
#define MARNAV_NMEA_NAME_HPP

#include <marnav/nmea/constants.hpp>
#include <marnav/nmea/sentence_id.hpp>
#include <marnav/nmea/talker_id.hpp>
#include <string>

namespace marnav::nmea
{
/// @{
/// Returns a printable / human readable name for the specified argument.
///
/// @param[in] t The argument to return the name for.
/// @return The human readable name.

std::string to_name(sentence_id t);
std::string to_name(talker t);
std::string to_name(selection_mode t);
std::string to_name(status t);
std::string to_name(route_mode t);
std::string to_name(mode_indicator t);
std::string to_name(quality t);
std::string to_name(reference t);
std::string to_name(side t);
std::string to_name(type_of_point t);

std::string to_name(unit::distance t);
std::string to_name(unit::temperature t);
std::string to_name(unit::velocity t);
/// @}
}

#endif
