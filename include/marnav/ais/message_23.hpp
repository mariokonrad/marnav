#ifndef MARNAV__AIS__MESSAGE_23__HPP
#define MARNAV__AIS__MESSAGE_23__HPP

#include <marnav/ais/message.hpp>
#include <marnav/geo/position.hpp>
#include <marnav/utils/mmsi.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace ais
{
/// @brief Group Assignment Command
///
class message_23 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::group_assignment_command;
	constexpr static std::size_t SIZE_BITS = 160u;

	enum class report_interval : uint8_t {
		autonomous_mode = 0,
		minutes_10 = 1,
		minutes_06 = 2,
		minutes_03 = 3,
		minutes_01 = 4,
		seconds_30 = 5,
		seconds_15 = 6,
		seconds_10 = 7,
		seconds_05 = 8,
		next_shorter = 9,
		next_longer = 10,
		// reserved for future use: 11 - 15
	};

	message_23();
	message_23(const message_23 &) = default;
	message_23 & operator=(const message_23 &) = default;
	message_23(message_23 &&) = default;
	message_23 & operator=(message_23 &&) = default;

protected:
	message_23(const raw & bits);
	void read_data(const raw & bits);
	virtual raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t       > repeat_indicator = 0;
	bitset_value<  8, 30, uint32_t       > mmsi = 0;
	bitset_value< 40, 18, uint32_t       > ne_lon = longitude_not_available_short;
	bitset_value< 58, 17, uint32_t       > ne_lat = latitude_not_available_short;
	bitset_value< 75, 18, uint32_t       > sw_lon = longitude_not_available_short;
	bitset_value< 93, 17, uint32_t       > sw_lat = latitude_not_available_short;
	bitset_value<110,  4, uint32_t       > station_type = 0;
	bitset_value<114,  8, ship_type      > shiptype = ship_type::not_available;
	bitset_value<144,  2, uint32_t       > txrx_mode = 0;
	bitset_value<146,  4, report_interval> interval = report_interval::autonomous_mode;
	bitset_value<150,  4, uint32_t       > quiet_time = 0; // minutes (0=none, 1..15 minutes)
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	uint32_t get_station_type() const noexcept { return station_type; }
	ship_type get_shiptype() const noexcept { return shiptype; }
	uint32_t get_txrx_mode() const noexcept { return txrx_mode; }
	report_interval get_interval() const noexcept { return interval; }
	uint32_t get_quiet_time() const noexcept { return quiet_time; }

	utils::optional<geo::position> get_position_ne() const;
	utils::optional<geo::position> get_position_sw() const;

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_station_type(uint32_t t) noexcept { station_type = t; }
	void set_txrx_mode(uint32_t t) noexcept { txrx_mode = t; }
	void set_interval(report_interval t) { interval = t; }
	void set_quiet_time(uint32_t t) noexcept { quiet_time = t; }

	void set_position_ne(const geo::position & t) noexcept;
	void set_position_sw(const geo::position & t) noexcept;
};
}
}

#endif
