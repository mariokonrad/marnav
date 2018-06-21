#ifndef MARNAV__NMEA__MTW__HPP
#define MARNAV__NMEA__MTW__HPP

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
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::MTW;
	constexpr static const char * TAG = "MTW";

	mtw();
	mtw(const mtw &) = default;
	mtw & operator=(const mtw &) = default;
	mtw(mtw &&) = default;
	mtw & operator=(mtw &&) = default;

protected:
	mtw(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<double> temperature_; // water temperature
	utils::optional<unit::temperature> temperature_unit_; // unit degrees, C:celcius

public:
	decltype(temperature_) get_temperature() const { return temperature_; }
	decltype(temperature_unit_) get_temperature_unit() const { return temperature_unit_; }

	void set_temperature(double t) noexcept;
};
}
}

#endif
