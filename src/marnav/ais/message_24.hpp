#ifndef __AIS__MESSAGE_24__HPP__
#define __AIS__MESSAGE_24__HPP__

#include <marnav/ais/message.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav
{
namespace ais
{

/// @brief Static Data Report
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

	static std::unique_ptr<message> parse(const raw & bits);

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
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	part get_part_number() const noexcept { return part_number; }

	// part A specific
	std::string get_shipname() const { return shipname; }

	// part B specific (normal)
	ship_type get_shiptype() const noexcept { return shiptype; }
	std::string get_vendor_id() const { return vendor_id; }
	uint32_t get_model() const noexcept { return model; }
	uint32_t get_serial() const noexcept { return serial; }
	std::string get_callsign() const { return callsign; }

	// part B specific (normal)
	uint32_t get_to_bow() const noexcept { return to_bow; }
	uint32_t get_to_stern() const noexcept { return to_stern; }
	uint32_t get_to_port() const noexcept { return to_port; }
	uint32_t get_to_starboard() const noexcept { return to_starboard; }

	// part B specific (auxiliary)
	utils::mmsi get_mothership_mmsi() const noexcept { return utils::mmsi{mothership_mmsi}; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_part_number(part t) noexcept { part_number = t; }

	// part A specific
	void set_shipname(const std::string & t) { shipname = t; }

	// part B specific
	void set_shiptype(ship_type t) noexcept { shiptype = t; }
	void set_vendor_id(const std::string & t) { vendor_id = t; }
	void set_model(uint32_t t) noexcept { model = t; }
	void set_serial(uint32_t t) noexcept { serial = t; }
	void set_callsign(const std::string & t) { callsign = t; }

	// part B specific (normal)
	void set_to_bow(uint32_t t) noexcept { to_bow = t; }
	void set_to_stern(uint32_t t) noexcept { to_stern = t; }
	void set_to_port(uint32_t t) noexcept { to_port = t; }
	void set_to_starboard(uint32_t t) noexcept { to_starboard = t; }

	// part B specific (auxiliary)
	void set_mothership_mmsi(const utils::mmsi & t) noexcept { mothership_mmsi = t; }
};
}
}

#endif
