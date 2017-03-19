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

alm::alm(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
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

void alm::append_data_to(std::string & s) const
{
	append(s, to_string(number_of_messages));
	append(s, to_string(message_number));
	append(s, format(satellite_prn, 2));
	append(s, to_string(gps_week_number));
	append(s, format(sv_health, 2));
	append(s, format(eccentricity, 1, data_format::hex));
	append(s, format(almanac_reference_time, 1, data_format::hex));
	append(s, format(inclination_angle, 1, data_format::hex));
	append(s, format(rate_of_right_ascension, 1, data_format::hex));
	append(s, format(root_of_semimajor_axis, 1, data_format::hex));
	append(s, format(argument_of_perigee, 1, data_format::hex));
	append(s, format(longitude_of_ascension_node, 1, data_format::hex));
	append(s, format(mean_anomaly, 1, data_format::hex));
	append(s, format(f0_clock_parameter, 1, data_format::hex));
	append(s, format(f1_clock_parameter, 1, data_format::hex));
}
}
}
