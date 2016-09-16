#ifndef __NMEA__RSA__HPP__
#define __NMEA__RSA__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(rsa)

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
	MARNAV_NMEA_SENTENCE_FRIENDS(rsa)

public:
	constexpr static const sentence_id ID = sentence_id::RSA;
	constexpr static const char * TAG = "RSA";

	virtual ~rsa() {}

	rsa();
	rsa(const rsa &) = default;
	rsa & operator=(const rsa &) = default;

protected:
	rsa(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> rudder1;
	utils::optional<status> rudder1_valid;
	utils::optional<double> rudder2;
	utils::optional<status> rudder2_valid;

public:
	MARNAV_NMEA_GETTER(rudder1)
	MARNAV_NMEA_GETTER(rudder1_valid)
	MARNAV_NMEA_GETTER(rudder2)
	MARNAV_NMEA_GETTER(rudder2_valid)

	void set_rudder1(double t) noexcept;
	void set_rudder2(double t) noexcept;
};
}
}

#endif
