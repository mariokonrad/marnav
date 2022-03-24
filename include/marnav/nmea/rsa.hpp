#ifndef MARNAV_NMEA_RSA_HPP
#define MARNAV_NMEA_RSA_HPP

#include <marnav/nmea/sentence.hpp>
#include <optional>

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
	constexpr static sentence_id ID = sentence_id::RSA;
	constexpr static const char * TAG = "RSA";

	rsa();
	rsa(const rsa &) = default;
	rsa & operator=(const rsa &) = default;
	rsa(rsa &&) = default;
	rsa & operator=(rsa &&) = default;

protected:
	rsa(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<double> rudder1_;
	std::optional<status> rudder1_valid_;
	std::optional<double> rudder2_;
	std::optional<status> rudder2_valid_;

public:
	std::optional<double> get_rudder1() const { return rudder1_; }
	std::optional<status> get_rudder1_valid() const { return rudder1_valid_; }
	std::optional<double> get_rudder2() const { return rudder2_; }
	std::optional<status> get_rudder2_valid() const { return rudder2_valid_; }

	void set_rudder1(double t) noexcept;
	void set_rudder2(double t) noexcept;
};
}
}

#endif
