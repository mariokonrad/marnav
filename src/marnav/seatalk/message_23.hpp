#ifndef __SEATALK__MESSAGE_23__HPP__
#define __SEATALK__MESSAGE_23__HPP__

#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace seatalk
{

/// @brief Water temperature (ST50)
///
/// @code
/// 23 Z1 XX YY
///
/// Water temperature (ST50): XX deg Celsius, YY deg Fahrenheit
///    Flag Z&4: Sensor defective or not connected (Z=4)
/// @endcode
///
/// Corresponding NMEA sentence: MTW
///
class message_23 : public message
{
public:
	constexpr static const message_id ID = message_id::water_temperature_1;

	message_23();
	message_23(const message_23 &) = default;
	message_23 & operator=(const message_23 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data) throw(std::invalid_argument);

private:
	bool sensor_defective;
	uint8_t temperature_celsius; // degrees celsius
	uint8_t temperature_fahrenheit; // degrees fahrenheit

public:
	bool get_sensor_defective() const { return sensor_defective; }
	uint8_t get_celsius() const { return temperature_celsius; }
	uint8_t get_fahrenheit() const { return temperature_fahrenheit; }

	void set_sensor_defective(bool t) { sensor_defective = t; }
	void set_celsius(uint8_t t) { temperature_celsius = t; }
	void set_fahrenheit(uint8_t t) { temperature_fahrenheit = t; }
};
}
}

#endif
