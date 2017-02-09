#ifndef MARNAV__NMEA__VDM__HPP
#define MARNAV__NMEA__VDM__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(vdm)

/// @brief VDM - AIS VHF Data-Link Message
///
/// @code
///        1 2 3 4 5    6
///        | | | | |    |
/// $--VDM,x,x,x,a,s--s,x*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Number of fragments
/// 2. Fragment number
/// 3. Sequence Message ID
/// 4. Radio Channel
///    - A
///    - B
/// 5. Payload, 6-bit encoded content, max. 63 characters
/// 6. Number of fill bits (0..5)
///
class vdm : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(vdm)

public:
	constexpr static const sentence_id ID = sentence_id::VDM;
	constexpr static const char * TAG = "VDM";

	vdm();
	vdm(const vdm &) = default;
	vdm & operator=(const vdm &) = default;
	vdm(vdm &&) = default;
	vdm & operator=(vdm &&) = default;

protected:
	vdm(sentence_id id, const std::string & tag, talker talk);
	vdm(talker talk, fields::const_iterator first, fields::const_iterator last);

	virtual std::vector<std::string> get_data() const override;
	virtual char get_start_token() const override { return start_token_ais; }

	void read_fields(fields::const_iterator first);

private:
	uint32_t n_fragments = 0;
	uint32_t fragment = 0;
	utils::optional<uint32_t> seq_msg_id;
	utils::optional<ais_channel> radio_channel; // A = 161.975MHz (87B), B = 162.025MHz (88B)
	std::string payload; // 6bit encoded content
	uint32_t n_fill_bits = 0; // 0..5

public:
	decltype(n_fragments) get_n_fragments() const { return n_fragments; }
	decltype(fragment) get_fragment() const { return fragment; }
	decltype(seq_msg_id) get_seq_msg_id() const { return seq_msg_id; }
	decltype(radio_channel) get_radio_channel() const { return radio_channel; }
	decltype(payload) get_payload() const { return payload; }
	decltype(n_fill_bits) get_n_fill_bits() const { return n_fill_bits; }

	void set_n_fragments(uint32_t t) noexcept { n_fragments = t; }
	void set_fragment(uint32_t t) noexcept { fragment = t; }
	void set_seq_msg_id(uint32_t t) { seq_msg_id = t; }
	void set_radio_channel(ais_channel channel) noexcept { radio_channel = channel; }
	void set_payload(const std::string & data, uint32_t fill_bits) noexcept
	{
		payload = data;
		n_fill_bits = fill_bits;
	}
	void set_payload(const std::pair<std::string, uint32_t> & data)
	{
		set_payload(data.first, data.second);
	}
};
}
}

#endif
