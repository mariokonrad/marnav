#ifndef MARNAV_AIS_MESSAGE_21_HPP
#define MARNAV_AIS_MESSAGE_21_HPP

#include <marnav/ais/message.hpp>
#include <marnav/ais/vessel_dimension.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>
#include <optional>

namespace marnav::ais
{
/// @brief Aid-to-Navigation Report
class message_21 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::aid_to_navigation_report;
	constexpr static std::size_t SIZE_BITS_MIN = 272u;
	constexpr static std::size_t SIZE_BITS_MAX = 360u;

	message_21();
	message_21(const message_21 &) = default;
	message_21 & operator=(const message_21 &) = default;
	message_21(message_21 &&) = default;
	message_21 & operator=(message_21 &&) = default;

protected:
	message_21(const raw & bits);
	void read_data(const raw & bits);
	raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t              > repeat_indicator_ = 0;
	bitset_value<  8, 30, uint32_t              > mmsi_ = 0;
	bitset_value< 38,  5, aid_type_id           > aid_type_ = aid_type_id::unspecified;
	bitset_value< 43, 20, std::string           > name_;
	bitset_value<163,  1, bool                  > position_accuracy_ = false;
	bitset_value<164, 28, uint32_t              > longitude_minutes_ = longitude_not_available; // in 10000 minutes
	bitset_value<192, 27, uint32_t              > latitude_minutes_ = latitude_not_available; // in 10000 minutes
	bitset_value<219,  9, uint32_t              > to_bow_ = 0;
	bitset_value<228,  9, uint32_t              > to_stern_ = 0;
	bitset_value<237,  6, uint32_t              > to_port_ = 0;
	bitset_value<243,  6, uint32_t              > to_starboard_ = 0;
	bitset_value<249,  4, epfd_fix_type         > epfd_fix_ = epfd_fix_type::undefined;
	bitset_value<253,  6, uint32_t              > utc_second_ = 0;
	bitset_value<259,  1, off_position_indicator> off_position_ = off_position_indicator::off_position;
	bitset_value<260,  8, uint8_t               > regional_ = 0;
	bitset_value<268,  1, bool                  > raim_ = false;
	bitset_value<269,  1, virtual_aid           > virtual_aid_flag_ = virtual_aid::virtual_aid;
	bitset_value<270,  1, bool                  > assigned_ = false;
	std::string name_extension_;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator_; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi_}; }
	aid_type_id get_aid_type() const noexcept { return aid_type_; }
	std::string get_name() const;
	bool get_position_accuracy() const noexcept { return position_accuracy_; }
	vessel_dimension get_vessel_dimension() const noexcept;
	epfd_fix_type get_epfd_fix() const noexcept { return epfd_fix_; }
	uint32_t get_utc_second() const noexcept { return utc_second_; }
	off_position_indicator get_off_position() const noexcept { return off_position_; }
	uint8_t get_regional() const noexcept { return regional_; }
	bool get_raim() const noexcept { return raim_; }
	virtual_aid get_virtual_aid_flag() const noexcept { return virtual_aid_flag_; }
	bool get_assigned() const noexcept { return assigned_; }
	std::string get_name_extension() const;

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator_ = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi_ = t; }
	void set_aid_type(aid_type_id t) noexcept { aid_type_ = t; }
	void set_name(const std::string & t);
	void set_position_accuracy(bool t) noexcept { position_accuracy_ = t; }
	void set_vessel_dimension(const vessel_dimension & t);
	void set_epfd_fix(epfd_fix_type t) noexcept { epfd_fix_ = t; }
	void set_utc_second(uint32_t t) noexcept { utc_second_ = t; }
	void set_off_position(off_position_indicator t) noexcept { off_position_ = t; }
	void set_regional(uint8_t t) noexcept { regional_ = t; }
	void set_raim(bool t) noexcept { raim_ = t; }
	void set_virtual_aid_flag(virtual_aid t) noexcept { virtual_aid_flag_ = t; }
	void set_assigned(bool t) noexcept { assigned_ = t; }
	void set_name_extension(const std::string & t);

	std::optional<geo::longitude> get_lon() const;
	std::optional<geo::latitude> get_lat() const;
	void set_lon_unavailable();
	void set_lat_unavailable();
	void set_lon(const geo::longitude & t);
	void set_lat(const geo::latitude & t);
};
}

#endif
