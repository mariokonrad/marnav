#include "gtd.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * gtd::TAG;

gtd::gtd()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, time_diffs({{0.0, 0.0, 0.0, 0.0, 0.0}})
{
}

gtd::gtd(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in gtd"};

	for (int i = 0; i < max_time_diffs; ++i)
		read(*(first + i), time_diffs[i]);
}

void gtd::check_index(int index) const
{
	if ((index < 0) || (index >= max_time_diffs)) {
		throw std::out_of_range{"time difference index out of range"};
	}
}

double gtd::get_time_diff(int index) const
{
	check_index(index);
	return time_diffs[index];
}

void gtd::set_time_diff(int index, double value)
{
	check_index(index);
	time_diffs[index] = value;
}

std::vector<std::string> gtd::get_data() const
{
	std::vector<std::string> result;
	result.reserve(time_diffs.size());
	for (auto const & t : time_diffs)
		result.push_back(to_string(t));
	return result;
}
}
}
