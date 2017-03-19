#ifndef MARNAV__NMEA__RSA__HPP
#define MARNAV__NMEA__RSA__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief RSA - Rudder Sensor Angle
///
/// @code
///        1   2 3   4
///        |   | |   |
/// $--RSA,x.x,A,x.x,A*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Starboard (or single) rudder sensor, "-" means Turn To Port
/// 2. Status, A means data is valid
///    - A = data is valid
///    - V = invalid
/// 3. Port rudder sensor
/// 4. Status, A means data is valid
///    - A = data is valid
///    - V = invalid
///
class rsa : public sentence
{
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::RSA;
	constexpr static const char * TAG = "RSA";

	rsa();
	rsa(const rsa &) = default;
	rsa & operator=(const rsa &) = default;
	rsa(rsa &&) = default;
	rsa & operator=(rsa &&) = default;

protected:
	rsa(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	utils::optional<double> rudder1;
	utils::optional<status> rudder1_valid;
	utils::optional<double> rudder2;
	utils::optional<status> rudder2_valid;

public:
	decltype(rudder1) get_rudder1() const { return rudder1; }
	decltype(rudder1_valid) get_rudder1_valid() const { return rudder1_valid; }
	decltype(rudder2) get_rudder2() const { return rudder2; }
	decltype(rudder2_valid) get_rudder2_valid() const { return rudder2_valid; }

	void set_rudder1(double t) noexcept;
	void set_rudder2(double t) noexcept;
};
}
}

#endif
