#ifndef __AIS__MESSAGE_09__HPP__
#define __AIS__MESSAGE_09__HPP__

#include "message.hpp"
#include <marnav/geo/angle.hpp>

namespace marnav
{
namespace ais
{

class message_09 : public message
{
public:
	constexpr static const message_id ID = message_id::standard_sar_aircraft_position_report;
	constexpr static const int SIZE_BITS = 168;

	constexpr static const uint32_t altitude_not_available = 4095;
	constexpr static const uint32_t speed_not_available = 1023;

	message_09();
	message_09(const message_09 &) = default;
	message_09 & operator=(const message_09 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & bits) throw(std::invalid_argument);

protected:
	void read_data(const raw & bits);

private:
	unsigned int repeat_indicator;
	uint32_t mmsi;
	uint32_t altitude;
	uint32_t speed; // speed over ground in knots
	uint32_t position_accuracy;
	uint32_t longitude_minutes; // in 10000 minutes
	uint32_t latitude_minutes; // in 10000 minutes
	uint32_t course; // in 0.1 degrees
	uint32_t utc_second;
	uint8_t reserved;
	bool dte;
	bool assigned;
	bool raim;
	uint32_t radio_status;

public:
	unsigned int get_repeat_indicator() const { return repeat_indicator; }
	uint32_t get_mmsi() const { return mmsi; }
	uint32_t get_altitude() const { return altitude; }
	uint32_t get_speed() const { return speed; }
	bool get_position_accuracy() const { return position_accuracy; }
	uint32_t get_longitude_minutes() const;
	uint32_t get_latitude_minutes() const;
	uint32_t get_course() const { return course; }
	uint32_t get_utc_second() const { return utc_second; }
	bool get_dte() const { return dte; }
	bool get_assigned() const { return assigned; }
	bool get_raim() const { return raim; }
	uint32_t get_radio_status() const { return radio_status; }

	void set_repeat_indicator(unsigned int t) { repeat_indicator = t; }
	void set_mmsi(uint32_t t) { mmsi = t; }
	void set_altitude(uint32_t t) { altitude = t; }
	void set_speed(uint32_t t) { speed= t; }
	void set_position_accuracy(bool t) { position_accuracy = t; }
	void set_longitude_minutes(uint32_t t) { longitude_minutes = t; }
	void set_latitude_minutes(uint32_t t) { latitude_minutes = t; }
	void set_course(uint32_t t ) { course = t; }
	void set_utc_second(uint32_t t) { utc_second =t; }
	void set_dte(bool t) { dte = t; }
	void set_assigned(bool t) { assigned =t; }
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
