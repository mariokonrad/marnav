#ifndef __AIS__MESSAGE_24__HPP__
#define __AIS__MESSAGE_24__HPP__

#include "message.hpp"
#include <marnav/geo/angle.hpp>

namespace marnav
{
namespace ais
{

/// @todo TESTING
///
/// @note This class combines both possible parts of message 24 (A and B).
///       It also contains all necessary stuff to have a normal and auxiliary
///       part B. The consequence is, some attributes are never used, depending
///       on other attributes. Since this is not the single true OO design (tm),
///       this implementation is intentional and serves the purpose well enough,
///       without further complication of the design.
class message_24 : public message
{
public:
	constexpr static const message_id ID = message_id::static_data_report;
	constexpr static const int SIZE_BITS = 168;
	constexpr static const int SIZE_BITS_IGNORED_SPARES_OF_TYPE_A = 160;

	enum class part : uint32_t { A = 0, B = 1 };

	message_24();
	message_24(const message_24 &) = default;
	message_24 & operator=(const message_24 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & bits) throw(std::invalid_argument);

	bool is_auxiliary_vessel() const;

private:
	message_24(message_id id);
	void read_data(const raw & bits);

private:
	uint32_t repeat_indicator;
	uint32_t mmsi;
	part part_number;

	// part A specific
	std::string shipname;

	// part B specific
	ship_type shiptype;
	std::string vendor_id;
	uint32_t model;
	uint32_t serial;
	std::string callsign;

	// part B specific (normal)
	uint32_t to_bow;
	uint32_t to_stern;
	uint32_t to_port;
	uint32_t to_starboard;

	// part B specific (auxiliary)
	uint32_t mothership_mmsi;

public:
	uint32_t get_repeat_indicator() const { return repeat_indicator; }
	uint32_t get_mmsi() const { return mmsi; }
	part get_part_number() const { return part_number; }

	// part A specific
	std::string get_shipname() const { return shipname; }

	// part B specific (normal)
	ship_type get_shiptype() const { return shiptype; }
	std::string get_vendor_id() const { return vendor_id; }
	uint32_t get_model() const { return model; }
	uint32_t get_serial() const { return serial; }
	std::string get_callsign() const { return callsign; }

	// part B specific (normal)
	uint32_t get_to_bow() const { return to_bow; }
	uint32_t get_to_stern() const { return to_stern; }
	uint32_t get_to_port() const { return to_port; }
	uint32_t get_to_starboard() const { return to_starboard; }

	// part B specific (auxiliary)
	uint32_t get_mothership_mmsi() const { return mothership_mmsi; }

	void set_repeat_indicator(uint32_t t) { repeat_indicator = t; }
	void set_mmsi(uint32_t t) { mmsi = t; }
	void set_part_number(part t) { part_number = t; }

	// part A specific
	void set_shipname(const std::string & t) { shipname = t; }

	// part B specific
	void set_shiptype(ship_type t) { shiptype = t; }
	void set_vendor_id(const std::string & t) { vendor_id = t; }
	void set_model(uint32_t t) { model = t; }
	void set_serial(uint32_t t) { serial = t; }
	void set_callsign(const std::string & t) { callsign = t; }

	// part B specific (normal)
	void set_to_bow(uint32_t t) { to_bow = t; }
	void set_to_stern(uint32_t t) { to_stern = t; }
	void set_to_port(uint32_t t) { to_port = t; }
	void set_to_starboard(uint32_t t) { to_starboard = t; }

	// part B specific (auxiliary)
	void set_mothership_mmsi(uint32_t t) { mothership_mmsi = t; }
};
}
}

#endif
