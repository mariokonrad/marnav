#include "grs.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

namespace
{
/// Converts data read from the NMEA string to the corresponding
/// enumerator.
///
/// @param[in] value The numerical value to convert.
/// @return The corresponding enumerator.
/// @exception std::invalid_argument The specified value to convert is unknown.
///
static grs::residual_usage residual_usage_mapping(
	typename std::underlying_type<grs::residual_usage>::type value) throw(std::invalid_argument)
{
	switch (value) {
		case 0:
			return grs::residual_usage::used_in_gga;
		case 1:
			return grs::residual_usage::calculated_after_gga;
	}
	throw std::invalid_argument{"invaild value for conversion to grs::residual_usage"};
}
}

std::string to_string(grs::residual_usage value) throw(std::invalid_argument)
{
	switch (value) {
		case grs::residual_usage::used_in_gga:
			return "0";
		case grs::residual_usage::calculated_after_gga:
			return "1";
	}
	throw std::invalid_argument{"invaild value for conversion of grs::residual_usage"};
}

constexpr const char * grs::TAG;

grs::grs()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, usage(grs::residual_usage::used_in_gga)
{
	// first three residuals are not optional
	sat_residual[0] = 0.0;
	sat_residual[1] = 0.0;
	sat_residual[2] = 0.0;
}

void grs::check_index(int index) const throw(std::out_of_range)
{
	if ((index < 1) || (index > 12)) {
		throw std::out_of_range{"satellite id out of range"};
	}
}

utils::optional<double> grs::get_sat_residual(int index) const throw(std::out_of_range)
{
	check_index(index);
	return sat_residual[index];
}

void grs::set_sat_residual(int index, double value) throw(std::out_of_range)
{
	check_index(index);
	sat_residual[index] = value;
}

std::unique_ptr<sentence> grs::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument, std::runtime_error)
{
	if (fields.size() != 14)
		throw std::invalid_argument{"invalid number of fields in grs::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<grs>();
	result->set_talker(talker);
	grs & detail = static_cast<grs &>(*result);

	read(fields[0], detail.time_utc);
	read(fields[1], detail.usage, residual_usage_mapping);
	for (size_t i = 0; i < detail.sat_residual.size(); ++i)
		read(fields[i + 2], detail.sat_residual[i]);

	return result;
}

std::vector<std::string> grs::get_data() const
{
	std::vector<std::string> result;
	result.reserve(14);
	result.push_back(format(time_utc, 2));
	result.push_back(to_string(usage));
	for (auto const & t : sat_residual)
		result.push_back(to_string(t));
	return result;
}
}
}
