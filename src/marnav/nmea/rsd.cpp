#include "rsd.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * rsd::TAG;

rsd::rsd()
	: sentence(ID, TAG, talker_id::integrated_instrumentation)
	, unknowns({{0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0}})
	, cursor_range(0.0)
	, cursor_bearing(0.0)
	, range_scale(0.0)
	, range_unit('V')
	, unknown('V')
{
}

void rsd::set_cursor(double range, double bearing) noexcept
{
	cursor_range = range;
	cursor_bearing = bearing;
}

void rsd::set_range(double scale, char unit) noexcept
{
	range_scale = scale;
	range_unit = unit;
}

std::unique_ptr<sentence> rsd::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	if (fields.size() != 13)
		throw std::invalid_argument{"invalid number of fields in rsd::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<rsd>();
	result->set_talker(talker);
	rsd & detail = static_cast<rsd &>(*result);

	for (decltype(detail.unknowns.size()) i = 0; i < detail.unknowns.size(); ++i)
		read(fields[i], detail.unknowns[i]);
	read(fields[8], detail.cursor_range);
	read(fields[9], detail.cursor_bearing);
	read(fields[10], detail.range_scale);
	read(fields[11], detail.range_unit);
	read(fields[12], detail.unknown);

	return result;
}

std::vector<std::string> rsd::get_data() const
{
	std::vector<std::string> result;
	result.reserve(13);
	for (auto const & t : unknowns)
		result.push_back(to_string(t));
	result.push_back(to_string(cursor_range));
	result.push_back(to_string(cursor_bearing));
	result.push_back(to_string(range_scale));
	result.push_back(to_string(range_unit));
	result.push_back(to_string(unknown));
	return result;
}
}
}
