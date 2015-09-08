#include "alm.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * alm::TAG;

alm::alm()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, number_of_messages(0)
	, message_number(0)
	, satellite_prn(0)
	, gps_week_number(0)
	, sv_health(0)
	, eccentricity(0)
	, almanac_reference_time(0)
	, inclination_angle(0)
	, rate_of_right_ascension(0)
	, root_of_semimajor_axis(0)
	, argument_of_perigee(0)
	, longitude_of_ascension_node(0)
	, mean_anomaly(0)
	, f0_clock_parameter(0)
	, f1_clock_parameter(0)
{
}

void alm::check() const
{
	if ((satellite_prn < 1) || (satellite_prn > 32))
		throw std::invalid_argument{"invalid satellite PRN"};
}

std::unique_ptr<sentence> alm::parse(
	const std::string & talker, const std::vector<std::string> & fields)
{
	if (fields.size() != 15)
		throw std::invalid_argument{"invalid number of fields in alm::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<alm>();
	result->set_talker(talker);
	alm & detail = static_cast<alm &>(*result);

	read(fields[0], detail.number_of_messages);
	read(fields[1], detail.message_number);
	read(fields[2], detail.satellite_prn);
	read(fields[3], detail.gps_week_number);
	read(fields[4], detail.sv_health);
	read(fields[5], detail.eccentricity, data_format::hex);
	read(fields[6], detail.almanac_reference_time, data_format::hex);
	read(fields[7], detail.inclination_angle, data_format::hex);
	read(fields[8], detail.rate_of_right_ascension, data_format::hex);
	read(fields[9], detail.root_of_semimajor_axis, data_format::hex);
	read(fields[10], detail.argument_of_perigee, data_format::hex);
	read(fields[11], detail.longitude_of_ascension_node, data_format::hex);
	read(fields[12], detail.mean_anomaly, data_format::hex);
	read(fields[13], detail.f0_clock_parameter, data_format::hex);
	read(fields[14], detail.f1_clock_parameter, data_format::hex);

	detail.check();

	return result;
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
