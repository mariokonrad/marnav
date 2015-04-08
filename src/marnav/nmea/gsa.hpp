#ifndef __NMEA__GSA__HPP__
#define __NMEA__GSA__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

class gsa : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::GSA;

	gsa();
	gsa(const gsa &) = default;
	gsa & operator=(const gsa &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<char> selection_mode; // A:automatic 2D/3D, M:manual
	utils::optional<uint32_t> mode; // 1 = no fix, 2 = 2D fix, 3 = 3D fix
	utils::optional<uint32_t> satellite_id_01;
	utils::optional<uint32_t> satellite_id_02;
	utils::optional<uint32_t> satellite_id_03;
	utils::optional<uint32_t> satellite_id_04;
	utils::optional<uint32_t> satellite_id_05;
	utils::optional<uint32_t> satellite_id_06;
	utils::optional<uint32_t> satellite_id_07;
	utils::optional<uint32_t> satellite_id_08;
	utils::optional<uint32_t> satellite_id_09;
	utils::optional<uint32_t> satellite_id_10;
	utils::optional<uint32_t> satellite_id_11;
	utils::optional<uint32_t> satellite_id_12;
	utils::optional<double> pdop;
	utils::optional<double> hdop;
	utils::optional<double> vdop;

public:
	decltype(selection_mode) get_selection_mode() const { return selection_mode; }
	decltype(mode) get_mode() const { return mode; }
	decltype(satellite_id_01) get_satellite_id_01() const { return satellite_id_01; }
	decltype(satellite_id_02) get_satellite_id_02() const { return satellite_id_02; }
	decltype(satellite_id_03) get_satellite_id_03() const { return satellite_id_03; }
	decltype(satellite_id_04) get_satellite_id_04() const { return satellite_id_04; }
	decltype(satellite_id_05) get_satellite_id_05() const { return satellite_id_05; }
	decltype(satellite_id_06) get_satellite_id_06() const { return satellite_id_06; }
	decltype(satellite_id_07) get_satellite_id_07() const { return satellite_id_07; }
	decltype(satellite_id_08) get_satellite_id_08() const { return satellite_id_08; }
	decltype(satellite_id_09) get_satellite_id_09() const { return satellite_id_09; }
	decltype(satellite_id_10) get_satellite_id_10() const { return satellite_id_10; }
	decltype(satellite_id_11) get_satellite_id_11() const { return satellite_id_11; }
	decltype(satellite_id_12) get_satellite_id_12() const { return satellite_id_12; }
	decltype(pdop) get_pdop() const { return pdop; }
	decltype(hdop) get_hdop() const { return hdop; }
	decltype(vdop) get_vdop() const { return vdop; }

	void set_selection_mode(char t) { selection_mode = t; }
	void set_mode(uint32_t t) { mode = t; }
	void set_satellite_id_01(uint32_t t) { satellite_id_01 = t; }
	void set_satellite_id_02(uint32_t t) { satellite_id_02 = t; }
	void set_satellite_id_03(uint32_t t) { satellite_id_03 = t; }
	void set_satellite_id_04(uint32_t t) { satellite_id_04 = t; }
	void set_satellite_id_05(uint32_t t) { satellite_id_05 = t; }
	void set_satellite_id_06(uint32_t t) { satellite_id_06 = t; }
	void set_satellite_id_07(uint32_t t) { satellite_id_07 = t; }
	void set_satellite_id_08(uint32_t t) { satellite_id_08 = t; }
	void set_satellite_id_09(uint32_t t) { satellite_id_09 = t; }
	void set_satellite_id_10(uint32_t t) { satellite_id_10 = t; }
	void set_satellite_id_11(uint32_t t) { satellite_id_11 = t; }
	void set_satellite_id_12(uint32_t t) { satellite_id_12 = t; }
	void set_pdop(double t) { pdop = t; }
	void set_hdop(double t) { hdop = t; }
	void set_vdop(double t) { vdop = t; }

	void set_satellite_id(int index, uint32_t t);
};
}
}

#endif
