#ifndef __NMEA__GSV__HPP__
#define __NMEA__GSV__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

class gsv : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::GSV;

	gsv();
	gsv(const gsv &) = default;
	gsv & operator=(const gsv &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<uint32_t> n_messages;
	utils::optional<uint32_t> message_number;
	utils::optional<uint32_t> n_satellites_in_view;
	utils::optional<uint32_t> sat_0_id;
	utils::optional<uint32_t> sat_0_elevation;
	utils::optional<uint32_t> sat_0_azimuth; // azimuth against true
	utils::optional<uint32_t> sat_0_snr;
	utils::optional<uint32_t> sat_1_id;
	utils::optional<uint32_t> sat_1_elevation;
	utils::optional<uint32_t> sat_1_azimuth; // azimuth against true
	utils::optional<uint32_t> sat_1_snr;
	utils::optional<uint32_t> sat_2_id;
	utils::optional<uint32_t> sat_2_elevation;
	utils::optional<uint32_t> sat_2_azimuth; // azimuth against true
	utils::optional<uint32_t> sat_2_snr;
	utils::optional<uint32_t> sat_3_id;
	utils::optional<uint32_t> sat_3_elevation;
	utils::optional<uint32_t> sat_3_azimuth; // azimuth against true
	utils::optional<uint32_t> sat_3_snr;

public:
	decltype(n_messages) get_n_messages() const { return n_messages; }
	decltype(message_number) get_message_number() const { return message_number; }
	decltype(n_satellites_in_view) get_n_satellites_in_view() const
	{
		return n_satellites_in_view;
	}
	decltype(sat_0_id) get_sat_0_id() const { return sat_0_id; }
	decltype(sat_0_elevation) get_sat_0_elevation() const { return sat_0_elevation; }
	decltype(sat_0_azimuth) get_sat_0_azimuth() const { return sat_0_azimuth; }
	decltype(sat_0_snr) get_sat_0_snr() const { return sat_0_snr; }
	decltype(sat_1_id) get_sat_1_id() const { return sat_1_id; }
	decltype(sat_1_elevation) get_sat_1_elevation() const { return sat_1_elevation; }
	decltype(sat_1_azimuth) get_sat_1_azimuth() const { return sat_1_azimuth; }
	decltype(sat_1_snr) get_sat_1_snr() const { return sat_1_snr; }
	decltype(sat_2_id) get_sat_2_id() const { return sat_2_id; }
	decltype(sat_2_elevation) get_sat_2_elevation() const { return sat_2_elevation; }
	decltype(sat_2_azimuth) get_sat_2_azimuth() const { return sat_2_azimuth; }
	decltype(sat_2_snr) get_sat_2_snr() const { return sat_2_snr; }
	decltype(sat_3_id) get_sat_3_id() const { return sat_3_id; }
	decltype(sat_3_elevation) get_sat_3_elevation() const { return sat_3_elevation; }
	decltype(sat_3_azimuth) get_sat_3_azimuth() const { return sat_3_azimuth; }
	decltype(sat_3_snr) get_sat_3_snr() const { return sat_3_snr; }

	void set_n_messages(uint32_t t) { n_messages = t; }
	void set_message_number(uint32_t t) { message_number = t; }
	void set_n_satellites_in_view(uint32_t t) { n_satellites_in_view = t; }
	void set_sat(int index, uint32_t id, uint32_t elevation, uint32_t azimuth, uint32_t snr);
	void set_sat_0(uint32_t id, uint32_t elevation, uint32_t azimuth, uint32_t snr);
	void set_sat_1(uint32_t id, uint32_t elevation, uint32_t azimuth, uint32_t snr);
	void set_sat_2(uint32_t id, uint32_t elevation, uint32_t azimuth, uint32_t snr);
	void set_sat_3(uint32_t id, uint32_t elevation, uint32_t azimuth, uint32_t snr);
};
}
}

#endif
