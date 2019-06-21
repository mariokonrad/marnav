#include <marnav/nmea/gtd.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id gtd::ID;
constexpr const char * gtd::TAG;

constexpr int gtd::max_time_diffs;

gtd::gtd()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, time_diffs_({{0.0, 0.0, 0.0, 0.0, 0.0}})
{
}

gtd::gtd(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in gtd"};

	for (int i = 0; i < max_time_diffs; ++i)
		read(*(first + i), time_diffs_[i]);
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
	return time_diffs_[index];
}

void gtd::set_time_diff(int index, double value)
{
	check_index(index);
	time_diffs_[index] = value;
}

void gtd::append_data_to(std::string & s) const
{
	for (auto const & t : time_diffs_)
		append(s, to_string(t));
}
}
}
