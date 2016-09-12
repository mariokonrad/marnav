#ifndef __MARNAV__NMEA__NAME__HPP__
#define __MARNAV__NMEA__NAME__HPP__

#include <string>
#include <marnav/nmea/sentence_id.hpp>
#include <marnav/nmea/constants.hpp>

namespace marnav
{
namespace nmea
{
/// @{
std::string to_name(sentence_id t);
std::string to_name(selection_mode t);
std::string to_name(status t);
std::string to_name(route t);
std::string to_name(mode_indicator t);
std::string to_name(quality t);
std::string to_name(reference t);
std::string to_name(side t);

std::string to_name(unit::distance t);
std::string to_name(unit::temperature t);
std::string to_name(unit::velocity t);
/// @}
}
}

#endif
