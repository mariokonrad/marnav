#ifndef __NMEA__DBK__HPP__
#define __NMEA__DBK__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(dbk)

/// @brief DBK - Depth Below Keel
///
/// @note This sentence appears to be deprected, use @ref marnav::nmea::dpt "DPT" instead.
///
/// @code
///        1   2 3   4 5   6
///        |   | |   | |   |
/// $--DBK,x.x,f,x.x,M,x.x,F*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Depth feet
/// 2. Depth feet unit
///    - f = feet
/// 3. Depth meters
/// 4. Depth meters unit
///    - M = meters
/// 5. Depth Fathoms
/// 6. Depth Fathoms
///    - F = Fathoms
///
class dbk : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(dbk)

public:
	constexpr static const sentence_id ID = sentence_id::DBK;
	constexpr static const char * TAG = "DBK";

	virtual ~dbk() {}

	dbk();
	dbk(const dbk &) = default;
	dbk & operator=(const dbk &) = default;

protected:
	dbk(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> depth_feet;
	utils::optional<unit::distance> depth_feet_unit;
	utils::optional<double> depth_meter;
	utils::optional<unit::distance> depth_meter_unit;
	utils::optional<double> depth_fathom;
	utils::optional<unit::distance> depth_fathom_unit;

public:
	MARNAV_NMEA_GETTER(depth_feet)
	MARNAV_NMEA_GETTER(depth_feet_unit)
	MARNAV_NMEA_GETTER(depth_meter)
	MARNAV_NMEA_GETTER(depth_meter_unit)
	MARNAV_NMEA_GETTER(depth_fathom)
	MARNAV_NMEA_GETTER(depth_fathom_unit)

	void set_depth_feet(double t) noexcept;
	void set_depth_meter(double t) noexcept;
	void set_depth_fathom(double t) noexcept;
};
}
}

#endif
