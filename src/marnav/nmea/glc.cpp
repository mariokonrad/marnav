#include <marnav/nmea/glc.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id glc::ID;
constexpr const char * glc::TAG;

glc::glc()
	: sentence(ID, TAG, talker::global_positioning_system)
	, master_({0, nmea::status::warning})
{
}

glc::glc(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 13)
		throw std::invalid_argument{"invalid number of fields in glc"};

	read(*(first + 0), gri_);
	read(*(first + 1), master_.diff);
	read(*(first + 2), master_.status);
	for (int i = 0; i < max_differences; ++i) {
		utils::optional<double> diff;
		utils::optional<nmea::status> status;
		read(*(first + (i * 2) + 3 + 0), diff);
		read(*(first + (i * 2) + 3 + 1), status);
		if (diff && status) {
			time_diffs_[i] = utils::make_optional<time_difference>(*diff, *status);
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
	return time_diffs_[index];
}

void glc::set_time_diff(int index, time_difference t)
{
	check_index(index);
	time_diffs_[index] = t;
}

void glc::append_data_to(std::string & s) const
{
	append(s, to_string(gri_));
	append(s, to_string(master_.diff));
	append(s, to_string(master_.status));
	for (int i = 0; i < max_differences; ++i) {
		auto const & t = time_diffs_[i];
		if (t) {
			append(s, to_string(t->diff));
			append(s, to_string(t->status));
		} else {
			append(s, "");
			append(s, "");
		}
	}
}
}
}
