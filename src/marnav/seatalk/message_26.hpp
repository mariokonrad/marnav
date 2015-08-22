#ifndef __SEATALK__MESSAGE_26__HPP__
#define __SEATALK__MESSAGE_26__HPP__

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

	message_26();
	message_26(const message_26 &) = default;
	message_26 & operator=(const message_26 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data) throw(std::invalid_argument);

private:
	uint16_t speed1;
	uint16_t speed2;
	uint8_t status;

public:
	bool is_display_in_mph() const { return (status & 0x02) != 0; }
	bool avg_speed_calc_stopped() const { return (status & 0x01) != 0; }
	bool is_sensor1_valid() const { return (status & 0x40) != 0; }
	bool is_avg_valid() const { return (status & 0x80) == 0; }
	bool is_sensor2_valid() const { return (status & 0x80) != 0; }

	double get_speed1() const;
	double get_speed2() const;

	void set_display_in_mph(bool t);
	void set_avg_speed_calc_stopped(bool t);
	void set_sensor1_valid(bool t);
	void set_avg_valid() { status &= ~0x80; }
	void set_sensor2_valid() { status |= 0x80; }

	void set_speed1(double t);
	void set_speed2(double t);
};
}
}

#endif
