#ifndef MARNAV__SEATALK__MESSAGE_26__HPP
#define MARNAV__SEATALK__MESSAGE_26__HPP

#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace seatalk
{

/// @brief Speed through water
///
/// @code
/// 26 04 XX XX YY YY DE
///
/// XXXX/100 Knots, sensor 1, current speed, valid if D & 4 == 4
/// YYYY/100 Knots, average speed (trip/time) if D & 8 == 0
///          or data from sensor 2 if D & 8 == 8
/// E & 1 == 1: Average speed calulation stopped
/// E & 2 == 2: Display value in MPH
/// @endcode
///
/// Corresponding NMEA sentence: VHW
///
class message_26 : public message
{
public:
	constexpr static const message_id ID = message_id::speed_through_water_2;
	constexpr static size_t SIZE = 7;

	message_26();
	message_26(const message_26 &) = default;
	message_26 & operator=(const message_26 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	uint16_t speed1_;
	uint16_t speed2_;
	uint8_t status_;

public:
	bool is_display_in_mph() const noexcept { return (status_ & 0x02) != 0; }
	bool avg_speed_calc_stopped() const noexcept { return (status_ & 0x01) != 0; }
	bool is_sensor1_valid() const noexcept { return (status_ & 0x40) != 0; }
	bool is_avg_valid() const noexcept { return (status_ & 0x80) == 0; }
	bool is_sensor2_valid() const noexcept { return (status_ & 0x80) != 0; }

	double get_speed1() const noexcept;
	double get_speed2() const noexcept;

	void set_display_in_mph(bool t) noexcept;
	void set_avg_speed_calc_stopped(bool t) noexcept;
	void set_sensor1_valid(bool t) noexcept;
	void set_avg_valid() noexcept { status_ &= ~0x80; }
	void set_sensor2_valid() noexcept { status_ |= 0x80; }

	void set_speed1(double t) noexcept;
	void set_speed2(double t) noexcept;
};
}
}

#endif
