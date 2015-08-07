#include "dtm.hpp"
#include <marnav/nmea/checks.hpp>
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * dtm::TAG;

dtm::dtm()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, ref("W84")
	, lat_offset(0)
	, lat_hem('N')
	, lon_offset(0)
	, lon_hem('E')
	, altitude(0)
	, name("W84")
{
}

std::unique_ptr<sentence> dtm::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument)
{
	if (fields.size() != 8)
		throw std::invalid_argument{"invalid number of fields in dtm::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<dtm>();
	result->set_talker(talker);
	dtm & detail = static_cast<dtm &>(*result);

	read(fields[0], detail.ref);
	read(fields[1], detail.subcode);
	read(fields[2], detail.lat_offset);
	read(fields[3], detail.lat_hem);
	read(fields[4], detail.lon_offset);
	read(fields[5], detail.lon_hem);
	read(fields[6], detail.altitude);
	read(fields[7], detail.name);

	return result;
}

std::vector<std::string> dtm::get_data() const
{
	return {to_string(ref), to_string(subcode), format(lat_offset, 4), to_string(lat_hem),
		format(lon_offset, 4), to_string(lon_hem), format(altitude, 1), to_string(name)};
}
}
}
