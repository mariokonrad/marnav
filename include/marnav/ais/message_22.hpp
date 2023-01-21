#ifndef MARNAV_AIS_MESSAGE_22_HPP
#define MARNAV_AIS_MESSAGE_22_HPP

#include <marnav/ais/message.hpp>
#include <marnav/geo/position.hpp>
#include <marnav/utils/mmsi.hpp>
#include <optional>

namespace marnav::ais
{
/// @brief Channel Management
///
/// @todo Refactoring to resolve the different cases (addressed or broadcast)
///
class message_22 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::channel_management;
	constexpr static std::size_t SIZE_BITS = 168u;

	message_22();
	message_22(const message_22 &) = default;
	message_22 & operator=(const message_22 &) = default;
	message_22(message_22 &&) = default;
	message_22 & operator=(message_22 &&) = default;

protected:
	message_22(const raw & bits);
	void read_data(const raw & bits);
	raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t> repeat_indicator_ = 0;
	bitset_value<  8, 30, uint32_t> mmsi_ = 0;
	bitset_value< 40, 12, uint32_t> channel_a_ = 0;
	bitset_value< 52, 12, uint32_t> channel_b_ = 0;
	bitset_value< 64,  4, uint32_t> txrx_mode_ = 0;
	bitset_value< 68,  1, uint32_t> power_ = 0;
    bitset_value<139,  1, bool    > addressed_ = false;
	bitset_value<140,  1, bool    > band_a_ = false;
	bitset_value<141,  1, bool    > band_b_ = false;
	bitset_value<142,  3, uint32_t> zone_size_ = 0;

	// addressed = 0 (broadcast)
	bitset_value< 69, 18, uint32_t> ne_lon_ = longitude_not_available_short;
	bitset_value< 87, 17, uint32_t> ne_lat_ = latitude_not_available_short;
	bitset_value<104, 18, uint32_t> sw_lon_ = longitude_not_available_short;
	bitset_value<122, 17, uint32_t> sw_lat_ = latitude_not_available_short;

	// addressed = 1 (addressed)
	bitset_value< 69, 30, uint32_t> mmsi_1_ = 0;
	bitset_value<104, 30, uint32_t> mmsi_2_ = 0;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator_; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi_}; }
	uint32_t get_channel_a() const noexcept { return channel_a_; }
	uint32_t get_channel_b() const noexcept { return channel_b_; }
	uint32_t get_power() const noexcept { return power_; }
	uint32_t get_txrx_mode() const noexcept { return txrx_mode_; }
	bool get_addressed() const noexcept { return addressed_; }
	bool get_band_a() const noexcept { return band_a_; }
	bool get_band_b() const noexcept { return band_b_; }
	uint32_t get_zone_size() const noexcept { return zone_size_; }

	// broadcast
	std::optional<geo::position> get_position_ne() const;
	std::optional<geo::position> get_position_sw() const;

	// addressed
	utils::mmsi get_mmsi_1() const noexcept { return utils::mmsi{mmsi_1_}; }
	utils::mmsi get_mmsi_2() const noexcept { return utils::mmsi{mmsi_2_}; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator_ = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi_ = t; }
	void set_channel_a(uint32_t t) noexcept { channel_a_ = t; }
	void set_channel_b(uint32_t t) noexcept { channel_b_ = t; }
	void set_power(uint32_t t) noexcept { power_ = t; }
	void set_txrx_mode(uint32_t t) noexcept { txrx_mode_ = t; }
	void set_addressed(bool t) noexcept { addressed_ = t; }
	void set_band_a(bool t) noexcept { band_a_ = t; }
	void set_band_b(bool t) noexcept { band_b_ = t; }
	void set_zone_size(uint32_t t) noexcept { zone_size_ = t; }

	// broadcast
	void set_position_ne(const geo::position & t) noexcept;
	void set_position_sw(const geo::position & t) noexcept;

	// addressed
	void set_mmsi_1(const utils::mmsi & t) noexcept { mmsi_1_ = t; }
	void set_mmsi_2(const utils::mmsi & t) noexcept { mmsi_2_ = t; }
};
}

#endif
