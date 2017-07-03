#ifndef MARNAV__NMEA__NMEA__HPP
#define MARNAV__NMEA__NMEA__HPP

#include <memory>
#include <string>
#include <vector>
#include <marnav/nmea/sentence_id.hpp>
#include <marnav/nmea/checksum_enum.hpp>

namespace marnav
{
/// @brief Contains everything to encode and decode NMEA sentences.
///
/// This is provides all NMEA sentences and supporting functions.
///
/// **Example:** list all supported NMEA sentences
/// @code
/// using namespace marnav;
///
/// for (auto const & s : nmea::get_supported_sentences_str()) {
///     std::cout << s << "\n";
/// }
/// @endcode
///
/// **Example:** create a sentence from a given string
/// @code
/// using namespace marnav;
///
/// auto s = nmea::make_sentence("$GPBOD,099.3,T,105.6,M,POINTB,*01");
///
/// if (s->id() == nmea::sentence_id::BOD) {
///     auto bod = nmea::sentence_cast<nmea::bod>(s);
///     std::cout << bod->get_waypoint_from() << " -> " << bod->get_waypoint_to() << "\n";
/// }
/// @endcode
///
/// **Example:** create a specific sentence from a given string
/// @code
/// using namespace marnav;
///
/// const auto bod =
///   nmea::detail::factory::create_sentence<nmea::bod>("$GPBOD,099.3,T,105.6,M,POINTB,*01");
/// std::cout << bod.get_waypoint_from() << " -> " << bod.get_waypoint_to() << "\n";
/// @endcode
///
/// **Example:** create a sentence and encode it to a string
/// @code
/// using namespace marnav;
///
/// nmea::bod bod;
/// bod.set_waypoint_from("POINT1");
/// bod.set_waypoint_to("POINT2");
///
/// std::cout << nmea::to_string(bod) << "\n";
/// @endcode
///
namespace nmea
{
/// @brief Exception to be thrown if a NMEA sentence is not known/supported.
class unknown_sentence : public std::logic_error
{
public:
	using logic_error::logic_error;
};

class sentence; // forward declaration

std::unique_ptr<sentence> make_sentence(
	const std::string & s, checksum_handling chksum = checksum_handling::check);

sentence_id extract_id(const std::string & s);

std::vector<std::string> get_supported_sentences_str();
std::vector<sentence_id> get_supported_sentences_id();
std::string to_string(sentence_id id);
sentence_id tag_to_id(const std::string & tag);
}
}

#endif
