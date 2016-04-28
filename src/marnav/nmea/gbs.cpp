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

std::unique_ptr<sentence> gbs::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	if (std::distance(first, last) != 8)
		throw std::invalid_argument{"invalid number of fields in gbs::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<gbs>();
	result->set_talker(talker);
	gbs & detail = static_cast<gbs &>(*result);

	read(*(first + 0), detail.time_utc);
	read(*(first + 1), detail.err_lat);
	read(*(first + 2), detail.err_lon);
	read(*(first + 3), detail.err_alt);
	read(*(first + 4), detail.satellite);
	read(*(first + 5), detail.probability);
	read(*(first + 6), detail.bias);
	read(*(first + 7), detail.bias_dev);

	return result;
}

std::vector<std::string> gbs::get_data() const
{
	return {format(time_utc, 2), to_string(err_lat), to_string(err_lon), to_string(err_alt),
		format(satellite, 3), to_string(probability), to_string(bias), to_string(bias_dev)};
}
}
}
