#ifndef __AIS__MESSAGE_19__HPP__
#define __AIS__MESSAGE_19__HPP__

#include <marnav/ais/message.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav
{
namespace ais
{

/// @brief Extended Class B Equipment Position Report
class message_19 : public message
{
public:
	constexpr static const message_id ID
		= message_id::extended_class_b_equipment_position_report;
	constexpr static const int SIZE_BITS = 312;

	message_19();
	message_19(const message_19 &) = default;
	message_19 & operator=(const message_19 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & bits);

protected:
	message_19(message_id id);
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
	std::string shipname;
	ship_type shiptype;
	uint32_t to_bow;
	uint32_t to_stern;
	uint32_t to_port;
	uint32_t to_starboard;
	epfd_fix_type epfd_fix;
	bool raim;
	bool dte;
	bool assigned;

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	uint32_t get_sog() const noexcept { return sog; }
	bool get_position_accuracy() const noexcept { return position_accuracy; }
	uint32_t get_cog() const noexcept { return cog; }
	uint32_t get_hdg() const noexcept { return hdg; }
	uint32_t get_timestamp() const noexcept { return timestamp; }
	std::string get_shipname() const { return shipname; }
	ship_type get_shiptype() const noexcept { return shiptype; }
	uint32_t get_to_bow() const noexcept { return to_bow; }
	uint32_t get_to_stern() const noexcept { return to_stern; }
	uint32_t get_to_port() const noexcept { return to_port; }
	uint32_t get_to_starboard() const noexcept { return to_starboard; }
	epfd_fix_type get_epfd_fix() const noexcept { return epfd_fix; }
	bool get_raim() const noexcept { return raim; }
	bool get_dte() const noexcept { return dte; }
	bool get_assigned() const noexcept { return assigned; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_sog(uint32_t t) noexcept { sog = t; }
	void set_position_accuracy(bool t) noexcept { position_accuracy = t; }
	void set_cog(uint32_t t) noexcept { cog = t; }
	void set_hdg(uint32_t t) noexcept { hdg = t; }
	void set_timestamp(uint32_t t) noexcept { timestamp = t; }
	void set_shipname(const std::string & t);
	void set_shiptype(ship_type t) noexcept { shiptype = t; }
	void set_to_bow(uint32_t t) noexcept { to_bow = t; }
	void set_to_stern(uint32_t t) noexcept { to_stern = t; }
	void set_to_port(uint32_t t) noexcept { to_port = t; }
	void set_to_starboard(uint32_t t) noexcept { to_starboard = t; }
	void set_epfd_fix(epfd_fix_type t) noexcept { epfd_fix = t; }
	void set_raim(bool t) noexcept { raim = t; }
	void set_dte(bool t) noexcept { dte = t; }
	void set_assigned(bool t) noexcept { assigned = t; }

	geo::longitude get_longitude() const;
	geo::latitude get_latitude() const;
	void set_longitude(const geo::longitude & t);
	void set_latitude(const geo::latitude & t);
};
}
}

#endif
