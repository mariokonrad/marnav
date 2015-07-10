#ifndef __NMEA__VBW__HPP__
#define __NMEA__VBW__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief VBW - Dual Ground/Water Speed
///
/// @code
///        1   2   3 4   5   6 7
///        |   |   | |   |   | |
/// $--VBW,x.x,x.x,A,x.x,x.x,A*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
/// 1. Longitudinal water speed, "-" means astern
/// 2. Transverse water speed, "-" means port
/// 3. Status, A = Data Valid
/// 4. Longitudinal ground speed, "-" means astern
/// 5. Transverse ground speed, "-" means port
/// 6. Status, A = Data Valid
/// 7. Checksum
///
class vbw : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::VBW;
	constexpr static const char * TAG = "VBW";

	vbw();
	vbw(const vbw &) = default;
	vbw & operator=(const vbw &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> water_speed_longitudinal;
	utils::optional<double> water_speed_transveral;
	utils::optional<char> water_speed_status;
	utils::optional<double> ground_speed_longitudinal;
	utils::optional<double> ground_speed_transveral;
	utils::optional<char> ground_speed_status;

public:
	decltype(water_speed_longitudinal) get_water_speed_longitudinal() const
	{
		return water_speed_longitudinal;
	}
	decltype(water_speed_transveral) get_water_speed_transveral() const
	{
		return water_speed_transveral;
	}
	decltype(water_speed_status) get_water_speed_status() const
	{
		return water_speed_status;
	}
	decltype(ground_speed_longitudinal) get_ground_speed_longitudinal() const
	{
		return ground_speed_longitudinal;
	}
	decltype(ground_speed_transveral) get_ground_speed_transveral() const
	{
		return ground_speed_transveral;
	}
	decltype(ground_speed_status) get_ground_speed_status() const
	{
		return water_speed_status;
	}

	void set_water_speed(double l, double t, char s);
	void set_ground_speed(double l, double t, char s);
};
}
}

#endif
