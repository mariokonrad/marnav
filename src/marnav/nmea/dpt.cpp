#include <marnav/nmea/dpt.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav
{
namespace nmea
{
constexpr sentence_id dpt::ID;
constexpr const char * dpt::TAG;

dpt::dpt()
	: dpt(talker::integrated_instrumentation)
{
}

dpt::dpt(talker talk)
	: sentence(ID, TAG, talk)
{
}

dpt::dpt(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	const auto size = std::distance(first, last);
	if ((size < 2) || (size > 3))
		throw std::invalid_argument{"invalid number of fields in dpt"};

	read(*(first + 0), depth_meter_);
	read(*(first + 1), transducer_offset_);

	if (size > 2)
		read(*(first + 2), max_depth_);
}

void dpt::set_depth_meter(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"depth less than zero"};
	depth_meter_ = t.get<units::meters>();
}

void dpt::set_transducer_offset(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"transducer offset less than zero"};
	transducer_offset_ = t.get<units::meters>();
}

void dpt::set_max_depth(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"max depth less than zero"};
	max_depth_ = t.get<units::meters>();
}

utils::optional<units::length> dpt::get_max_depth() const noexcept
{
	if (!max_depth_)
		return {};
	return {*max_depth_};
}

void dpt::append_data_to(std::string & s) const
{
	append(s, to_string(depth_meter_));
	append(s, to_string(transducer_offset_));
	append(s, to_string(max_depth_));
}
}
}
