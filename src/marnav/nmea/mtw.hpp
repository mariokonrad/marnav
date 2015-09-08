#ifndef __NMEA__MTW__HPP__
#define __NMEA__MTW__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

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
public:
	constexpr static const sentence_id ID = sentence_id::MTW;
	constexpr static const char * TAG = "MTW";

	mtw();
	mtw(const mtw &) = default;
	mtw & operator=(const mtw &) = default;

	static std::unique_ptr<sentence> parse(
		const std::string & talker, const std::vector<std::string> & fields);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> temperature; // water temperature
	utils::optional<unit::temperature> temperature_unit; // unit degrees, C:celcius

public:
	NMEA_GETTER(temperature)
	NMEA_GETTER(temperature_unit)

	void set_temperature(double t) noexcept;
};
}
}

#endif
