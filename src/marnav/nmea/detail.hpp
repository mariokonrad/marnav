#ifndef __MARNAV__NMEA__DETAIL__HPP__
#define __MARNAV__NMEA__DETAIL__HPP__

#include <string>
#include <tuple>
#include <type_traits>
#include <vector>
#include <marnav/nmea/talker_id.hpp>

namespace marnav
{
namespace nmea
{
/// @cond DEV
class sentence; // forward declaration

namespace detail
{
std::tuple<talker, std::string> parse_address(
	const std::string & address, bool ignore_unknown = false);

void ensure_checksum(const std::string & s, const std::string & expected);

void check_raw_sentence(const std::string & s);

std::tuple<talker, std::string, std::vector<std::string>> extract_sentence_information(
	const std::string & s, bool ignore_checksum = false);

/// Exists only to do SFINAE on the template parameter type `T`.
/// Since it does nothing, the compiler will optimize it out.
template <typename T,
	typename std::enable_if<std::is_base_of<sentence, T>::value, int>::type = 0>
void create_sentence_base_class_check()
{
	// intentionally left blank
}
}
/// @endcond
}
}

#endif
