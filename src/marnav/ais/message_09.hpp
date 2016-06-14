#ifndef __AIS__MESSAGE_09__HPP__
#define __AIS__MESSAGE_09__HPP__

#include <marnav/ais/message.hpp>
#include <marnav/geo/angle.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav
{
namespace ais
{

/// @brief Standard SAR Aircraft Position Report.
class message_09 : public message
{
public:
	constexpr static const message_id ID = message_id::standard_sar_aircraft_position_report;
	constexpr static const int SIZE_BITS = 168;

	constexpr static const uint32_t altitude_not_available = 4095;

	message_09();
	message_09(const message_09 &) = default;
	message_09 & operator=(const message_09 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & bits);

protected:
	void read_data(const raw & bits);

private:
	unsigned int repeat_indicator = 0;
	uint32_t mmsi = 0;
	uint32_t altitude = altitude_not_available;
	uint32_t speed = sog_not_available; // speed over ground in knots
	bool position_accuracy = false;
	uint32_t longitude_minutes = longitude_not_available; // in 10000 minutes
	uint32_t latitude_minutes = latitude_not_available; // in 10000 minutes
	uint32_t course = cog_not_available; // in 0.1 degrees
	uint32_t utc_second = second_not_available;
	uint8_t reserved = 0;
	bool dte = false;
	bool assigned = false;
	bool raim = false;
	uint32_t radio_status = 0;

public:
	unsigned int get_repeat_indicator() const noexcept { return repeat_indicator; }
	utils::mmsi get_mmsi() const noexcept { return utils::mmsi{mmsi}; }
	uint32_t get_altitude() const noexcept { return altitude; }
	uint32_t get_speed() const noexcept { return speed; }
	bool get_position_accuracy() const noexcept { return position_accuracy; }
	uint32_t get_course() const noexcept { return course; }
	uint32_t get_utc_second() const noexcept { return utc_second; }
	bool get_dte() const noexcept { return dte; }
	bool get_assigned() const noexcept { return assigned; }
	bool get_raim() const noexcept { return raim; }
	uint32_t get_radio_status() const noexcept { return radio_status; }

	void set_repeat_indicator(unsigned int t) noexcept { repeat_indicator = t; }
	void set_mmsi(const utils::mmsi & t) noexcept { mmsi = t; }
	void set_altitude(uint32_t t) noexcept { altitude = t; }
	void set_speed(uint32_t t) noexcept { speed = t; }
	void set_position_accuracy(bool t) noexcept { position_accuracy = t; }
	void set_course(uint32_t t) noexcept { course = t; }
	void set_utc_second(uint32_t t) noexcept { utc_second = t; }
	void set_dte(bool t) noexcept { dte = t; }
	void set_assigned(bool t) noexcept { assigned = t; }
	void set_raim(bool t) noexcept { raim = t; }
	void set_radio_status(uint32_t t) noexcept { radio_status = t; }

	geo::longitude get_longitude() const;
	geo::latitude get_latitude() const;
	void set_longitude(const geo::longitude & t);
	void set_latitude(const geo::latitude & t);
};
}
}

#endif
