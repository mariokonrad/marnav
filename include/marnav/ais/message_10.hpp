#ifndef MARNAV_AIS_MESSAGE_10_HPP
#define MARNAV_AIS_MESSAGE_10_HPP

#include <marnav/ais/message.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav::ais
{
/// @brief UTC/Date Inquiry
class message_10 : public message
{
	friend class detail::factory;

public:
	constexpr static message_id ID = message_id::utc_and_date_inquiry;
	constexpr static std::size_t SIZE_BITS = 72u;

	message_10();
	message_10(const message_10 &) = default;
	message_10 & operator=(const message_10 &) = default;
	message_10(message_10 &&) = default;
	message_10 & operator=(message_10 &&) = default;

protected:
	message_10(const raw & bits);
	void read_data(const raw & bits);
	raw get_data() const override;

private:
	// clang-format off
	bitset_value< 6,  2, uint32_t> repeat_indicator_ = 0;
	bitset_value< 8, 30, uint32_t> mmsi_ = 0;
	bitset_value<40, 30, uint32_t> dest_mmsi_ = 0;
	// clang-format on

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator_; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi_}; }
	utils::mmsi get_dest_mmsi() const noexcept { return utils::mmsi{dest_mmsi_}; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator_ = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi_ = t; }
	void set_dest_mmsi(const utils::mmsi & t) noexcept { mmsi_ = t; }
};
}

#endif
