#ifndef __AIS__MESSAGE_05__HPP__
#define __AIS__MESSAGE_05__HPP__

#include "message.hpp"

namespace ais
{
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
	message_05(const message_05&) = default;
	message_05& operator=(const message_05&) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw& bits) throw(std::invalid_argument);

protected:
	void read_data(const raw& bits);

	std::string read_string(const raw& bits, raw::size_type ofs,
							raw::size_type count_sixbits) const;
	void write_string(raw& bits, raw::size_type ofs, raw::size_type count_sixbits,
					  const std::string& s) const;

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
	uint32_t get_mmsi() const { return mmsi; }
	uint32_t get_ais_version() const { return ais_version; }
	uint32_t get_imo_number() const { return imo_number; }
	std::string get_callsign() const { return callsign; }
	std::string get_shipname() const { return shipname; }
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
	std::string get_destination() const { return destination; }
	bool get_dte() const { return dte; }
};
}

#endif
