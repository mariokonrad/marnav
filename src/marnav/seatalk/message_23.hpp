#ifndef MARNAV__SEATALK__MESSAGE_23__HPP
#define MARNAV__SEATALK__MESSAGE_23__HPP

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
	constexpr static size_t SIZE = 4;

	message_23();
	message_23(const message_23 &) = default;
	message_23 & operator=(const message_23 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	bool sensor_defective_;
	uint8_t temperature_celsius_; // degrees celsius
	uint8_t temperature_fahrenheit_; // degrees fahrenheit

public:
	bool get_sensor_defective() const noexcept { return sensor_defective_; }
	uint8_t get_celsius() const noexcept { return temperature_celsius_; }
	uint8_t get_fahrenheit() const noexcept { return temperature_fahrenheit_; }

	void set_sensor_defective(bool t) noexcept { sensor_defective_ = t; }
	void set_celsius(uint8_t t) noexcept { temperature_celsius_ = t; }
	void set_fahrenheit(uint8_t t) noexcept { temperature_fahrenheit_ = t; }
};
}
}

#endif
