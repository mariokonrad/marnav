#ifndef MARNAV__AIS__MESSAGE_22__HPP
#define MARNAV__AIS__MESSAGE_22__HPP

#include <marnav/ais/message.hpp>
#include <marnav/geo/position.hpp>
#include <marnav/utils/mmsi.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace ais
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
	virtual raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t> repeat_indicator = 0;
	bitset_value<  8, 30, uint32_t> mmsi = 0;
	bitset_value< 40, 12, uint32_t> channel_a = 0;
	bitset_value< 52, 12, uint32_t> channel_b = 0;
	bitset_value< 64,  4, uint32_t> txrx_mode = 0;
	bitset_value< 68,  1, uint32_t> power = 0;
    bitset_value<139,  1, bool    > addressed = false;
	bitset_value<140,  1, bool    > band_a = false;
	bitset_value<141,  1, bool    > band_b = false;
	bitset_value<142,  3, uint32_t> zone_size = 0;

	// addressed = 0 (broadcast)
	bitset_value< 69, 18, uint32_t> ne_lon = longitude_not_available_short;
	bitset_value< 87, 17, uint32_t> ne_lat = latitude_not_available_short;
	bitset_value<104, 18, uint32_t> sw_lon = longitude_not_available_short;
	bitset_value<122, 17, uint32_t> sw_lat = latitude_not_available_short;

	// addressed = 1 (addressed)
	bitset_value< 69, 30, uint32_t> mmsi_1 = 0;
	bitset_value<104, 30, uint32_t> mmsi_2 = 0;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	uint32_t get_channel_a() const noexcept { return channel_a; }
	uint32_t get_channel_b() const noexcept { return channel_b; }
	uint32_t get_power() const noexcept { return power; }
	uint32_t get_txrx_mode() const noexcept { return txrx_mode; }
	bool get_addressed() const noexcept { return addressed; }
	bool get_band_a() const noexcept { return band_a; }
	bool get_band_b() const noexcept { return band_b; }
	uint32_t get_zone_size() const noexcept { return zone_size; }

	// broadcast
	utils::optional<geo::position> get_position_ne() const;
	utils::optional<geo::position> get_position_sw() const;

	// addressed
	utils::mmsi get_mmsi_1() const noexcept { return utils::mmsi{mmsi_1}; }
	utils::mmsi get_mmsi_2() const noexcept { return utils::mmsi{mmsi_2}; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_channel_a(uint32_t t) noexcept { channel_a = t; }
	void set_channel_b(uint32_t t) noexcept { channel_b = t; }
	void set_power(uint32_t t) noexcept { power = t; }
	void set_txrx_mode(uint32_t t) noexcept { txrx_mode = t; }
	void set_addressed(bool t) noexcept { addressed = t; }
	void set_band_a(bool t) noexcept { band_a = t; }
	void set_band_b(bool t) noexcept { band_b = t; }
	void set_zone_size(uint32_t t) noexcept { zone_size = t; }

	// broadcast
	void set_position_ne(const geo::position & t) noexcept;
	void set_position_sw(const geo::position & t) noexcept;

	// addressed
	void set_mmsi_1(const utils::mmsi & t) noexcept { mmsi_1 = t; }
	void set_mmsi_2(const utils::mmsi & t) noexcept { mmsi_2 = t; }
};
}
}

#endif
