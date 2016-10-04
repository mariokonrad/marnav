#ifndef __NMEA__PGRMM__HPP__
#define __NMEA__PGRMM__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(pgrmm)

/// @brief PGRMM - Garmin Map Datum
///
/// @code
///        1
///        |
/// $PGRMM,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
///
/// 1. Map datum, variable length
///
/// Example: <tt>$PGRMM,WGS 84*06</tt>
///
class pgrmm : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(pgrmm)

public:
	constexpr static const sentence_id ID = sentence_id::PGRMM;
	constexpr static const char * TAG = "PGRMM";

	pgrmm();
	pgrmm(const pgrmm &) = default;
	pgrmm & operator=(const pgrmm &) = default;
	pgrmm(pgrmm &&) = default;
	pgrmm & operator=(pgrmm &&) = default;

protected:
	pgrmm(
		const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	std::string map_datum;

public:
	MARNAV_NMEA_GETTER(map_datum)

	void set_map_datum(const std::string & t) noexcept;
};
}
}

#endif
