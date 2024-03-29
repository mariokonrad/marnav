#ifndef MARNAV_AIS_MESSAGE_24_HPP
#define MARNAV_AIS_MESSAGE_24_HPP

#include <marnav/ais/message.hpp>
#include <marnav/ais/vessel_dimension.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav::ais
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
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::static_data_report;
	constexpr static std::size_t SIZE_BITS = 168u;
	constexpr static std::size_t SIZE_BITS_IGNORED_SPARES_OF_TYPE_A = 160u;

	enum class part : uint32_t { A = 0, B = 1 };

	message_24();
	message_24(const message_24 &) = default;
	message_24 & operator=(const message_24 &) = default;
	message_24(message_24 &&) = default;
	message_24 & operator=(message_24 &&) = default;

	bool is_auxiliary_vessel() const;

private:
	message_24(message_id id);
	message_24(const raw & bits);
	void read_data(const raw & bits);
	raw get_data() const override;

private:
	// clang-format off
	bitset_value< 6,  2, uint32_t> repeat_indicator_ = 0;
	bitset_value< 8, 30, uint32_t> mmsi_ = 0;
	bitset_value<38,  2, part    > part_number_ = part::A;

	// part A specific
	bitset_value<40, 20, std::string> shipname_;

	// part B specific
	bitset_value<40,  8, ship_type  > shiptype_ = ship_type::not_available;
	bitset_value<48,  3, std::string> vendor_id_;
	bitset_value<66,  4, uint32_t   > model_ = 0;
	bitset_value<70, 20, uint32_t   > serial_ = 0;
	bitset_value<90,  7, std::string> callsign_;

	// part B specific (normal)
	bitset_value<132, 9, uint32_t> to_bow_ = 0;
	bitset_value<141, 9, uint32_t> to_stern_ = 0;
	bitset_value<150, 6, uint32_t> to_port_ = 0;
	bitset_value<156, 6, uint32_t> to_starboard_ = 0;

	// part B specific (auxiliary)
	bitset_value<132, 30, uint32_t> mothership_mmsi_ = 0;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator_; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi_}; }
	part get_part_number() const noexcept { return part_number_; }

	// part A specific
	std::string get_shipname() const;

	// part B specific (normal)
	ship_type get_shiptype() const noexcept { return shiptype_; }
	std::string get_vendor_id() const;
	uint32_t get_model() const noexcept { return model_; }
	uint32_t get_serial() const noexcept { return serial_; }
	std::string get_callsign() const;

	// part B specific (normal)
	vessel_dimension get_vessel_dimension() const noexcept;

	// part B specific (auxiliary)
	utils::mmsi get_mothership_mmsi() const noexcept { return utils::mmsi{mothership_mmsi_}; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator_ = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi_ = t; }
	void set_part_number(part t) noexcept { part_number_ = t; }

	// part A specific
	void set_shipname(const std::string & t);

	// part B specific
	void set_shiptype(ship_type t) noexcept { shiptype_ = t; }
	void set_vendor_id(const std::string & t);
	void set_model(uint32_t t) noexcept { model_ = t; }
	void set_serial(uint32_t t) noexcept { serial_ = t; }
	void set_callsign(const std::string & t);

	// part B specific (normal)
	void set_vessel_dimension(const vessel_dimension & t);

	// part B specific (auxiliary)
	void set_mothership_mmsi(const utils::mmsi & t) noexcept { mothership_mmsi_ = t; }
};
}

#endif
