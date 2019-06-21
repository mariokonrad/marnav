#ifndef MARNAV__NMEA__AIS_HELPER__HPP
#define MARNAV__NMEA__AIS_HELPER__HPP

#include <vector>
#include <marnav/nmea/vdm.hpp>
#include <marnav/nmea/vdo.hpp>

namespace marnav
{
namespace nmea
{
/// @{

/// @brief Collects payload from proper NMEA sentences.
///
/// @note This function assumes, that all sentences in the specified range are
///   providing payload (VDM or VDO).
///
/// @param[in] begin Iterator pointing to the beginning of the messges to process.
/// @param[in] end   Iterator pointing after the messages to process (will not be
///   processed).
/// @return The container with all payload and padding bit information.
///
/// std::unique_ptr<nmea::sentence> variant. Example:
/// @code
///   std::vector<std::unique_ptr<nmea::sentence>> v;
///   v.push_back(nmea::make_sentence("..."));
///   v.push_back(nmea::make_sentence("..."));
///   auto data = nmea::collect_payload(v.begin(), v.end());
/// @endcode
template <class InputIt, typename std::enable_if<std::is_class<InputIt>::value
								 && std::is_convertible<typename InputIt::value_type,
										std::unique_ptr<sentence>>::value,
							 int>::type
	= 0>
std::vector<std::pair<std::string, uint32_t>> collect_payload(InputIt begin, InputIt end)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.reserve(std::distance(begin, end));

	for (; begin != end; ++begin) {
		const auto & t = *begin;

		// sentence_cast is not dynamic_cast, therefore the class hierarchy
		// is not detected automatically (the advantage is, it is faster).
		// this means, we have to check individually for VDM and VDO.

		if (t->id() == sentence_id::VDM) {
			const auto s = sentence_cast<nmea::vdm>(t.get());
			v.push_back(make_pair(s->get_payload(), s->get_n_fill_bits()));
		} else if (t->id() == sentence_id::VDO) {
			const auto s = sentence_cast<nmea::vdo>(t.get());
			v.push_back(make_pair(s->get_payload(), s->get_n_fill_bits()));
		} else {
			throw std::runtime_error{"invalid sentence in collect_payload"};
		}
	}

	return v;
}

/// Object iterator variant. Example:
/// @code
///    std::vector<nmea::vdm> v; // collect data, for example:
///    v.push_back(nmea::vdm{});
///    v.push_back(nmea::vdm{});
///    auto data = nmea::collect_payload(v.begin(), v.end());
/// @endcode
template <class InputIt, typename std::enable_if<std::is_class<InputIt>::value
								 && !std::is_convertible<typename InputIt::value_type,
										std::unique_ptr<sentence>>::value,
							 int>::type
	= 0>
std::vector<std::pair<std::string, uint32_t>> collect_payload(InputIt begin, InputIt end)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.reserve(std::distance(begin, end));
	for (; begin != end; ++begin) {
		v.push_back(make_pair(begin->get_payload(), begin->get_n_fill_bits()));
	}
	return v;
}

/// Pointer variant. Example:
/// @code
///   nmea::vdm v[3]; // initialize them in any way...
///   auto data = nmea::collect_payload(v, v + 3);
/// @endcode
/// or more modern:
/// @code
///   nmea::vdm v[3]; // initialize them in any way...
///   auto data = nmea::collect_payload(std::begin(v), std::end(v));
/// @endcode
/// this will not compile, because MTW does not provide payload:
/// @code
///   nmea::mtw v[3];
///   auto data = nmea::collect_payload(std::begin(v), std::end(v));
/// @endcode
template <class InputIt,
	typename std::enable_if<std::is_pointer<InputIt>::value, int>::type = 0>
std::vector<std::pair<std::string, uint32_t>> collect_payload(InputIt begin, InputIt end)
{
	std::vector<std::pair<std::string, uint32_t>> v;
	v.reserve(std::distance(begin, end));
	for (; begin != end; ++begin) {
		v.push_back(make_pair(begin->get_payload(), begin->get_n_fill_bits()));
	}
	return v;
}

/// @}

std::vector<std::unique_ptr<nmea::sentence>> make_vdms(
	const std::vector<std::pair<std::string, uint32_t>> & payload,
	utils::optional<uint32_t> seq_msg_id = utils::optional<uint32_t>{},
	ais_channel radio_channel = ais_channel::B);
}
}

#endif
