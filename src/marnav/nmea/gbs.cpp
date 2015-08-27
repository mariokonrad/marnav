#include "gbs.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

namespace marnav
{
namespace nmea
{

constexpr const char * gbs::TAG;

gbs::gbs()
	: sentence(ID, TAG, talker_id::global_positioning_system)
	, err_lat(0.0)
	, err_lon(0.0)
	, err_alt(0.0)
	, satellite(0)
	, probability(0.0)
	, bias(0.0)
	, bias_dev(0.0)
{
}

std::unique_ptr<sentence> gbs::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument, std::runtime_error)
{
	if (fields.size() != 8)
		throw std::invalid_argument{"invalid number of fields in gbs::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<gbs>();
	result->set_talker(talker);
	gbs & detail = static_cast<gbs &>(*result);

	read(fields[0], detail.time_utc);
	read(fields[1], detail.err_lat);
	read(fields[2], detail.err_lon);
	read(fields[3], detail.err_alt);
	read(fields[4], detail.satellite);
	read(fields[5], detail.probability);
	read(fields[6], detail.bias);
	read(fields[7], detail.bias_dev);

	return result;
}

std::vector<std::string> gbs::get_data() const
{
	return {format(time_utc, 2), to_string(err_lat), to_string(err_lon), to_string(err_alt),
		format(satellite, 3), to_string(probability), to_string(bias), to_string(bias_dev)};
}
}
}
