#ifndef MARNAV__NMEA__GTD__HPP
#define MARNAV__NMEA__GTD__HPP

#include <array>
#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
/// @brief GTD - Geographic Location in Time Differences
///
/// @code
///        1   2   3   4   5
///        |   |   |   |   |
/// $--GTD,x.x,x.x,x.x,x.x,x.x*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. time difference
/// 2. time difference
/// 3. time difference
/// 4. time difference
/// 5. time difference
///
class gtd : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::GTD;
	constexpr static const char * TAG = "GTD";

	constexpr static int max_time_diffs = 5;

	gtd();
	gtd(const gtd &) = default;
	gtd & operator=(const gtd &) = default;
	gtd(gtd &&) = default;
	gtd & operator=(gtd &&) = default;

protected:
	gtd(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	std::array<double, max_time_diffs> time_diffs_;

	void check_index(int index) const;

public:
	double get_time_diff(int index) const;

	void set_time_diff(int index, double value);
};
}
}

#endif
