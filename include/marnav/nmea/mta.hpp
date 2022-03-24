#ifndef MARNAV_NMEA_MTA_HPP
#define MARNAV_NMEA_MTA_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>

namespace marnav
{
namespace nmea
{
/// @brief MTA - Air Temperature
///
/// @code
///        1   2
///        |   |
/// $--MTA,x.x,C*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Temperature in degrees Celsius
/// 2. Temperature unit
///    - C = Celsius
///
class mta : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::MTA;
	constexpr static const char * TAG = "MTA";

	mta();
	mta(const mta &) = default;
	mta & operator=(const mta &) = default;
	mta(mta &&) = default;
	mta & operator=(mta &&) = default;

protected:
	mta(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	units::celsius temperature_;

public:
	units::celsius get_temperature() const { return temperature_; }

	void set_temperature(units::temperature t) noexcept;
};
}
}

#endif
