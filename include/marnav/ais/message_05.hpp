#ifndef MARNAV_AIS_MESSAGE_05_HPP
#define MARNAV_AIS_MESSAGE_05_HPP

#include <marnav/ais/message.hpp>
#include <marnav/ais/vessel_dimension.hpp>
#include <marnav/units/units.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav::ais
{
/// @brief Static and Voyage related Data
///
/// This message handles messages of normal size 424 bits. The (presumably) common
/// occurrence of 422 bits, are also handled. The encoded message always is 424 bits.
/// The occurrence of 420 bits messages are not supported.
///
class message_05 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::static_and_voyage_related_data;
	constexpr static std::size_t SIZE_BITS = 424u;
	constexpr static std::size_t SIZE_BITS_MIN = 422u;

	constexpr static uint32_t eta_month_not_available = 0;
	constexpr static uint32_t eta_day_not_available = 0;
	constexpr static uint32_t eta_hour_not_available = 24;
	constexpr static uint32_t eta_minute_not_available = 60;

	message_05();
	message_05(const message_05 &) = default;
	message_05 & operator=(const message_05 &) = default;
	message_05(message_05 &&) = default;
	message_05 & operator=(message_05 &&) = default;

protected:
	message_05(const raw & bits);
	void read_data(const raw & bits);
	raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t     > repeat_indicator_ = 0;
	bitset_value<  8, 30, uint32_t     > mmsi_ = 0;
	bitset_value< 38,  2, uint32_t     > ais_version_ = 0;
	bitset_value< 40, 30, uint32_t     > imo_number_ = 0;
	bitset_value< 70,  7, std::string  > callsign_;
	bitset_value<112, 20, std::string  > shipname_;
	bitset_value<232,  8, ship_type    > shiptype_ = ship_type::not_available;
	bitset_value<240,  9, uint32_t     > to_bow_ = 0;
	bitset_value<249,  9, uint32_t     > to_stern_ = 0;
	bitset_value<258,  6, uint32_t     > to_port_ = 0;
	bitset_value<264,  6, uint32_t     > to_starboard_ = 0;
	bitset_value<270,  4, epfd_fix_type> epfd_fix_ = epfd_fix_type::undefined;
	bitset_value<274,  4, uint32_t     > eta_month_ = eta_month_not_available;
	bitset_value<278,  5, uint32_t     > eta_day_ = eta_day_not_available;
	bitset_value<283,  5, uint32_t     > eta_hour_ = eta_hour_not_available;
	bitset_value<288,  6, uint32_t     > eta_minute_ = eta_minute_not_available;
	bitset_value<294,  8, uint32_t     > draught_ = 0; // in 0.1m
	bitset_value<302, 20, std::string  > destination_;
	bitset_value<422,  1, data_terminal> dte_ = data_terminal::not_ready;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator_; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi_}; }
	uint32_t get_ais_version() const noexcept { return ais_version_; }
	uint32_t get_imo_number() const noexcept { return imo_number_; }
	std::string get_callsign() const;
	std::string get_shipname() const;
	ship_type get_shiptype() const noexcept { return shiptype_; }
	vessel_dimension get_vessel_dimension() const noexcept;
	epfd_fix_type get_epfd_fix() const noexcept { return epfd_fix_; }
	uint32_t get_eta_month() const noexcept { return eta_month_; }
	uint32_t get_eta_day() const noexcept { return eta_day_; }
	uint32_t get_eta_hour() const noexcept { return eta_hour_; }
	uint32_t get_eta_minute() const noexcept { return eta_minute_; }
	units::meters get_draught() const noexcept;
	std::string get_destination() const;
	data_terminal get_dte() const noexcept { return dte_; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator_ = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi_ = t; }
	void set_ais_version(uint32_t t) noexcept { ais_version_ = t; }
	void set_imo_number(uint32_t t) noexcept { imo_number_ = t; }
	void set_callsign(const std::string & t);
	void set_shipname(const std::string & t);
	void set_shiptype(ship_type t) noexcept { shiptype_ = t; }
	void set_vessel_dimension(const vessel_dimension & t);
	void set_epfd_fix(epfd_fix_type t) noexcept { epfd_fix_ = t; }
	void set_eta_month(uint32_t t) noexcept { eta_month_ = t; }
	void set_eta_day(uint32_t t) noexcept { eta_day_ = t; }
	void set_eta_hour(uint32_t t) noexcept { eta_hour_ = t; }
	void set_eta_minute(uint32_t t) noexcept { eta_minute_ = t; }

	// The resolution of the draught is in 0.1m. For safety reasons, the value
	// is ceiled within the resolution of 0.1m.
	// Example:
	//   set_draught(units::meters{1.5})  => stored draught 1.5
	//   set_draught(units::meters{1.51}) => stored draught 1.6
	void set_draught(units::length t);

	void set_destination(const std::string & t);
	void set_dte(data_terminal t) noexcept { dte_ = t; }
};
}

#endif
