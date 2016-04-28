#ifndef __NMEA__VDM__HPP__
#define __NMEA__VDM__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

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
public:
	constexpr static const sentence_id ID = sentence_id::VDM;
	constexpr static const char * TAG = "VDM";

	vdm();
	vdm(const vdm &) = default;
	vdm & operator=(const vdm &) = default;

	virtual ~vdm() {}

	static std::unique_ptr<sentence> parse(
		const std::string & talker, fields::const_iterator first, fields::const_iterator last);

protected:
	vdm(sentence_id id, const std::string & tag, const std::string & talker);

	virtual std::vector<std::string> get_data() const override;
	virtual char get_start_token() const override { return start_token_ais; }

	void read_fields(fields::const_iterator first);

private:
	uint32_t n_fragments;
	uint32_t fragment;
	utils::optional<uint32_t> seq_msg_id;
	utils::optional<ais_channel> radio_channel; // A = 161.975MHz (87B), B = 162.025MHz (88B)
	std::string payload; // 6bit encoded content
	uint32_t n_fill_bits; // 0..5

public:
	NMEA_GETTER(n_fragments)
	NMEA_GETTER(fragment)
	NMEA_GETTER(seq_msg_id)
	NMEA_GETTER(radio_channel)
	NMEA_GETTER(payload)
	NMEA_GETTER(n_fill_bits)

	void set_n_fragments(uint32_t t) noexcept { n_fragments = t; }
	void set_fragment(uint32_t t) noexcept { fragment = t; }
	void set_seq_msg_id(uint32_t t) { seq_msg_id = t; }
	void set_radio_channel(ais_channel channel) noexcept { radio_channel = channel; }
	void set_payload(const std::string & data, uint32_t fill_bits) noexcept
	{
		payload = data;
		n_fill_bits = fill_bits;
	}
	void set_payload(const std::pair<std::string, int> & data)
	{
		set_payload(data.first, data.second);
	}
};

/// @{

/// @brief Collects payload from proper NMEA sentences.
///
/// @note This function assumes, that all sentences in the specified range are
///   providing payload (VDM or descendents).
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
std::vector<std::pair<std::string, int>> collect_payload(InputIt begin, InputIt end)
{
	std::vector<std::pair<std::string, int>> v;
	v.reserve(std::distance(begin, end));

	for (; begin != end; ++begin) {
		const auto & s = sentence_cast<nmea::vdm>(*begin);
		v.push_back(make_pair(s->get_payload(), s->get_n_fill_bits()));
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
std::vector<std::pair<std::string, int>> collect_payload(InputIt begin, InputIt end)
{
	std::vector<std::pair<std::string, int>> v;
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
std::vector<std::pair<std::string, int>> collect_payload(InputIt begin, InputIt end)
{
	std::vector<std::pair<std::string, int>> v;
	v.reserve(std::distance(begin, end));
	for (; begin != end; ++begin) {
		v.push_back(make_pair(begin->get_payload(), begin->get_n_fill_bits()));
	}
	return v;
}

/// @}

std::vector<std::unique_ptr<nmea::sentence>> make_vdms(
	const std::vector<std::pair<std::string, int>> & payload,
	utils::optional<uint32_t> seq_msg_id = utils::optional<uint32_t>{},
	ais_channel radio_channel = ais_channel::B);
}
}

#endif
