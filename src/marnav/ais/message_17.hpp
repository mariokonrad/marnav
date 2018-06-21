#ifndef MARNAV__AIS__MESSAGE_17__HPP
#define MARNAV__AIS__MESSAGE_17__HPP

#include <marnav/ais/message.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace ais
{
/// @brief DGNSS Broadcast Binary Message
class message_17 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::dgnss_binary_broadcast_message;
	constexpr static std::size_t SIZE_BITS_MIN = 80u;
	constexpr static std::size_t SIZE_BITS_MAX = 816u;

	message_17();
	message_17(const message_17 &) = default;
	message_17 & operator=(const message_17 &) = default;
	message_17(message_17 &&) = default;
	message_17 & operator=(message_17 &&) = default;

protected:
	message_17(message_id id);
	message_17(const raw & bits);
	void read_data(const raw & bits);
	virtual raw get_data() const override;

private:
	// clang-format off
	bitset_value< 6,  2, uint32_t> repeat_indicator = 0;
	bitset_value< 8, 30, uint32_t> mmsi = 0;
	bitset_value<40, 18, uint32_t> longitude_minutes = longitude_not_available_short;
	bitset_value<58, 17, uint32_t> latitude_minutes = latitude_not_available_short;
	// clang-format on

	raw payload;

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	const raw & get_payload() const { return payload; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_payload(const raw & p);

	utils::optional<geo::longitude> get_longitude() const;
	utils::optional<geo::latitude> get_latitude() const;
	void set_longitude(const utils::optional<geo::longitude> & t);
	void set_latitude(const utils::optional<geo::latitude> & t);
};
}
}

#endif
