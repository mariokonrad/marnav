#ifndef __AIS__MESSAGE_01__HPP__
#define __AIS__MESSAGE_01__HPP__

#include "message.hpp"

namespace ais
{

class message_01 : public message
{
public:
	constexpr static const message_id ID = message_id::position_report_class_a;

	constexpr static const uint32_t longitude_not_available = 0x6791AC0;
	constexpr static const uint32_t latitude_not_available = 0x3412140;
	constexpr static const uint32_t cog_not_available = 3600;
	constexpr static const uint32_t hdg_not_available = 511;
	constexpr static const uint8_t timestamp_not_available = 60;
	constexpr static const uint8_t maneuver_indictor_not_available = 0;

	message_01();
	message_01(const message_01&) = default;
	message_01& operator=(const message_01&) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw& bits) throw(std::invalid_argument);

protected:
	message_01(message_id id);
	void read_data(const raw& bits);

private:
	unsigned int repeat_indicator;
	uint32_t mmsi;
	navigation_status nav_status;
	int8_t rot; // rate of turn, raw format
	unsigned int sog; // speed over ground, in 0.1 knots
	bool position_accuracy;
	uint32_t longitude_minutes; // in 10000 minutes
	uint32_t latitude_minutes; // in 10000 minutes
	uint32_t cog; // course of ground in 0.1 deg true north
	uint32_t hdg; // true heading in deg
	uint32_t timestamp;
	uint32_t maneuver_indicator;
	bool raim;
	uint32_t radio_status;

public:
	unsigned int get_repeat_indicator() const { return repeat_indicator; }
	uint32_t get_mmsi() const { return mmsi; }
	int8_t get_rot() const { return rot; }
	unsigned int get_sog() const { return sog; }
	bool get_position_accuracy() const { return position_accuracy; }
	double get_longitude() const;
	double get_latitude() const;
	uint32_t get_cog() const { return cog; }
	uint32_t get_hdg() const { return hdg; }
	uint32_t get_timestamp() const { return timestamp; }
	uint32_t get_maneuver_indicator() const { return maneuver_indicator; }
	bool get_raim() const { return raim; }
	uint32_t get_radio_status() const { return radio_status; }
};

}

#endif
