#include "gsa.hpp"
#include <utils/unique.hpp>
#include "io.hpp"

namespace nmea
{

gsa::gsa()
	: sentence(ID, "GSA", talker_id::global_positioning_system)
{
}

void gsa::set_satellite_id(int index, uint32_t t)
{
	switch (index) {
		case 1:
			satellite_id_01 = t;
			break;
		case 2:
			satellite_id_02 = t;
			break;
		case 3:
			satellite_id_03 = t;
			break;
		case 4:
			satellite_id_04 = t;
			break;
		case 5:
			satellite_id_05 = t;
			break;
		case 6:
			satellite_id_06 = t;
			break;
		case 7:
			satellite_id_07 = t;
			break;
		case 8:
			satellite_id_08 = t;
			break;
		case 9:
			satellite_id_09 = t;
			break;
		case 10:
			satellite_id_10 = t;
			break;
		case 11:
			satellite_id_11 = t;
			break;
		case 12:
			satellite_id_12 = t;
			break;
		default:
			break;
	}
}

std::unique_ptr<sentence>
gsa::parse(const std::string& talker,
		   const std::vector<std::string>& fields) throw(std::invalid_argument)
{
	if (fields.size() != 17)
		throw std::invalid_argument{"invalid number of fields in gsa::parse"};

	std::unique_ptr<sentence> result = utils::make_unique<gsa>();
	result->set_talker(talker);
	gsa& detail = static_cast<gsa&>(*result);

	read(fields[ 0], detail.selection_mode);
	read(fields[ 1], detail.mode);
	read(fields[ 2], detail.satellite_id_01);
	read(fields[ 3], detail.satellite_id_02);
	read(fields[ 4], detail.satellite_id_03);
	read(fields[ 5], detail.satellite_id_04);
	read(fields[ 6], detail.satellite_id_05);
	read(fields[ 7], detail.satellite_id_06);
	read(fields[ 8], detail.satellite_id_07);
	read(fields[ 9], detail.satellite_id_08);
	read(fields[10], detail.satellite_id_09);
	read(fields[11], detail.satellite_id_10);
	read(fields[12], detail.satellite_id_11);
	read(fields[13], detail.satellite_id_12);
	read(fields[14], detail.pdop);
	read(fields[15], detail.hdop);
	read(fields[16], detail.vdop);

	return result;
}

std::vector<std::string> gsa::get_data() const
{
	return {to_string(selection_mode),  to_string(mode),			to_string(satellite_id_01),
			to_string(satellite_id_02), to_string(satellite_id_03), to_string(satellite_id_04),
			to_string(satellite_id_05), to_string(satellite_id_06), to_string(satellite_id_07),
			to_string(satellite_id_08), to_string(satellite_id_09), to_string(satellite_id_10),
			to_string(satellite_id_11), to_string(satellite_id_12), to_string(pdop),
			to_string(hdop),			to_string(vdop)};
}

}

