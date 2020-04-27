#ifndef MARNAV_NMEA_DETAIL_HPP
#define MARNAV_NMEA_DETAIL_HPP

#include <marnav/nmea/checksum_enum.hpp>
#include <marnav/nmea/talker_id.hpp>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>

namespace marnav
{
namespace nmea
{
/// @cond DEV
class sentence; // forward declaration

namespace detail
{
std::tuple<talker, std::string> parse_address(const std::string & address);

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
