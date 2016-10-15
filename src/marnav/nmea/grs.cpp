#include "grs.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(grs)

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
	typename std::underlying_type<grs::residual_usage>::type value)
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

std::string to_string(grs::residual_usage value)
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

grs::grs(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 14)
		throw std::invalid_argument{"invalid number of fields in grs"};

	read(*(first + 0), time_utc);
	read(*(first + 1), usage, residual_usage_mapping);
	for (size_t i = 0; i < sat_residual.size(); ++i)
		read(*(first + i + 2), sat_residual[i]);
}

void grs::check_index(int index) const
{
	if ((index < 0) || (index >= num_satellite_residuals)) {
		throw std::out_of_range{"satellite index out of range"};
	}
}

utils::optional<double> grs::get_sat_residual(int index) const
{
	check_index(index);
	return sat_residual[index];
}

void grs::set_sat_residual(int index, double value)
{
	check_index(index);
	sat_residual[index] = value;
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
