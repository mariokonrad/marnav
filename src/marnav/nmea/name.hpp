#ifndef MARNAV__NMEA__NAME__HPP
#define MARNAV__NMEA__NAME__HPP

#include <string>
#include <marnav/nmea/sentence_id.hpp>
#include <marnav/nmea/constants.hpp>
#include <marnav/nmea/talker_id.hpp>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace nmea
{
/// @{
/// Returns a printable / human readable name for the specified argument.
///
/// @param[in] t The argument to return the name for.
/// @return The human readable name.

MARNAV_EXPORT std::string to_name(sentence_id t);
MARNAV_EXPORT std::string to_name(talker t);
MARNAV_EXPORT std::string to_name(selection_mode t);
MARNAV_EXPORT std::string to_name(status t);
MARNAV_EXPORT std::string to_name(route t);
MARNAV_EXPORT std::string to_name(mode_indicator t);
MARNAV_EXPORT std::string to_name(quality t);
MARNAV_EXPORT std::string to_name(reference t);
MARNAV_EXPORT std::string to_name(side t);
MARNAV_EXPORT std::string to_name(type_of_point t);

MARNAV_EXPORT std::string to_name(unit::distance t);
MARNAV_EXPORT std::string to_name(unit::temperature t);
MARNAV_EXPORT std::string to_name(unit::velocity t);
/// @}
}
}

#endif
