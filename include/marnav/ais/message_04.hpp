#ifndef MARNAV_AIS_MESSAGE_04_HPP
#define MARNAV_AIS_MESSAGE_04_HPP

#include <marnav/ais/message.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>
#include <optional>

namespace marnav::ais
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
	raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t     > repeat_indicator_ = 0;
	bitset_value<  8, 30, uint32_t     > mmsi_ = 0;
	bitset_value< 38, 14, uint32_t     > year_ = year_not_available; // UTC, 1..9999
	bitset_value< 52,  4, uint32_t     > month_ = month_not_available; // UTC, 1..12
	bitset_value< 56,  5, uint32_t     > day_ = day_not_available; // UTC, 1..31
	bitset_value< 61,  5, uint32_t     > hour_ = hour_not_available; // UTC, 0..23
	bitset_value< 66,  6, uint32_t     > minute_ = minute_not_available;
	bitset_value< 72,  6, uint32_t     > second_ = second_not_available;
	bitset_value< 78,  1, bool         > position_accuracy_ = false;
	bitset_value< 79, 28, uint32_t     > longitude_minutes_ = longitude_not_available; // in 10000 minutes
	bitset_value<107, 27, uint32_t     > latitude_minutes_ = latitude_not_available; // in 10000 minutes
	bitset_value<134,  4, epfd_fix_type> epfd_fix_ = epfd_fix_type::undefined;
	bitset_value<148,  1, bool         > raim_ = false;
	bitset_value<149, 19, uint32_t     > radio_status_ = 0;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator_; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi_}; }
	uint32_t get_year() const noexcept { return year_; }
	uint32_t get_month() const noexcept { return month_; }
	uint32_t get_day() const noexcept { return day_; }
	uint32_t get_hour() const noexcept { return hour_; }
	uint32_t get_minute() const noexcept { return minute_; }
	uint32_t get_second() const noexcept { return second_; }
	bool get_position_accuracy() const noexcept { return position_accuracy_; }
	epfd_fix_type get_epfd_fix() const noexcept { return epfd_fix_; }
	bool get_raim() const noexcept { return raim_; }
	uint32_t get_radio_status() const noexcept { return radio_status_; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator_ = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi_ = t; }
	void set_year(uint32_t t) noexcept { year_ = t; }
	void set_month(uint32_t t) noexcept { month_ = t; }
	void set_day(uint32_t t) noexcept { day_ = t; }
	void set_hour(uint32_t t) noexcept { hour_ = t; }
	void set_minute(uint32_t t) noexcept { minute_ = t; }
	void set_second(uint32_t t) noexcept { second_ = t; }
	void set_position_accuracy(bool t) noexcept { position_accuracy_ = t; }
	void set_epfd_fix(epfd_fix_type t) noexcept { epfd_fix_ = t; }
	void set_raim(bool t) noexcept { raim_ = t; }
	void set_radio_status(uint32_t t) noexcept { radio_status_ = t; }

	std::optional<geo::longitude> get_lon() const;
	std::optional<geo::latitude> get_lat() const;
	void set_lon(const std::optional<geo::longitude> & t);
	void set_lat(const std::optional<geo::latitude> & t);
};
}

#endif
