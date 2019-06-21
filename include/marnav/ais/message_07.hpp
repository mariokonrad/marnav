#ifndef MARNAV__AIS__MESSAGE_07__HPP
#define MARNAV__AIS__MESSAGE_07__HPP

#include <marnav/ais/message.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav
{
namespace ais
{
/// @brief Binary Acknowledge
class message_07 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::binary_acknowledge;
	constexpr static std::size_t SIZE_BITS_MIN = 72u;
	constexpr static std::size_t SIZE_BITS_MAX = 168u;

	message_07();
	message_07(const message_07 &) = default;
	message_07 & operator=(const message_07 &) = default;
	message_07(message_07 &&) = default;
	message_07 & operator=(message_07 &&) = default;

protected:
	message_07(const raw & bits);
	void read_data(const raw & bits);
	virtual raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t> repeat_indicator = 0;
	bitset_value<  8, 30, uint32_t> mmsi = 0;
	bitset_value< 40, 30, uint32_t> mmsi_1 = 0;
	bitset_value< 70,  2, uint32_t> mmsi_seq_1 = 0;
	bitset_value< 72, 30, uint32_t> mmsi_2 = 0;
	bitset_value<102,  2, uint32_t> mmsi_seq_2 = 0;
	bitset_value<104, 30, uint32_t> mmsi_3 = 0;
	bitset_value<134,  2, uint32_t> mmsi_seq_3 = 0;
	bitset_value<136, 30, uint32_t> mmsi_4 = 0;
	bitset_value<166,  2, uint32_t> mmsi_seq_4 = 0;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	utils::mmsi get_mmsi_1() const noexcept { return utils::mmsi{mmsi_1}; }
	utils::mmsi get_mmsi_2() const noexcept { return utils::mmsi{mmsi_2}; }
	utils::mmsi get_mmsi_3() const noexcept { return utils::mmsi{mmsi_3}; }
	utils::mmsi get_mmsi_4() const noexcept { return utils::mmsi{mmsi_4}; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_mmsi_1(const utils::mmsi & t) noexcept { mmsi_1 = t; }
	void set_mmsi_2(const utils::mmsi & t) noexcept { mmsi_2 = t; }
	void set_mmsi_3(const utils::mmsi & t) noexcept { mmsi_3 = t; }
	void set_mmsi_4(const utils::mmsi & t) noexcept { mmsi_4 = t; }
};
}
}

#endif
