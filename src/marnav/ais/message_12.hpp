#ifndef MARNAV__AIS__MESSAGE_12__HPP
#define MARNAV__AIS__MESSAGE_12__HPP

#include <marnav/ais/message.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav
{
namespace ais
{
/// @brief Addressed Safety-Related Message
class message_12 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::addressed_safety_related_message;
	constexpr static std::size_t SIZE_BITS_HEAD = 72u;
	constexpr static std::size_t SIZE_BITS_MAX = 1008u;
	constexpr static std::size_t SIZE_TEXT_MAX = 156u;

	message_12();
	message_12(const message_12 &) = default;
	message_12 & operator=(const message_12 &) = default;
	message_12(message_12 &&) = default;
	message_12 & operator=(message_12 &&) = default;

protected:
	message_12(const raw & bits);
	void read_data(const raw & bits);
	virtual raw get_data() const override;

private:
	// clang-format off
	bitset_value< 6,  2, uint32_t> repeat_indicator = 0;
	bitset_value< 8, 30, uint32_t> mmsi = 0;
	bitset_value<38,  2, uint32_t> seqno = 0; ///< Sequence Number
	bitset_value<40, 30, uint32_t> dest_mmsi = 0;
	bitset_value<70,  1, bool    > retransmit = false;
	// clang-format on

	std::string text; // bits 72..1008

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	uint32_t get_seqno() const noexcept { return seqno; }
	utils::mmsi get_dest_mmsi() const noexcept { return utils::mmsi{dest_mmsi}; }
	bool get_retransmit() const noexcept { return retransmit; }
	std::string get_text() const { return text; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_seqno(uint32_t t);
	void set_dest_mmsi(const utils::mmsi & t) noexcept { dest_mmsi = t; }
	void set_retransmit(bool t) noexcept { retransmit = t; }
	void set_text(const std::string & t);
};
}
}

#endif
