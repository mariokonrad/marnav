#include "glc.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * glc::TAG;

glc::glc()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, gri(0)
	, master({0, nmea::status::WARNING})
{
}

void glc::check_index(int index) const throw(std::out_of_range)
{
	if ((index < 0) || (index >= NUM_DIFFERENCES)) {
		throw std::out_of_range{"time difference index out of range"};
	}
}

utils::optional<glc::time_difference> glc::get_time_diff(int index) const
	throw(std::out_of_range)
{
	check_index(index);
	return time_diffs[index];
}

void glc::set_time_diff(int index, time_difference t) throw(std::out_of_range)
{
	check_index(index);
	time_diffs[index] = t;
}

std::unique_ptr<sentence> glc::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument, std::runtime_error)
{
	if (fields.size() != 13)
		throw std::invalid_argument{"invalid number of fields in glc::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<glc>();
	result->set_talker(talker);
	glc & detail = static_cast<glc &>(*result);

	read(fields[0], detail.gri);
	read(fields[1], detail.master.diff);
	read(fields[2], detail.master.status);
	for (int i = 0; i < NUM_DIFFERENCES; ++i) {
		utils::optional<double> diff;
		utils::optional<nmea::status> status;
		read(fields[(i * 2) + 3], diff);
		read(fields[(i * 2) + 3 + 1], status);
		if (diff && status) {
			detail.time_diffs[i] = utils::make_optional<time_difference>(*diff, *status);
		}
	}

	return result;
}

std::vector<std::string> glc::get_data() const
{
	std::vector<std::string> result;
	result.reserve(13);
	result.push_back(to_string(gri));
	result.push_back(to_string(master.diff));
	result.push_back(to_string(master.status));
	for (int i = 0; i < NUM_DIFFERENCES; ++i) {
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
