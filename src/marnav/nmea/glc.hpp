#ifndef MARNAV__NMEA__GLC__HPP
#define MARNAV__NMEA__GLC__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(glc)

/// @brief GLC - Geographic Position, Loran-C
///
/// @code
///                                           12
///        1    2   3 4   5 6   7 8   9 10  11|   13
///        |    |   | |   | |   | |   | |   | |   |
/// $--GLC,xxxx,x.x,a,x.x,a,x.x,a.x,x,a,x.x,a,x.x,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  GRI Microseconds/10
/// 2.  Master TOA Microseconds
/// 3.  Master TOA Signal Status
/// 4.  Time Difference 1 Microseconds
/// 5.  Time Difference 1 Signal Status
/// 6.  Time Difference 2 Microseconds
/// 7.  Time Difference 2 Signal Status
/// 8.  Time Difference 3 Microseconds
/// 9.  Time Difference 3 Signal Status
/// 10. Time Difference 4 Microseconds
/// 11. Time Difference 4 Signal Status
/// 12. Time Difference 5 Microseconds
/// 13. Time Difference 5 Signal Status
///
class glc : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(glc)

public:
	constexpr static const sentence_id ID = sentence_id::GLC;
	constexpr static const char * TAG = "GLC";

	static constexpr const int max_differences = 5;

	struct time_difference {
		double diff;
		nmea::status status;
	};

	glc();
	glc(const glc &) = default;
	glc & operator=(const glc &) = default;
	glc(glc &&) = default;
	glc & operator=(glc &&) = default;

protected:
	glc(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	uint32_t gri = 0; ///< unit: 0.1 microseconds
	time_difference master;
	std::array<utils::optional<time_difference>, max_differences> time_diffs;

	void check_index(int index) const;

public:
	decltype(gri) get_gri() const { return gri; }
	decltype(master) get_master() const { return master; }
	utils::optional<time_difference> get_time_diff(int index) const;

	void set_gri(uint32_t t) noexcept { gri = t; }
	void set_master(time_difference t) noexcept { master = t; }
	void set_time_diff(int index, time_difference t);
};
}
}

#endif
