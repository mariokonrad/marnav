#ifndef MARNAV_NMEA_TEP_HPP
#define MARNAV_NMEA_TEP_HPP

#include <marnav/nmea/sentence.hpp>

namespace marnav
{
namespace nmea
{
/// @brief TEP - Transit Satellite Predicted Elevation
///
/// @code
///        1   2
///        |   |
/// $--TEP,x.x,D*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Elevation in Degrees
/// 2. Elevation unit
///    - D = Degrees
///
class tep : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::TEP;
	constexpr static const char * TAG = "TEP";

	tep();
	tep(const tep &) = default;
	tep & operator=(const tep &) = default;
	tep(tep &&) = default;
	tep & operator=(tep &&) = default;

protected:
	tep(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	double elevation_ = 0.0;

public:
	double get_elevation() const { return elevation_; }

	void set_elevation(double t) { elevation_ = t; }
};
}
}

#endif
