#include "gtd.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

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

void gtd::check_index(int index) const
{
	if ((index < 0) || (index >= NUM_DATA)) {
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

std::unique_ptr<sentence> gtd::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	if (fields.size() != 5)
		throw std::invalid_argument{"invalid number of fields in gtd::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<gtd>();
	result->set_talker(talker);
	gtd & detail = static_cast<gtd &>(*result);

	for (int i = 0; i < NUM_DATA; ++i)
		read(fields[i], detail.time_diffs[i]);

	return result;
}

std::vector<std::string> gtd::get_data() const
{
	std::vector<std::string> result;
	result.reserve(NUM_DATA);
	for (auto const & t : time_diffs)
		result.push_back(to_string(t));
	return result;
}
}
}
