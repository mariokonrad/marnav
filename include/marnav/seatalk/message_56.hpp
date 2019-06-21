#ifndef MARNAV__SEATALK__MESSAGE_56__HPP
#define MARNAV__SEATALK__MESSAGE_56__HPP

#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace seatalk
{

/// @brief Date
///
/// @code
/// 56 M1 DD YY
///
/// YY year, M month, DD day in month
/// @endcode
///
/// Corresponding NMEA sentence: RMC
///
class message_56 : public message
{
public:
	constexpr static const message_id ID = message_id::date;
	constexpr static size_t SIZE = 4;

	message_56();
	message_56(const message_56 &) = default;
	message_56 & operator=(const message_56 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	uint8_t year_;
	uint8_t month_;
	uint8_t day_;

public:
	uint8_t get_year() const noexcept { return year_; }
	uint8_t get_month() const noexcept { return month_; }
	uint8_t get_day() const noexcept { return day_; }

	void set_date(uint8_t y, uint8_t m, uint8_t d) noexcept;
};
}
}

#endif
