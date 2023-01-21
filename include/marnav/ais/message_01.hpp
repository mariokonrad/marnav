#ifndef MARNAV_AIS_MESSAGE_01_HPP
#define MARNAV_AIS_MESSAGE_01_HPP

#include <marnav/ais/message.hpp>
#include <marnav/ais/rate_of_turn.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/units/units.hpp>
#include <marnav/utils/mmsi.hpp>
#include <optional>

namespace marnav::ais
{
/// @brief Position Report Class A
class message_01 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::position_report_class_a;
	constexpr static std::size_t SIZE_BITS = 168u;

	message_01();
	message_01(const message_01 &) = default;
	message_01 & operator=(const message_01 &) = default;
	message_01(message_01 &&) = default;
	message_01 & operator=(message_01 &&) = default;

protected:
	message_01(message_id id);
	message_01(const raw & bits);
	void read_data(const raw & bits);
	raw get_data() const override;

private:
	// clang-format off
	bitset_value<  6,  2, uint32_t             > repeat_indicator_ = 0;
	bitset_value<  8, 30, uint32_t             > mmsi_ = 0;
	bitset_value< 38,  4, navigation_status    > nav_status_ = navigation_status::not_defined;
	bitset_value< 42,  8, int8_t               > rot_ = rate_of_turn::no_information_available;
	bitset_value< 50, 10, uint32_t             > sog_ = sog_not_available;
	bitset_value< 60,  1, bool                 > position_accuracy_ = false;
	bitset_value< 61, 28, uint32_t             > longitude_minutes_ = longitude_not_available; // in 10000 minutes
	bitset_value< 89, 27, uint32_t             > latitude_minutes_ = latitude_not_available; // in 10000 minutes
	bitset_value<116, 12, uint32_t             > cog_ = cog_not_available;
	bitset_value<128,  9, uint32_t             > hdg_ = hdg_not_available;
	bitset_value<137,  6, uint32_t             > timestamp_ = timestamp_not_available;
	bitset_value<143,  2, maneuver_indicator_id> maneuver_indicator_ = maneuver_indicator_id::not_available;
	bitset_value<148,  1, bool                 > raim_ = false;
	bitset_value<149, 19, uint32_t             > radio_status_ = 0;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator_; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi_}; }
	navigation_status get_nav_status() const noexcept { return nav_status_; }
	rate_of_turn get_rot() const noexcept;
	std::optional<units::knots> get_sog() const noexcept;
	bool get_position_accuracy() const noexcept { return position_accuracy_; }
	std::optional<double> get_cog() const noexcept;
	std::optional<uint32_t> get_hdg() const noexcept;

	/// @todo Handle special values (61..63)
	uint32_t get_timestamp() const noexcept { return timestamp_; }

	maneuver_indicator_id get_maneuver_indicator() const noexcept
	{
		return maneuver_indicator_;
	}

	bool get_raim() const noexcept { return raim_; }
	uint32_t get_radio_status() const noexcept { return radio_status_; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator_ = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi_ = t; }
	void set_nav_status(navigation_status t) noexcept { nav_status_ = t; }
	void set_rot(rate_of_turn t) noexcept;

	void set_sog_unavailable();
	void set_sog(units::velocity t);

	void set_position_accuracy(bool t) noexcept { position_accuracy_ = t; }
	void set_cog(std::optional<double> t) noexcept;
	void set_hdg(std::optional<uint32_t> t) noexcept;
	void set_timestamp(uint32_t t) noexcept { timestamp_ = t; }
	void set_maneuver_indicator(maneuver_indicator_id t) noexcept { maneuver_indicator_ = t; }
	void set_raim(bool t) noexcept { raim_ = t; }
	void set_radio_status(uint32_t t) noexcept { radio_status_ = t; }

	std::optional<geo::longitude> get_lon() const;
	std::optional<geo::latitude> get_lat() const;
	void set_lon_unavailable();
	void set_lat_unavailable();
	void set_lon(const geo::longitude & t);
	void set_lat(const geo::latitude & t);
};
}

#endif
