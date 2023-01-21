#ifndef MARNAV_AIS_MESSAGE_20_HPP
#define MARNAV_AIS_MESSAGE_20_HPP

#include <marnav/ais/message.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav::ais
{
/// @brief Data Link Management
class message_20 : public message
{
	friend class detail::factory;

public:
	struct entry {
		uint32_t offset = 0u;
		uint32_t slots = 0u;
		uint32_t timeout = 0u;
		uint32_t increment = 0u;

		constexpr entry(uint32_t o = 0u, uint32_t s = 0u, uint32_t t = 0u, uint32_t i = 0u)
			: offset(o)
			, slots(s)
			, timeout(t)
			, increment(i)
		{
		}
	};

	constexpr static message_id ID = message_id::data_link_management;
	constexpr static std::size_t SIZE_BITS_MIN = 70u;
	constexpr static std::size_t SIZE_BITS_MAX = 160u;

	message_20();
	message_20(const message_20 &) = default;
	message_20 & operator=(const message_20 &) = default;
	message_20(message_20 &&) = default;
	message_20 & operator=(message_20 &&) = default;

protected:
	message_20(const raw & bits);
	void read_data(const raw & bits);
	raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t> repeat_indicator_ = 0;
	bitset_value<  8, 30, uint32_t> mmsi_ = 0;
	bitset_value< 40, 12, uint32_t> offset_number_1_ = 0;
	bitset_value< 52,  4, uint32_t> reserved_slots_1_ = 0;
	bitset_value< 56,  3, uint32_t> timeout_1_ = 0;
	bitset_value< 59, 11, uint32_t> increment_1_ = 0;
	bitset_value< 70, 12, uint32_t> offset_number_2_ = 0;
	bitset_value< 82,  4, uint32_t> reserved_slots_2_ = 0;
	bitset_value< 86,  3, uint32_t> timeout_2_ = 0;
	bitset_value< 89, 11, uint32_t> increment_2_ = 0;
	bitset_value<100, 12, uint32_t> offset_number_3_ = 0;
	bitset_value<112,  4, uint32_t> reserved_slots_3_ = 0;
	bitset_value<116,  3, uint32_t> timeout_3_ = 0;
	bitset_value<119, 11, uint32_t> increment_3_ = 0;
	bitset_value<130, 12, uint32_t> offset_number_4_ = 0;
	bitset_value<142,  4, uint32_t> reserved_slots_4_ = 0;
	bitset_value<146,  3, uint32_t> timeout_4_ = 0;
	bitset_value<149, 11, uint32_t> increment_4_ = 0;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator_; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi_}; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator_ = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi_ = t; }

	entry get_entry(int index) const;
	void set_entry(int index, entry e);
};
}

#endif
