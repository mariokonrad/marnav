#ifndef __AIS__MESSAGE_23__HPP__
#define __AIS__MESSAGE_23__HPP__

#include <marnav/ais/message.hpp>
#include <marnav/geo/position.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav
{
namespace ais
{

/// @brief Group Assignment Command
///
class message_23 : public message
{
public:
	constexpr static const message_id ID = message_id::group_assignment_command;
	constexpr static const int SIZE_BITS = 160;

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

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & bits);

protected:
	void read_data(const raw & bits);

private:
	unsigned int repeat_indicator = 0;
	uint32_t mmsi = 0;
	uint32_t ne_lon = 0; // 0.1 minutes, TODO: fix initialization
	uint32_t ne_lat = 0; // 0.1 minutes, TODO: fix initialization
	uint32_t sw_lon = 0; // 0.1 minutes, TODO: fix initialization
	uint32_t sw_lat = 0; // 0.1 minutes, TODO: fix initialization
	uint32_t station_type = 0;
	ship_type shiptype = ship_type::not_available;
	uint32_t txrx_mode = 0;
	report_interval interval = report_interval::autonomous_mode;
	uint32_t quiet_time = 0; // minutes (0=none, 1..15 minutes)

public:
	unsigned int get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	uint32_t get_station_type() const noexcept { return station_type; }
	uint32_t get_txrx_mode() const noexcept { return txrx_mode; }
	report_interval get_interval() const noexcept { return interval; }
	uint32_t get_quiet_time() const noexcept { return quiet_time; }

	geo::position get_position_ne() const noexcept;
	geo::position get_position_sw() const noexcept;

	void set_repeat_indicator(unsigned int t) noexcept { repeat_indicator = t; }
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
