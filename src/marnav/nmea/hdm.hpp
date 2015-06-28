#ifndef __NMEA__HDM__HPP__
#define __NMEA__HDM__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief HDM - Heading - Magnetic
///
/// Vessel heading in degrees with respect to magnetic north produced by any device
/// or system producing magnetic heading.
///
/// @note As of 2009, this sentence is designaged 'obsolete'. Older devices may
///   support them, therefore it makes sense to implement it.
///
/// @code
///        1   2 3
///        |   | |
/// $--HDM,x.x,M*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
/// 1. Heading Degrees, magnetic
/// 2. M = magnetic
/// 3. Checksum
///
class hdm : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::HDM;

	hdm();
	hdm(const hdm &) = default;
	hdm & operator=(const hdm &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> heading; // magnetic sensor heading in deg
	utils::optional<char> heading_mag;

public:
	decltype(heading) get_heading() const { return heading; }
	decltype(heading_mag) get_magn_dev() const { return heading_mag; }

	void set_heading(double t);
};
}
}

#endif
