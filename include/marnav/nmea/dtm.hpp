#ifndef MARNAV_NMEA_DTM_HPP
#define MARNAV_NMEA_DTM_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
/// @brief DTM - Datum Reference
///
/// @code
///          1  2  3   4  5   6  7  8    9
///          |  |  |   |  |   |  |  |    |
/// $ --DTM,ref,x,llll,c,llll,c,aaa,ref*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Local datum code.
///    - W84 = WGS84
/// 2. Local datum subcode. May be blank.
/// 3. Latitude offset (minutes)
/// 4. Latitude hemisphere
///    - N = North
///    - S = South
/// 5. Longitude offset (minutes)
/// 6. Longitude hemisphere
///    - E = East
///    - W = West
/// 7. Altitude offset in meters
/// 8. Datum name. What’s usually seen here is "W84", the standard WGS84 datum used by GPS.
///    - W84 = WGS84
///
/// @note Datum code, subcode and datum name are truncated to 5 characters.
///
class dtm : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::DTM;
	constexpr static const char * TAG = "DTM";

	dtm();
	dtm(const dtm &) = default;
	dtm & operator=(const dtm &) = default;
	dtm(dtm &&) = default;
	dtm & operator=(dtm &&) = default;

protected:
	dtm(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::string ref_ = "W84";
	std::optional<std::string> subcode_;
	double lat_offset_ = 0.0;
	direction lat_hem_ = direction::north;
	double lon_offset_ = 0.0;
	direction lon_hem_ = direction::east;
	units::meters altitude_;
	std::string name_ = "W84";

public:
	const std::string & get_ref() const { return ref_; }
	std::optional<std::string> get_subcode() const { return subcode_; }
	double get_lat_offset() const { return lat_offset_; }
	direction get_lat_hem() const { return lat_hem_; }
	double get_lon_offset() const { return lon_offset_; }
	direction get_lon_hem() const { return lon_hem_; }
	units::length get_altitude() const { return {altitude_}; }
	const std::string & get_name() const { return name_; }

	void set_ref(const std::string & t) noexcept;
	void set_subcode(const std::string & t) noexcept;
	void set_lat_offset(double t, direction h);
	void set_lon_offset(double t, direction h);
	void set_altitude(units::length t) { altitude_ = t.get<units::meters>(); }
	void set_name(const std::string & t) noexcept;
};
}
}

#endif
