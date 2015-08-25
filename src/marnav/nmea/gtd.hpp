#ifndef __NMEA__GTD__HPP__
#define __NMEA__GTD__HPP__

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
public:
	constexpr static const sentence_id ID = sentence_id::GTD;
	constexpr static const char * TAG = "GTD";

	gtd();
	gtd(const gtd &) = default;
	gtd & operator=(const gtd &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument,
		std::runtime_error);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	constexpr static const int NUM_DATA = 5;

	std::array<double, NUM_DATA> time_diffs;

	void check_index(int index) const throw(std::out_of_range);

public:
	double get_time_diff(int index) const throw(std::out_of_range);

	void set_time_diff(int index, double value) throw(std::out_of_range);
};
}
}

#endif
