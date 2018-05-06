#ifndef MARNAV__AIS__MESSAGE_10__HPP
#define MARNAV__AIS__MESSAGE_10__HPP

#include <marnav/ais/message.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace ais
{
/// @brief UTC/Date Inquiry
class MARNAV_EXPORT message_10 : public message
{
	friend class detail::factory;

public:
	constexpr static const message_id ID = message_id::utc_and_date_inquiry;
	constexpr static const int SIZE_BITS = 72;

	message_10();
	message_10(const message_10 &) = default;
	message_10 & operator=(const message_10 &) = default;
	message_10(message_10 &&) = default;
	message_10 & operator=(message_10 &&) = default;

protected:
	message_10(const raw & bits);
	void read_data(const raw & bits);
	virtual raw get_data() const override;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
	// clang-format off
	bitset_value< 6,  2, uint32_t> repeat_indicator = 0;
	bitset_value< 8, 30, uint32_t> mmsi = 0;
	bitset_value<40, 30, uint32_t> dest_mmsi = 0;
	// clang-format on
#ifdef _MSC_VER
#pragma warning(pop)
#endif

public:
	uint32_t get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	utils::mmsi get_dest_mmsi() const noexcept { return utils::mmsi{dest_mmsi}; }

	void set_repeat_indicator(uint32_t t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_dest_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
};
}
}

#endif
