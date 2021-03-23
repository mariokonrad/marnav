#ifndef MARNAV_AIS_MESSAGE_18_HPP
#define MARNAV_AIS_MESSAGE_18_HPP

#include <marnav/ais/message.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/units/units.hpp>
#include <marnav/utils/mmsi.hpp>
#include <optional>

namespace marnav
{
namespace ais
{
/// @brief Standard Class B CS Position Report
class message_18 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::standard_class_b_cs_position_report;
	constexpr static std::size_t SIZE_BITS = 168u;

	message_18();
	message_18(const message_18 &) = default;
	message_18 & operator=(const message_18 &) = default;
	message_18(message_18 &&) = default;
	message_18 & operator=(message_18 &&) = default;

protected:
	message_18(message_id id);
	message_18(const raw & bits);
	void read_data(const raw & bits);
	virtual raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t> repeat_indicator = 0;
	bitset_value<  8, 30, uint32_t> mmsi = 0;
	bitset_value< 46, 10, uint32_t> sog = sog_not_available; // speed over ground, in 0.1 knots
	bitset_value< 56,  1, bool    > position_accuracy = false;
	bitset_value< 57, 28, uint32_t> longitude_minutes = longitude_not_available; // in 10000 minutes
	bitset_value< 85, 27, uint32_t> latitude_minutes = latitude_not_available; // in 10000 minutes
	bitset_value<112, 12, uint32_t> cog = cog_not_available; // course of ground in 0.1 deg true north
	bitset_value<124,  9, uint32_t> hdg = hdg_not_available; // true heading in deg
	bitset_value<133,  6, uint32_t> timestamp = timestamp_not_available;
	bitset_value<141,  1, bool    > cs_unit = false; // false = class B SOTDMA unit, true = class B CS unit
	bitset_value<142,  1, bool    > display_flag = false; // false = no visual display, true = has display
	bitset_value<143,  1, bool    > dsc_flag = false; // true = unit is attached to VHF with DSC capability
	bitset_value<144,  1, bool    > band_flag = false;
	bitset_value<145,  1, bool    > message_22_flag = false;
	bitset_value<146,  1, bool    > assigned = false; // false = autonomous mode (default), true = assigned mode
	bitset_value<147,  1, bool    > raim = false;
	bitset_value<148, 20, uint32_t> radio_status = 0;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	std::optional<units::knots> get_sog() const noexcept;
	bool get_position_accuracy() const noexcept { return position_accuracy; }
	std::optional<double> get_cog() const noexcept;
	std::optional<uint32_t> get_hdg() const noexcept;
	uint32_t get_timestamp() const noexcept { return timestamp; }
	bool get_cs_unit() const noexcept { return cs_unit; }
	bool get_display_flag() const noexcept { return display_flag; }
	bool get_dsc_flag() const noexcept { return dsc_flag; }
	bool get_band_flag() const noexcept { return band_flag; }
	bool get_message_22_flag() const noexcept { return message_22_flag; }
	bool get_assigned() const noexcept { return assigned; }
	bool get_raim() const noexcept { return raim; }
	uint32_t get_radio_status() const noexcept { return radio_status; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }

	void set_sog_unavailable();
	void set_sog(units::velocity t);

	void set_position_accuracy(bool t) noexcept { position_accuracy = t; }
	void set_cog(std::optional<double> t) noexcept;
	void set_hdg(std::optional<uint32_t> t) noexcept;
	void set_timestamp(uint32_t t) noexcept { timestamp = t; }
	void set_cs_unit(bool t) noexcept { cs_unit = t; }
	void set_display_flag(bool t) noexcept { display_flag = t; }
	void set_dsc_flag(bool t) noexcept { dsc_flag = t; }
	void set_band_flag(bool t) noexcept { band_flag = t; }
	void set_message_22_flag(bool t) noexcept { message_22_flag = t; }
	void set_assigned(bool t) noexcept { assigned = t; }
	void set_raim(bool t) noexcept { raim = t; }
	void set_radio_status(uint32_t t) noexcept { radio_status = t; }

	std::optional<geo::longitude> get_lon() const;
	std::optional<geo::latitude> get_lat() const;
	void set_lon_unavailable();
	void set_lat_unavailable();
	void set_lon(const geo::longitude & t);
	void set_lat(const geo::latitude & t);
};
}
}

#endif
