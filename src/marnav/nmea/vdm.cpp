#include "vdm.hpp"
#include <string>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * vdm::TAG;

vdm::vdm()
	: sentence(ID, TAG, talker_id::ais_mobile_station)
	, n_fragments(0)
	, fragment(0)
	, n_fill_bits(0)
{
}

vdm::vdm(sentence_id id, const std::string & tag, const std::string & talker)
	: sentence(id, tag, talker)
	, n_fragments(0)
	, fragment(0)
	, n_fill_bits(0)
{
}

void vdm::read_fields(fields::const_iterator first)
{
	read(*(first + 0), n_fragments);
	read(*(first + 1), fragment);
	read(*(first + 2), seq_msg_id);
	read(*(first + 3), radio_channel);
	read(*(first + 4), payload);
	read(*(first + 5), n_fill_bits);
}

std::unique_ptr<sentence> vdm::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in vdm::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<vdm>();
	result->set_talker(talker);
	vdm & detail = static_cast<vdm &>(*result);

	detail.read_fields(first);

	return result;
}

std::vector<std::string> vdm::get_data() const
{
	return {to_string(n_fragments), to_string(fragment), to_string(seq_msg_id),
		to_string(radio_channel), to_string(payload), to_string(n_fill_bits)};
}

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
	const std::vector<std::pair<std::string, int>> & payload,
	utils::optional<uint32_t> seq_msg_id, ais_channel radio_channel)
{
	std::vector<std::unique_ptr<nmea::sentence>> sentences;

	for (uint32_t fragment = 0; fragment < payload.size(); ++fragment) {
		auto sentence = utils::make_unique<vdm>();

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
