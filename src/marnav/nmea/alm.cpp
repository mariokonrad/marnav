#include <marnav/nmea/alm.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id alm::ID;
constexpr const char * alm::TAG;

alm::alm()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

alm::alm(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 15)
		throw std::invalid_argument{"invalid number of fields in alm"};

	read(*(first + 0), number_of_messages_);
	read(*(first + 1), message_number_);
	read(*(first + 2), satellite_prn_);
	read(*(first + 3), gps_week_number_);
	read(*(first + 4), sv_health_);
	read(*(first + 5), eccentricity_, data_format::hex);
	read(*(first + 6), almanac_reference_time_, data_format::hex);
	read(*(first + 7), inclination_angle_, data_format::hex);
	read(*(first + 8), rate_of_right_ascension_, data_format::hex);
	read(*(first + 9), root_of_semimajor_axis_, data_format::hex);
	read(*(first + 10), argument_of_perigee_, data_format::hex);
	read(*(first + 11), longitude_of_ascension_node_, data_format::hex);
	read(*(first + 12), mean_anomaly_, data_format::hex);
	read(*(first + 13), f0_clock_parameter_, data_format::hex);
	read(*(first + 14), f1_clock_parameter_, data_format::hex);

	check();
}

void alm::check() const
{
	if ((satellite_prn_ < 1) || (satellite_prn_ > 32))
		throw std::invalid_argument{"invalid satellite PRN"};
}

void alm::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(number_of_messages_));
	append(s, to_string(message_number_));
	append(s, format(satellite_prn_, 2));
	append(s, to_string(gps_week_number_));
	append(s, format(sv_health_, 2));
	append(s, format(eccentricity_, 1, data_format::hex));
	append(s, format(almanac_reference_time_, 1, data_format::hex));
	append(s, format(inclination_angle_, 1, data_format::hex));
	append(s, format(rate_of_right_ascension_, 1, data_format::hex));
	append(s, format(root_of_semimajor_axis_, 1, data_format::hex));
	append(s, format(argument_of_perigee_, 1, data_format::hex));
	append(s, format(longitude_of_ascension_node_, 1, data_format::hex));
	append(s, format(mean_anomaly_, 1, data_format::hex));
	append(s, format(f0_clock_parameter_, 1, data_format::hex));
	append(s, format(f1_clock_parameter_, 1, data_format::hex));
}
}
}
