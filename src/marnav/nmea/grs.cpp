#include "grs.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>

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

constexpr sentence_id grs::ID;
constexpr const char * grs::TAG;

constexpr int grs::num_satellite_residuals;

grs::grs()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, usage_(grs::residual_usage::used_in_gga)
{
	// first three residuals are not optional
	sat_residual_[0] = 0.0;
	sat_residual_[1] = 0.0;
	sat_residual_[2] = 0.0;
}

grs::grs(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 14)
		throw std::invalid_argument{"invalid number of fields in grs"};

	read(*(first + 0), time_utc_);
	read(*(first + 1), usage_, residual_usage_mapping);
	for (size_t i = 0; i < sat_residual_.size(); ++i)
		read(*(first + i + 2), sat_residual_[i]);
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
	return sat_residual_[index];
}

void grs::set_sat_residual(int index, double value)
{
	check_index(index);
	sat_residual_[index] = value;
}

void grs::append_data_to(std::string & s) const
{
	append(s, format(time_utc_, 2));
	append(s, to_string(usage_));
	for (auto const & t : sat_residual_)
		append(s, to_string(t));
}
}
}
