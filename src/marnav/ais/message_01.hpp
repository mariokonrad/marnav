#ifndef __AIS__MESSAGE_01__HPP__
#define __AIS__MESSAGE_01__HPP__

#include "message.hpp"
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav
{
namespace ais
{

class message_01 : public message
{
public:
	constexpr static const message_id ID = message_id::position_report_class_a;
	constexpr static const int SIZE_BITS = 168;

	message_01();
	message_01(const message_01 &) = default;
	message_01 & operator=(const message_01 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & bits) throw(std::invalid_argument);

protected:
	message_01(message_id id);
	void read_data(const raw & bits);

private:
	uint32_t repeat_indicator;
	uint32_t mmsi;
	navigation_status nav_status;
	int8_t rot; // rate of turn, raw format
	uint32_t sog; // speed over ground, in 0.1 knots
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
	uint32_t get_repeat_indicator() const { return repeat_indicator; }
	utils::mmsi get_mmsi() const { return utils::mmsi{mmsi}; }
	int8_t get_rot() const { return rot; }
	uint32_t get_sog() const { return sog; }
	bool get_position_accuracy() const { return position_accuracy; }
	uint32_t get_cog() const { return cog; }
	uint32_t get_hdg() const { return hdg; }
	uint32_t get_timestamp() const { return timestamp; }
	uint32_t get_maneuver_indicator() const { return maneuver_indicator; }
	bool get_raim() const { return raim; }
	uint32_t get_radio_status() const { return radio_status; }

	void set_repeat_indicator(uint32_t t) { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) { mmsi = t; }
	void set_nav_status(navigation_status t) { nav_status = t; }
	void set_rot(int8_t t) { rot = t; }
	void set_sog(uint32_t t) { sog = t; }
	void set_position_accuracy(bool t) { position_accuracy = t; }
	void set_cog(uint32_t t) { cog = t; }
	void set_hdg(uint32_t t) { hdg = t; }
	void set_timestamp(uint32_t t) { timestamp = t; }
	void set_maneuver_indicator(uint32_t t) { maneuver_indicator = t; }
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
