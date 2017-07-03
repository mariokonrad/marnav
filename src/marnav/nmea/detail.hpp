#ifndef MARNAV__NMEA__DETAIL__HPP
#define MARNAV__NMEA__DETAIL__HPP

#include <string>
#include <tuple>
#include <type_traits>
#include <vector>
#include <marnav/nmea/talker_id.hpp>
#include <marnav/nmea/checksum_enum.hpp>

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

void ensure_checksum(
	const std::string & s, const std::string & expected, std::string::size_type start_pos);

void check_raw_sentence(const std::string & s);

std::tuple<talker, std::string, std::string, std::vector<std::string>>
extract_sentence_information(
	const std::string & s, checksum_handling chksum = checksum_handling::check);
}
/// @endcond
}
}

#endif
