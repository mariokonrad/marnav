#ifndef __NMEA__HSC__HPP__
#define __NMEA__HSC__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief HSC - Heading Steering Command
///
/// @code
///        1   2 3   4
///        |   | |   |
/// $--HSC,x.x,T,x.x,M*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Heading Degrees True
/// 2. Heading Degrees True reference
///    - T = True
/// 3. Heading Degrees Magnetic
/// 4. Heading Degrees Magnetic reference
///    - M = Magnetic
///
class hsc : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::HSC;
	constexpr static const char * TAG = "HSC";

	hsc();
	hsc(const hsc &) = default;
	hsc & operator=(const hsc &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> heading_true;
	utils::optional<char> heading_true_ref;
	utils::optional<double> heading_mag;
	utils::optional<char> heading_mag_ref;

public:
	decltype(heading_true) get_heading_true() const { return heading_true; }
	decltype(heading_true_ref) get_heading_true_ref() const { return heading_true_ref; }
	decltype(heading_mag) get_heading_mag() const { return heading_mag; }
	decltype(heading_mag_ref) get_heading_mag_ref() const { return heading_mag_ref; }

	void set_heading_true(double t);
	void set_heading_mag(double t);
};
}
}

#endif
