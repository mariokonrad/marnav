#ifndef MARNAV__NMEA__DTM__HPP
#define MARNAV__NMEA__DTM__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

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
	virtual void append_data_to(std::string &) const override;

private:
	std::string ref_ = "W84";
	utils::optional<std::string> subcode_;
	double lat_offset_ = 0.0;
	direction lat_hem_ = direction::north;
	double lon_offset_ = 0.0;
	direction lon_hem_ = direction::east;
	double altitude_ = 0.0;
	std::string name_ = "W84";

public:
	decltype(ref_) get_ref() const { return ref_; }
	decltype(subcode_) get_subcode() const { return subcode_; }
	decltype(lat_offset_) get_lat_offset() const { return lat_offset_; }
	decltype(lat_hem_) get_lat_hem() const { return lat_hem_; }
	decltype(lon_offset_) get_lon_offset() const { return lon_offset_; }
	decltype(lon_hem_) get_lon_hem() const { return lon_hem_; }
	decltype(altitude_) get_altitude() const { return altitude_; }
	decltype(name_) get_name() const { return name_; }

	void set_ref(const std::string & t) noexcept;
	void set_subcode(const std::string & t) noexcept;
	void set_lat_offset(double t, direction h);
	void set_lon_offset(double t, direction h);
	void set_altitude(double t) { altitude_ = t; }
	void set_name(const std::string & t) noexcept;
};
}
}

#endif
