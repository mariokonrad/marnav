#include "xdr.hpp"
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{

namespace
{
inline std::string to_string(const utils::optional<xdr::transducer_info> & data)
{
	if (!data)
		return std::string{};
	auto const & value = data.value();
	return marnav::nmea::to_string(value.transducer_type) + ","
		+ marnav::nmea::to_string(value.measurement_data) + ","
		+ marnav::nmea::to_string(value.units_of_measurement) + ","
		+ marnav::nmea::to_string(value.name);
}
}

constexpr const char * xdr::TAG;

xdr::xdr()
	: sentence(ID, TAG, talker_id::transducer)
{
}

xdr::xdr(const std::string & talker, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talker)
{
	const auto size = std::distance(first, last);
	if ((size < 1) || (size > 4 * xdr::max_transducer_info))
		throw std::invalid_argument{"invalid number of fields in xdr"};

	if ((size % 4) != 0)
		throw std::invalid_argument{"unexpected number of fields in xdr::parse (quadruples?)"};

	int index = 0;
	for (auto i = 0; i < size; i += 4, ++index) {
		xdr::transducer_info info;
		read(*(first + i + 0), info.transducer_type);
		read(*(first + i + 1), info.measurement_data);
		read(*(first + i + 2), info.units_of_measurement);
		read(*(first + i + 3), info.name);
		set_info(index, info);
	}
}

void xdr::check_index(int index) const
{
	if ((index < 0) || (index >= 4 * max_transducer_info)) {
		throw std::out_of_range{"transducer index out of range"};
	}
}

void xdr::set_info(int index, const transducer_info & info)
{
	check_index(index);
	transducer_data[index] = info;
}

utils::optional<xdr::transducer_info> xdr::get_info(int index) const
{
	check_index(index);
	return transducer_data[index];
}

std::unique_ptr<sentence> xdr::parse(
	const std::string & talker, fields::const_iterator first, fields::const_iterator last)
{
	return std::unique_ptr<xdr>(new xdr(talker, first, last));
}

std::vector<std::string> xdr::get_data() const
{
	std::vector<std::string> result;
	for (const auto & data : transducer_data) {
		auto s = to_string(data);
		if (!s.empty())
			result.push_back(s);
	}
	return result;
}
}
}
