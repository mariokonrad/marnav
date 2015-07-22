#ifndef __AIS__MESSAGE_18__HPP__
#define __AIS__MESSAGE_18__HPP__

#include "message.hpp"
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav
{
namespace ais
{

/// @todo TESTING
class message_18 : public message
{
public:
	constexpr static const message_id ID = message_id::standard_class_b_cs_position_report;
	constexpr static const int SIZE_BITS = 168;

	message_18();
	message_18(const message_18 &) = default;
	message_18 & operator=(const message_18 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & bits) throw(std::invalid_argument);

protected:
	message_18(message_id id);
	void read_data(const raw & bits);

private:
	uint32_t repeat_indicator;
	uint32_t mmsi;
	uint32_t sog; // speed over ground, in 0.1 knots
	bool position_accuracy;
	uint32_t longitude_minutes; // in 10000 minutes
	uint32_t latitude_minutes; // in 10000 minutes
	uint32_t cog; // course of ground in 0.1 deg true north
	uint32_t hdg; // true heading in deg
	uint32_t timestamp;
	bool cs_unit; // false = class B SOTDMA unit, true = class B CS unit
	bool display_flag; // false = no visual display, true = has display
	bool dsc_flag; // true = unit is attached to VHF with DSC capability
	bool band_flag;
	bool message_22_flag;
	bool assigned; // false = autonomous mode (default), true = assigned mode
	bool raim;
	uint32_t radio_status;

public:
	uint32_t get_repeat_indicator() const { return repeat_indicator; }
	utils::mmsi get_mmsi() const { return utils::mmsi{mmsi}; }
	uint32_t get_sog() const { return sog; }
	bool get_position_accuracy() const { return position_accuracy; }
	uint32_t get_cog() const { return cog; }
	uint32_t get_hdg() const { return hdg; }
	uint32_t get_timestamp() const { return timestamp; }
	bool get_cs_unit() const { return cs_unit; }
	bool get_display_flag() const { return display_flag; }
	bool get_dsc_flag() const { return dsc_flag; }
	bool get_band_flag() const { return band_flag; }
	bool get_message_22_flag() const { return message_22_flag; }
	bool get_assigned() const { return assigned; }
	bool get_raim() const { return raim; }
	uint32_t get_radio_status() const { return radio_status; }

	void set_repeat_indicator(uint32_t t) { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) { mmsi = t; }
	void set_sog(uint32_t t) { sog = t; }
	void set_position_accuracy(bool t) { position_accuracy = t; }
	void set_cog(uint32_t t) { cog = t; }
	void set_hdg(uint32_t t) { hdg = t; }
	void set_timestamp(uint32_t t) { timestamp = t; }
	void set_cs_unit(bool t) { cs_unit = t; }
	void set_display_flag(bool t) { display_flag = t; }
	void set_dsc_flag(bool t) { dsc_flag = t; }
	void set_band_flag(bool t) { band_flag = t; }
	void set_message_22_flag(bool t) { message_22_flag = t; }
	void set_assigned(bool t) { assigned = t; }
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
