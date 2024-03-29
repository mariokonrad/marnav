#ifndef MARNAV_AIS_MESSAGE_14_HPP
#define MARNAV_AIS_MESSAGE_14_HPP

#include <marnav/ais/message.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav::ais
{
/// @brief Safety-Related Broadcast Message
class message_14 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::safety_related_broadcast_message;
	constexpr static std::size_t SIZE_BITS_HEAD = 40u;
	constexpr static std::size_t SIZE_BITS_MAX = 1008u;
	constexpr static std::size_t SIZE_TEXT_MAX = 161u;

	message_14();
	message_14(const message_14 &) = default;
	message_14 & operator=(const message_14 &) = default;
	message_14(message_14 &&) = default;
	message_14 & operator=(message_14 &&) = default;

protected:
	message_14(const raw & bits);
	void read_data(const raw & bits);
	raw get_data() const override;

private:
	// clang-format off
	bitset_value< 6,  2, uint32_t> repeat_indicator_ = 0;
	bitset_value< 8, 30, uint32_t> mmsi_ = 0;
	// clang-format on

	std::string text_; // bits 72..1008

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator_; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi_}; }
	std::string get_text() const { return text_; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator_ = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi_ = t; }
	void set_text(const std::string & t);
};
}

#endif
