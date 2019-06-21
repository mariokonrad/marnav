#ifndef MARNAV__AIS__MESSAGE_04__HPP
#define MARNAV__AIS__MESSAGE_04__HPP

#include <marnav/ais/message.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace ais
{
/// @brief Base Station Report
class message_04 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::base_station_report;
	constexpr static std::size_t SIZE_BITS = 168u;

	constexpr static uint32_t eta_month_not_available = 0;
	constexpr static uint32_t eta_day_not_available = 0;
	constexpr static uint32_t eta_hour_not_available = 24;
	constexpr static uint32_t eta_minute_not_available = 60;

	message_04();
	message_04(const message_04 &) = default;
	message_04 & operator=(const message_04 &) = default;
	message_04(message_04 &&) = default;
	message_04 & operator=(message_04 &&) = default;

protected:
	message_04(message_id id);
	message_04(const raw & bits);
	void read_data(const raw & bits);
	virtual raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t     > repeat_indicator = 0;
	bitset_value<  8, 30, uint32_t     > mmsi = 0;
	bitset_value< 38, 14, uint32_t     > year = year_not_available; // UTC, 1..9999
	bitset_value< 52,  4, uint32_t     > month = month_not_available; // UTC, 1..12
	bitset_value< 56,  5, uint32_t     > day = day_not_available; // UTC, 1..31
	bitset_value< 61,  5, uint32_t     > hour = hour_not_available; // UTC, 0..23
	bitset_value< 66,  6, uint32_t     > minute = minute_not_available;
	bitset_value< 72,  6, uint32_t     > second = second_not_available;
	bitset_value< 78,  1, bool         > position_accuracy = false;
	bitset_value< 79, 28, uint32_t     > longitude_minutes = longitude_not_available; // in 10000 minutes
	bitset_value<107, 27, uint32_t     > latitude_minutes = latitude_not_available; // in 10000 minutes
	bitset_value<134,  4, epfd_fix_type> epfd_fix = epfd_fix_type::undefined;
	bitset_value<148,  1, bool         > raim = false;
	bitset_value<149, 19, uint32_t     > radio_status = 0;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	uint32_t get_year() const noexcept { return year; }
	uint32_t get_month() const noexcept { return month; }
	uint32_t get_day() const noexcept { return day; }
	uint32_t get_hour() const noexcept { return hour; }
	uint32_t get_minute() const noexcept { return minute; }
	uint32_t get_second() const noexcept { return second; }
	bool get_position_accuracy() const noexcept { return position_accuracy; }
	epfd_fix_type get_epfd_fix() const noexcept { return epfd_fix; }
	bool get_raim() const noexcept { return raim; }
	uint32_t get_radio_status() const noexcept { return radio_status; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_year(uint32_t t) noexcept { year = t; }
	void set_month(uint32_t t) noexcept { month = t; }
	void set_day(uint32_t t) noexcept { day = t; }
	void set_hour(uint32_t t) noexcept { hour = t; }
	void set_minute(uint32_t t) noexcept { minute = t; }
	void set_second(uint32_t t) noexcept { second = t; }
	void set_position_accuracy(bool t) noexcept { position_accuracy = t; }
	void set_epfd_fix(epfd_fix_type t) noexcept { epfd_fix = t; }
	void set_raim(bool t) noexcept { raim = t; }
	void set_radio_status(uint32_t t) noexcept { radio_status = t; }

	utils::optional<geo::longitude> get_longitude() const;
	utils::optional<geo::latitude> get_latitude() const;
	void set_longitude(const utils::optional<geo::longitude> & t);
	void set_latitude(const utils::optional<geo::latitude> & t);
};
}
}

#endif
