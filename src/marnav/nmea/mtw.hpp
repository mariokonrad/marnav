#ifndef __NMEA__MTW__HPP__
#define __NMEA__MTW__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(mtw)

/// @brief MTW - Mean Temperature of Water
///
/// @code
///        1   2
///        |   |
/// $--MTW,x.x,C*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Degrees
/// 2. Unit of Measurement
///    - C = Celcius
///
class mtw : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(mtw)

public:
	constexpr static const sentence_id ID = sentence_id::MTW;
	constexpr static const char * TAG = "MTW";

	mtw();
	mtw(const mtw &) = default;
	mtw & operator=(const mtw &) = default;
	mtw(mtw &&) = default;
	mtw & operator=(mtw &&) = default;

protected:
	mtw(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> temperature; // water temperature
	utils::optional<unit::temperature> temperature_unit; // unit degrees, C:celcius

public:
	MARNAV_NMEA_GETTER(temperature)
	MARNAV_NMEA_GETTER(temperature_unit)

	void set_temperature(double t) noexcept;
};
}
}

#endif
