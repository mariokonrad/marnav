#include "gsv.hpp"
#include <utils/unique.hpp>
#include "io.hpp"
#include <iostream>

namespace nmea
{

gsv::gsv()
	: sentence(ID, "GSV", talker_id::global_positioning_system)
{
}

void gsv::set_sat(int index, uint32_t id, uint32_t elevation, uint32_t azimuth, uint32_t snr)
{
	switch (index) {
		case 1:
			set_sat_0(id, elevation, azimuth, snr);
			break;
		case 2:
			set_sat_1(id, elevation, azimuth, snr);
			break;
		case 3:
			set_sat_2(id, elevation, azimuth, snr);
			break;
		case 4:
			set_sat_3(id, elevation, azimuth, snr);
			break;
		default:
			break;
	}
}

void gsv::set_sat_0(uint32_t id, uint32_t elevation, uint32_t azimuth, uint32_t snr)
{
	sat_0_id = id;
	sat_0_elevation = elevation;
	sat_0_azimuth = azimuth;
	sat_0_snr = snr;
}

void gsv::set_sat_1(uint32_t id, uint32_t elevation, uint32_t azimuth, uint32_t snr)
{
	sat_1_id = id;
	sat_1_elevation = elevation;
	sat_1_azimuth = azimuth;
	sat_1_snr = snr;
}

void gsv::set_sat_2(uint32_t id, uint32_t elevation, uint32_t azimuth, uint32_t snr)
{
	sat_2_id = id;
	sat_2_elevation = elevation;
	sat_2_azimuth = azimuth;
	sat_2_snr = snr;
}

void gsv::set_sat_3(uint32_t id, uint32_t elevation, uint32_t azimuth, uint32_t snr)
{
	sat_3_id = id;
	sat_3_elevation = elevation;
	sat_3_azimuth = azimuth;
	sat_3_snr = snr;
}

std::unique_ptr<sentence>
gsv::parse(const std::string& talker,
		   const std::vector<std::string>& fields) throw(std::invalid_argument)
{
	if (fields.size() != 19) {
		throw std::invalid_argument{
			std::string{"invalid number of fields in gsv::parse: expected 19, got "}
			+ std::to_string(fields.size())};
	}

	std::unique_ptr<sentence> result = utils::make_unique<gsv>();
	result->set_talker(talker);
	gsv& detail = static_cast<gsv&>(*result);

	read(fields[ 0], detail.n_messages);
	read(fields[ 1], detail.message_number);
	read(fields[ 2], detail.n_satellites_in_view);
	read(fields[ 3], detail.sat_0_id);
	read(fields[ 4], detail.sat_0_elevation);
	read(fields[ 5], detail.sat_0_azimuth);
	read(fields[ 6], detail.sat_0_snr);
	read(fields[ 7], detail.sat_1_id);
	read(fields[ 8], detail.sat_1_elevation);
	read(fields[ 9], detail.sat_1_azimuth);
	read(fields[10], detail.sat_1_snr);
	read(fields[11], detail.sat_2_id);
	read(fields[12], detail.sat_2_elevation);
	read(fields[13], detail.sat_2_azimuth);
	read(fields[14], detail.sat_2_snr);
	read(fields[15], detail.sat_3_id);
	read(fields[16], detail.sat_3_elevation);
	read(fields[17], detail.sat_3_azimuth);
	read(fields[18], detail.sat_3_snr);

	return result;
}

std::vector<std::string> gsv::get_data() const
{
	return {to_string(n_messages),		to_string(message_number),  to_string(n_satellites_in_view),
			format(sat_0_id, 2),		format(sat_0_elevation, 2), format(sat_0_azimuth, 3),
			format(sat_0_snr, 2),		format(sat_1_id, 2),		format(sat_1_elevation, 2),
			format(sat_1_azimuth, 3),   format(sat_1_snr, 2),		format(sat_2_id, 2),
			format(sat_2_elevation, 2), format(sat_2_azimuth, 3),   format(sat_2_snr, 2),
			format(sat_3_id, 2),		format(sat_3_elevation, 2), format(sat_3_azimuth, 3),
			format(sat_3_snr, 2)};
}
}

