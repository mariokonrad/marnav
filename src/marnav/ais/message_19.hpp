#ifndef MARNAV__AIS__MESSAGE_19__HPP
#define MARNAV__AIS__MESSAGE_19__HPP

#include <marnav/ais/message.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace ais
{
/// @brief Extended Class B Equipment Position Report
class message_19 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::extended_class_b_equipment_position_report;
	constexpr static std::size_t SIZE_BITS = 312u;

	message_19();
	message_19(const message_19 &) = default;
	message_19 & operator=(const message_19 &) = default;
	message_19(message_19 &&) = default;
	message_19 & operator=(message_19 &&) = default;

protected:
	message_19(message_id id);
	message_19(const raw & bits);
	void read_data(const raw & bits);
	virtual raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t     > repeat_indicator = 0;
	bitset_value<  8, 30, uint32_t     > mmsi = 0;
	bitset_value< 46, 10, uint32_t     > sog = sog_not_available; // speed over ground, in 0.1 knots
	bitset_value< 56,  1, bool         > position_accuracy = false;
	bitset_value< 57, 28, uint32_t     > longitude_minutes = longitude_not_available; // in 10000 minutes
	bitset_value< 85, 27, uint32_t     > latitude_minutes = latitude_not_available; // in 10000 minutes
	bitset_value<112, 12, uint32_t     > cog = cog_not_available; // course of ground in 0.1 deg true north
	bitset_value<124,  9, uint32_t     > hdg = hdg_not_available; // true heading in deg
	bitset_value<133,  6, uint32_t     > timestamp = timestamp_not_available;
	bitset_value<143, 20, std::string  > shipname;
	bitset_value<263,  8, ship_type    > shiptype = ship_type::not_available;
	bitset_value<271,  9, uint32_t     > to_bow = 0;
	bitset_value<280,  9, uint32_t     > to_stern = 0;
	bitset_value<289,  6, uint32_t     > to_port = 0;
	bitset_value<295,  6, uint32_t     > to_starboard = 0;
	bitset_value<301,  4, epfd_fix_type> epfd_fix = epfd_fix_type::undefined;
	bitset_value<305,  1, bool         > raim = false;
	bitset_value<306,  1, data_terminal> dte = data_terminal::not_ready;
	bitset_value<307,  1, bool         > assigned = false;
	// clang-format on

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
	data_terminal get_dte() const noexcept { return dte; }
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
	void set_dte(data_terminal t) noexcept { dte = t; }
	void set_assigned(bool t) noexcept { assigned = t; }

	utils::optional<geo::longitude> get_longitude() const;
	utils::optional<geo::latitude> get_latitude() const;
	void set_longitude(const utils::optional<geo::longitude> & t);
	void set_latitude(const utils::optional<geo::latitude> & t);
};
}
}

#endif
