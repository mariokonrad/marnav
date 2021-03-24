#include <marnav/nmea/ais_helper.hpp>

namespace marnav
{
namespace nmea
{
/// Creates and returns a container of VDM sentences, created from the specified
/// payload.
///
/// @param[in] payload The payload to create VDM sentences from.
/// @param[in] seq_msg_id The optional sequence message ID to be configured for
///   the resulting sentences.
/// @param[in] radio_channel Specifies which AIS radio channel to configure for
///   the resulting sentences.
/// @return Container of NMEA sentences containing VDM sentences.
std::vector<std::unique_ptr<nmea::sentence>> make_vdms(
	const std::vector<std::pair<std::string, uint32_t>> & payload,
	std::optional<uint32_t> seq_msg_id, ais_channel radio_channel)
{
	std::vector<std::unique_ptr<nmea::sentence>> sentences;

	for (uint32_t fragment = 0; fragment < payload.size(); ++fragment) {
		auto sentence = std::make_unique<vdm>();

		sentence->set_n_fragments(payload.size());
		sentence->set_fragment(fragment + 1);
		sentence->set_radio_channel(radio_channel);
		sentence->set_payload(payload[fragment]);

		if (seq_msg_id)
			sentence->set_seq_msg_id(*seq_msg_id);

		sentences.push_back(std::move(sentence));
	}

	return sentences;
}
}
}
