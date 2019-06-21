#ifndef MARNAV__AIS__MESSAGE_21__HPP
#define MARNAV__AIS__MESSAGE_21__HPP

#include <marnav/ais/message.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace ais
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
	virtual raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t              > repeat_indicator = 0;
	bitset_value<  8, 30, uint32_t              > mmsi = 0;
	bitset_value< 38,  5, aid_type_id           > aid_type = aid_type_id::unspecified;
	bitset_value< 43, 20, std::string           > name;
	bitset_value<163,  1, bool                  > position_accuracy = false;
	bitset_value<164, 28, uint32_t              > longitude_minutes = longitude_not_available; // in 10000 minutes
	bitset_value<192, 27, uint32_t              > latitude_minutes = latitude_not_available; // in 10000 minutes
	bitset_value<219,  9, uint32_t              > to_bow = 0;
	bitset_value<228,  9, uint32_t              > to_stern = 0;
	bitset_value<237,  6, uint32_t              > to_port = 0;
	bitset_value<243,  6, uint32_t              > to_starboard = 0;
	bitset_value<249,  4, epfd_fix_type         > epfd_fix = epfd_fix_type::undefined;
	bitset_value<253,  6, uint32_t              > utc_second = 0;
	bitset_value<259,  1, off_position_indicator> off_position = off_position_indicator::off_position;
	bitset_value<260,  8, uint8_t               > regional = 0;
	bitset_value<268,  1, bool                  > raim = false;
	bitset_value<269,  1, virtual_aid           > virtual_aid_flag = virtual_aid::virtual_aid;
	bitset_value<270,  1, bool                  > assigned = false;
	std::string name_extension;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	aid_type_id get_aid_type() const noexcept { return aid_type; }
	std::string get_name() const;
	bool get_position_accuracy() const noexcept { return position_accuracy; }
	uint32_t get_to_bow() const noexcept { return to_bow; }
	uint32_t get_to_stern() const noexcept { return to_stern; }
	uint32_t get_to_port() const noexcept { return to_port; }
	uint32_t get_to_starboard() const noexcept { return to_starboard; }
	epfd_fix_type get_epfd_fix() const noexcept { return epfd_fix; }
	uint32_t get_utc_second() const noexcept { return utc_second; }
	off_position_indicator get_off_position() const noexcept { return off_position; }
	uint8_t get_regional() const noexcept { return regional; }
	bool get_raim() const noexcept { return raim; }
	virtual_aid get_virtual_aid_flag() const noexcept { return virtual_aid_flag; }
	bool get_assigned() const noexcept { return assigned; }
	std::string get_name_extension() const;

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_aid_type(aid_type_id t) noexcept { aid_type = t; }
	void set_name(const std::string & t);
	void set_position_accuracy(bool t) noexcept { position_accuracy = t; }
	void set_to_bow(uint32_t t) noexcept { to_bow = t; }
	void set_to_stern(uint32_t t) noexcept { to_stern = t; }
	void set_to_port(uint32_t t) noexcept { to_port = t; }
	void set_to_starboard(uint32_t t) noexcept { to_starboard = t; }
	void set_epfd_fix(epfd_fix_type t) noexcept { epfd_fix = t; }
	void set_utc_second(uint32_t t) noexcept { utc_second = t; }
	void set_off_position(off_position_indicator t) noexcept { off_position = t; }
	void set_regional(uint8_t t) noexcept { regional = t; }
	void set_raim(bool t) noexcept { raim = t; }
	void set_virtual_aid_flag(virtual_aid t) noexcept { virtual_aid_flag = t; }
	void set_assigned(bool t) noexcept { assigned = t; }
	void set_name_extension(const std::string & t);

	utils::optional<geo::longitude> get_longitude() const;
	utils::optional<geo::latitude> get_latitude() const;
	void set_longitude(const utils::optional<geo::longitude> & t);
	void set_latitude(const utils::optional<geo::latitude> & t);
};
}
}

#endif
