#ifndef __AIS__MESSAGE_05__HPP__
#define __AIS__MESSAGE_05__HPP__

#include <marnav/ais/message.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav
{
namespace ais
{

/// @brief Static and Voyage related Data
class message_05 : public message
{
public:
	constexpr static const message_id ID = message_id::static_and_voyage_related_data;
	constexpr static const int SIZE_BITS = 424;

	constexpr static const uint32_t eta_month_not_available = 0;
	constexpr static const uint32_t eta_day_not_available = 0;
	constexpr static const uint32_t eta_hour_not_available = 24;
	constexpr static const uint32_t eta_minute_not_available = 60;

	message_05();
	message_05(const message_05 &) = default;
	message_05 & operator=(const message_05 &) = default;

	virtual raw get_data() const throw(std::out_of_range) override;

	static std::unique_ptr<message> parse(const raw & bits) throw(
		std::invalid_argument, std::out_of_range);

protected:
	void read_data(const raw & bits) throw(std::out_of_range);

private:
	unsigned int repeat_indicator;
	uint32_t mmsi;
	uint32_t ais_version;
	uint32_t imo_number;
	std::string callsign;
	std::string shipname;
	ship_type shiptype;
	uint32_t to_bow;
	uint32_t to_stern;
	uint32_t to_port;
	uint32_t to_starboard;
	epfd_fix_type epfd_fix;
	uint32_t eta_month;
	uint32_t eta_day;
	uint32_t eta_hour;
	uint32_t eta_minute;
	uint32_t draught; // in 0.1m
	std::string destination;
	bool dte;

public:
	unsigned int get_repeat_indicator() const { return repeat_indicator; }
	utils::mmsi get_mmsi() const { return utils::mmsi{mmsi}; }
	uint32_t get_ais_version() const { return ais_version; }
	uint32_t get_imo_number() const { return imo_number; }
	std::string get_callsign() const;
	std::string get_shipname() const;
	ship_type get_shiptype() const { return shiptype; }
	uint32_t get_to_bow() const { return to_bow; }
	uint32_t get_to_stern() const { return to_stern; }
	uint32_t get_to_port() const { return to_port; }
	uint32_t get_to_starboard() const { return to_starboard; }
	epfd_fix_type get_epfd_fix() const { return epfd_fix; }
	uint32_t get_eta_month() const { return eta_month; }
	uint32_t get_eta_day() const { return eta_day; }
	uint32_t get_eta_hour() const { return eta_hour; }
	uint32_t get_eta_minute() const { return eta_minute; }
	uint32_t get_draught() const { return draught; }
	std::string get_destination() const;
	bool get_dte() const { return dte; }

	void set_repeat_indicator(unsigned int t) { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) { mmsi = t; }
	void set_ais_version(uint32_t t) { ais_version = t; }
	void set_imo_number(uint32_t t) { imo_number = t; }
	void set_callsign(const std::string & t);
	void set_shipname(const std::string & t);
	void set_shiptype(ship_type t) { shiptype = t; }
	void set_to_bow(uint32_t t) { to_bow = t; }
	void set_to_stern(uint32_t t) { to_stern = t; }
	void set_to_port(uint32_t t) { to_port = t; }
	void set_to_starboard(uint32_t t) { to_starboard = t; }
	void set_epfd_fix(epfd_fix_type t) { epfd_fix = t; }
	void set_eta_month(uint32_t t) { eta_month = t; }
	void set_eta_day(uint32_t t) { eta_day = t; }
	void set_eta_hour(uint32_t t) { eta_hour = t; }
	void set_eta_minute(uint32_t t) { eta_minute = t; }
	void set_draught(uint32_t t) { draught = t; }
	void set_destination(const std::string & t);
	void set_dte(bool t) { dte = t; }
};
}
}

#endif
