#ifndef MARNAV_AIS_MESSAGE_19_HPP
#define MARNAV_AIS_MESSAGE_19_HPP

#include <marnav/ais/message.hpp>
#include <marnav/ais/vessel_dimension.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/units/units.hpp>
#include <marnav/utils/mmsi.hpp>
#include <optional>

namespace marnav::ais
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
	raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t     > repeat_indicator_ = 0;
	bitset_value<  8, 30, uint32_t     > mmsi_ = 0;
	bitset_value< 46, 10, uint32_t     > sog_ = sog_not_available; // speed over ground, in 0.1 knots
	bitset_value< 56,  1, bool         > position_accuracy_ = false;
	bitset_value< 57, 28, uint32_t     > longitude_minutes_ = longitude_not_available; // in 10000 minutes
	bitset_value< 85, 27, uint32_t     > latitude_minutes_ = latitude_not_available; // in 10000 minutes
	bitset_value<112, 12, uint32_t     > cog_ = cog_not_available; // course of ground in 0.1 deg true north
	bitset_value<124,  9, uint32_t     > hdg_ = hdg_not_available; // true heading in deg
	bitset_value<133,  6, uint32_t     > timestamp_ = timestamp_not_available;
	bitset_value<143, 20, std::string  > shipname_;
	bitset_value<263,  8, ship_type    > shiptype_ = ship_type::not_available;
	bitset_value<271,  9, uint32_t     > to_bow_ = 0;
	bitset_value<280,  9, uint32_t     > to_stern_ = 0;
	bitset_value<289,  6, uint32_t     > to_port_ = 0;
	bitset_value<295,  6, uint32_t     > to_starboard_ = 0;
	bitset_value<301,  4, epfd_fix_type> epfd_fix_ = epfd_fix_type::undefined;
	bitset_value<305,  1, bool         > raim_ = false;
	bitset_value<306,  1, data_terminal> dte_ = data_terminal::not_ready;
	bitset_value<307,  1, bool         > assigned_ = false;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator_; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi_}; }
	std::optional<units::knots> get_sog() const noexcept;
	bool get_position_accuracy() const noexcept { return position_accuracy_; }
	uint32_t get_cog() const noexcept { return cog_; }
	uint32_t get_hdg() const noexcept { return hdg_; }
	uint32_t get_timestamp() const noexcept { return timestamp_; }
	std::string get_shipname() const { return shipname_; }
	ship_type get_shiptype() const noexcept { return shiptype_; }
	vessel_dimension get_vessel_dimension() const noexcept;
	epfd_fix_type get_epfd_fix() const noexcept { return epfd_fix_; }
	bool get_raim() const noexcept { return raim_; }
	data_terminal get_dte() const noexcept { return dte_; }
	bool get_assigned() const noexcept { return assigned_; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator_ = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi_ = t; }

	void set_sog_unavailable();
	void set_sog(units::velocity t);

	void set_position_accuracy(bool t) noexcept { position_accuracy_ = t; }
	void set_cog(uint32_t t) noexcept { cog_ = t; }
	void set_hdg(uint32_t t) noexcept { hdg_ = t; }
	void set_timestamp(uint32_t t) noexcept { timestamp_ = t; }
	void set_shipname(const std::string & t);
	void set_shiptype(ship_type t) noexcept { shiptype_ = t; }
	void set_vessel_dimension(const vessel_dimension & t);
	void set_epfd_fix(epfd_fix_type t) noexcept { epfd_fix_ = t; }
	void set_raim(bool t) noexcept { raim_ = t; }
	void set_dte(data_terminal t) noexcept { dte_ = t; }
	void set_assigned(bool t) noexcept { assigned_ = t; }

	std::optional<geo::longitude> get_lon() const;
	std::optional<geo::latitude> get_lat() const;
	void set_lon_unavailable();
	void set_lat_unavailable();
	void set_lon(const geo::longitude & t);
	void set_lat(const geo::latitude & t);
};
}

#endif
