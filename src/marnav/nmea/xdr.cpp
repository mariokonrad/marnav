#include "xdr.hpp"
#include <marnav/nmea/io.hpp>
#include <marnav/utils/unique.hpp>

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

void xdr::check_index(int index) const throw(std::out_of_range)
{
	if ((index < 0) || (index >= 4 * MAX_TRANSDUCER_INFO)) {
		throw std::out_of_range{"transducer index out of range"};
	}
}

void xdr::set_info(int index, const transducer_info & info) throw(std::out_of_range)
{
	check_index(index);
	transducer_data[index] = info;
}

utils::optional<xdr::transducer_info> xdr::get_info(int index) const throw(std::out_of_range)
{
	check_index(index);
	return transducer_data[index];
}

std::unique_ptr<sentence> xdr::parse(const std::string & talker,
	const std::vector<std::string> & fields) throw(std::invalid_argument, std::runtime_error)
{
	if ((fields.size() < 1) || (fields.size() > 4 * xdr::MAX_TRANSDUCER_INFO))
		throw std::invalid_argument{"invalid number of fields in xdr::parse"};

	if ((fields.size() % 4) != 0)
		throw std::invalid_argument{"unexpected number of fields in xdr::parse (quadruples?)"};

	std::unique_ptr<sentence> result = utils::make_unique<xdr>();
	result->set_talker(talker);
	xdr & detail = static_cast<xdr &>(*result);

	int index = 0;
	for (std::vector<std::string>::size_type i = 0; i < fields.size(); i += 4, ++index) {
		xdr::transducer_info info;
		read(fields[i + 0], info.transducer_type);
		read(fields[i + 1], info.measurement_data);
		read(fields[i + 2], info.units_of_measurement);
		read(fields[i + 3], info.name);
		detail.set_info(index, info);
	}

	return result;
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

