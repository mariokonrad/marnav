#include "alm.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * alm::TAG;

alm::alm()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

alm::alm(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	if (std::distance(first, last) != 15)
		throw std::invalid_argument{"invalid number of fields in alm"};

	read(*(first + 0), number_of_messages);
	read(*(first + 1), message_number);
	read(*(first + 2), satellite_prn);
	read(*(first + 3), gps_week_number);
	read(*(first + 4), sv_health);
	read(*(first + 5), eccentricity, data_format::hex);
	read(*(first + 6), almanac_reference_time, data_format::hex);
	read(*(first + 7), inclination_angle, data_format::hex);
	read(*(first + 8), rate_of_right_ascension, data_format::hex);
	read(*(first + 9), root_of_semimajor_axis, data_format::hex);
	read(*(first + 10), argument_of_perigee, data_format::hex);
	read(*(first + 11), longitude_of_ascension_node, data_format::hex);
	read(*(first + 12), mean_anomaly, data_format::hex);
	read(*(first + 13), f0_clock_parameter, data_format::hex);
	read(*(first + 14), f1_clock_parameter, data_format::hex);

	check();
}

void alm::check() const
{
	if ((satellite_prn < 1) || (satellite_prn > 32))
		throw std::invalid_argument{"invalid satellite PRN"};
}

std::unique_ptr<sentence> alm::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	return std::unique_ptr<alm>(new alm(talker, first, last));
}

std::vector<std::string> alm::get_data() const
{
	return {to_string(number_of_messages), to_string(message_number), format(satellite_prn, 2),
		to_string(gps_week_number), format(sv_health, 2),
		format(eccentricity, 1, data_format::hex),
		format(almanac_reference_time, 1, data_format::hex),
		format(inclination_angle, 1, data_format::hex),
		format(rate_of_right_ascension, 1, data_format::hex),
		format(root_of_semimajor_axis, 1, data_format::hex),
		format(argument_of_perigee, 1, data_format::hex),
		format(longitude_of_ascension_node, 1, data_format::hex),
		format(mean_anomaly, 1, data_format::hex),
		format(f0_clock_parameter, 1, data_format::hex),
		format(f1_clock_parameter, 1, data_format::hex)};
}
}
}
