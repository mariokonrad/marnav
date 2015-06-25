#ifndef __NMEA__MTW__HPP__
#define __NMEA__MTW__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief MTW - Mean Temperature of Water
///
/// @code
///        1   2 3
///        |   | |
/// $--MTW,x.x,C*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
///  1. Degrees
///  2. Unit of Measurement, Celcius
///  3. Checksum
///
class mtw : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::MTW;

	mtw();
	mtw(const mtw &) = default;
	mtw & operator=(const mtw &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> temperature; // water temperature
	utils::optional<char> unit; // unit degrees, C:celcius

public:
	decltype(temperature) get_temperature() const { return temperature; }
	decltype(unit) get_unit() const { return unit; }

	void set_temperature(double t)
	{
		temperature = t;
		unit = unit::CELSIUS;
	}
};
}
}

#endif
