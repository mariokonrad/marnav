#ifndef __NMEA__RSA__HPP__
#define __NMEA__RSA__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief RSA - Rudder Sensor Angle
///
/// @code
///        1   2 3   4 5
///        |   | |   | |
/// $--RSA,x.x,A,x.x,A*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
/// 1. Starboard (or single) rudder sensor, "-" means Turn To Port
/// 2. Status, A means data is valid
/// 3. Port rudder sensor
/// 4. Status, A means data is valid
/// 5. Checksum
///
class rsa : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::RSA;

	rsa();
	rsa(const rsa &) = default;
	rsa & operator=(const rsa &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> rudder1;
	utils::optional<char> status1;
	utils::optional<double> rudder2;
	utils::optional<char> status2;

public:
	decltype(rudder1) get_rudder1() const { return rudder1; }
	decltype(status1) get_status1() const { return status1; }
	decltype(rudder2) get_rudder2() const { return rudder2; }
	decltype(status2) get_status2() const { return status2; }

	void set_rudder1(double t);
	void set_rudder2(double t);
};
}
}

#endif
