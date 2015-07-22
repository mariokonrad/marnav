#ifndef __AIS__MESSAGE_04__HPP__
#define __AIS__MESSAGE_04__HPP__

#include "message.hpp"
#include <marnav/geo/angle.hpp>

namespace marnav
{
namespace ais
{

class message_04 : public message
{
public:
	constexpr static const message_id ID = message_id::base_station_report;
	constexpr static const int SIZE_BITS = 168;

	constexpr static const uint32_t eta_month_not_available = 0;
	constexpr static const uint32_t eta_day_not_available = 0;
	constexpr static const uint32_t eta_hour_not_available = 24;
	constexpr static const uint32_t eta_minute_not_available = 60;

	message_04();
	message_04(const message_04 &) = default;
	message_04 & operator=(const message_04 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & bits) throw(std::invalid_argument);

protected:
	message_04(message_id id);
	void read_data(const raw & bits);

private:
	unsigned int repeat_indicator;
	uint32_t mmsi;
	uint32_t year; // UTC, 1..9999
	uint32_t month; // UTC, 1..12
	uint32_t day; // UTC, 1..31
	uint32_t hour; // UTC, 0..23
	uint32_t minute;
	uint32_t second;
	bool position_accuracy;
	uint32_t longitude_minutes; // in 10000 minutes
	uint32_t latitude_minutes; // in 10000 minutes
	epfd_fix_type epfd_fix;
	bool raim;
	uint32_t radio_status;

public:
	unsigned int get_repeat_indicator() const { return repeat_indicator; }
	uint32_t get_mmsi() const { return mmsi; }
	uint32_t get_year() const { return year; }
	uint32_t get_month() const { return month; }
	uint32_t get_day() const { return day; }
	uint32_t get_hour() const { return hour; }
	uint32_t get_minute() const { return minute; }
	uint32_t get_second() const { return second; }
	bool get_position_accuracy() const { return position_accuracy; }
	uint32_t get_longitude_minutes() const;
	uint32_t get_latitude_minutes() const;
	epfd_fix_type get_epfd_fix() const { return epfd_fix; }
	bool get_raim() const { return raim; }
	uint32_t get_radio_status() const { return radio_status; }

	void set_repeat_indicator(unsigned int t) { repeat_indicator = t; }
	void set_mmsi(uint32_t t) { mmsi = t; }
	void set_year(uint32_t t) { year = t; }
	void set_month(uint32_t t) { month = t; }
	void set_day(uint32_t t) { day = t; }
	void set_hour(uint32_t t) { hour = t; }
	void set_minute(uint32_t t) { minute = t; }
	void set_second(uint32_t t) { second = t; }
	void set_position_accuracy(bool t) { position_accuracy = t; }
	void set_longitude_minutes(uint32_t t) { longitude_minutes = t; }
	void set_latitude_minutes(uint32_t t) { latitude_minutes = t; }
	void set_epfd_fix(epfd_fix_type t) { epfd_fix = t; }
	void set_raim(bool t) { raim = t; }
	void set_radio_status(uint32_t t) { radio_status = t; }

	geo::longitude get_longitude() const;
	geo::latitude get_latitude() const;
	void set_longitude(const geo::longitude & t);
	void set_latitude(const geo::latitude & t);
};
}
}

#endif
