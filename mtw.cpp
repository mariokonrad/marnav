#include "mtw.hpp"
#include "unique.hpp"

namespace nmea
{

mtw::mtw(const std::string& talker)
	: sentence(ID, "MTW", talker)
{
}

std::unique_ptr<sentence>
mtw::parse(const std::string& talker,
		   const std::vector<std::string>& fields) throw(std::invalid_argument)
{
	if (fields.size() != 2)
		throw std::invalid_argument{"invalid number of fields in mtw::parse"};

	std::unique_ptr<sentence> result = std::make_unique<mtw>(talker);
	mtw& detail = static_cast<mtw&>(*result);

	read(fields[0], detail.temperature);
	read(fields[1], detail.unit);

	return result;
}

void mtw::append_data(std::ostream& os, const std::string& delimiter) const
{
	os << delimiter;
	os << temperature;
	os << delimiter;
	os << unit;
}

}
