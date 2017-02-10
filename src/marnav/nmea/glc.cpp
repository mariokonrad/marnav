#include "glc.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr const char * glc::TAG;

glc::glc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, master({0, nmea::status::warning})
{
}

glc::glc(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 13)
		throw std::invalid_argument{"invalid number of fields in glc"};

	read(*(first + 0), gri);
	read(*(first + 1), master.diff);
	read(*(first + 2), master.status);
	for (int i = 0; i < max_differences; ++i) {
		utils::optional<double> diff;
		utils::optional<nmea::status> status;
		read(*(first + (i * 2) + 3 + 0), diff);
		read(*(first + (i * 2) + 3 + 1), status);
		if (diff && status) {
			time_diffs[i] = utils::make_optional<time_difference>(*diff, *status);
		}
	}
}

void glc::check_index(int index) const
{
	if ((index < 0) || (index >= max_differences)) {
		throw std::out_of_range{"time difference index out of range"};
	}
}

utils::optional<glc::time_difference> glc::get_time_diff(int index) const
{
	check_index(index);
	return time_diffs[index];
}

void glc::set_time_diff(int index, time_difference t)
{
	check_index(index);
	time_diffs[index] = t;
}

std::vector<std::string> glc::get_data() const
{
	std::vector<std::string> result;
	result.reserve(13);
	result.push_back(to_string(gri));
	result.push_back(to_string(master.diff));
	result.push_back(to_string(master.status));
	for (int i = 0; i < max_differences; ++i) {
		auto const & t = time_diffs[i];
		if (t) {
			result.push_back(to_string(t->diff));
			result.push_back(to_string(t->status));
		} else {
			result.push_back("");
			result.push_back("");
		}
	}
	return result;
}
}
}
