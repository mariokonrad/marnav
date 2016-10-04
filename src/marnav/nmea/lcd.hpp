#ifndef __NMEA__LCD__HPP__
#define __NMEA__LCD__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(lcd)

/// @brief LCD - Loran-C Signal Data
///
/// @code
///
///        1    2   3   4   5   6   7   8   9   10  11  12  13
///        |    |   |   |   |   |   |   |   |   |   |   |   |
/// $--LCD,xxxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx,xxx*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  GRI Microseconds/10
/// 2.  Master Relative SNR
/// 3.  Master Relative ECD
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
class lcd : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(lcd)

public:
	constexpr static const sentence_id ID = sentence_id::LCD;
	constexpr static const char * TAG = "LCD";

	static constexpr const int max_differences = 5;

	struct time_difference {
		int32_t snr;
		int32_t ecd;
	};

	lcd();
	lcd(const lcd &) = default;
	lcd & operator=(const lcd &) = default;
	lcd(lcd &&) = default;
	lcd & operator=(lcd &&) = default;

protected:
	lcd(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	uint32_t gri = 0; ///< unit: 0.1 microseconds
	time_difference master;
	std::array<utils::optional<time_difference>, max_differences> time_diffs;

	void check_index(int index) const;

public:
	MARNAV_NMEA_GETTER(gri)
	MARNAV_NMEA_GETTER(master)
	utils::optional<time_difference> get_time_diff(int index) const;

	void set_gri(uint32_t t) noexcept { gri = t; }
	void set_master(const time_difference & t) noexcept { master = t; }
	void set_time_diff(int index, time_difference t);
};
}
}

#endif
