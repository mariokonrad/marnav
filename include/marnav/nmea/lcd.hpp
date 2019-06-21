#ifndef MARNAV__NMEA__LCD__HPP
#define MARNAV__NMEA__LCD__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
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
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::LCD;
	constexpr static const char * TAG = "LCD";

	constexpr static int max_differences = 5;

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
	lcd(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	uint32_t gri_ = 0; ///< unit: 0.1 microseconds
	time_difference master_;
	std::array<utils::optional<time_difference>, max_differences> time_diffs_;

	void check_index(int index) const;

public:
	decltype(gri_) get_gri() const { return gri_; }
	decltype(master_) get_master() const { return master_; }
	utils::optional<time_difference> get_time_diff(int index) const;

	void set_gri(uint32_t t) noexcept { gri_ = t; }
	void set_master(const time_difference & t) noexcept { master_ = t; }
	void set_time_diff(int index, time_difference t);
};
}
}

#endif
