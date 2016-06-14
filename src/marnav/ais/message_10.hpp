#ifndef __AIS__MESSAGE_10__HPP__
#define __AIS__MESSAGE_10__HPP__

#include <marnav/ais/message.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav
{
namespace ais
{

/// @brief UTC/Date Inquiry
class message_10 : public message
{
public:
	constexpr static const message_id ID = message_id::utc_and_date_inquiry;
	constexpr static const int SIZE_BITS = 72;

	message_10();
	message_10(const message_10 &) = default;
	message_10 & operator=(const message_10 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & bits);

protected:
	void read_data(const raw & bits);

private:
	unsigned int repeat_indicator = 0;
	uint32_t mmsi = 0;
	uint32_t dest_mmsi = 0;

public:
	unsigned int get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	utils::mmsi get_dest_mmsi() const noexcept { return utils::mmsi{dest_mmsi}; }

	void set_repeat_indicator(unsigned int t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_dest_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
};
}
}

#endif
