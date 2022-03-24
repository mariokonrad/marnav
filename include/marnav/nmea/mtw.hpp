#ifndef MARNAV_NMEA_MTW_HPP
#define MARNAV_NMEA_MTW_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	units::celsius temperature_; // water temperature

public:
	units::temperature get_temperature() const { return {temperature_}; }

	void set_temperature(units::temperature t) noexcept;
};
}
}

#endif
