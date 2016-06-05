#ifndef __NMEA__GSA__HPP__
#define __NMEA__GSA__HPP__

#include <array>
#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief GSA - GPS DOP and active satellites
///
/// @code
///        1 2 3                        14 15  16  17
///        | | |                         |  |   |   |
/// $--GSA,a,a,x,x,x,x,x,x,x,x,x,x,x,x,x,x,x.x,x.x,x.x*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  Selection mode: M=Manual, forced to operate in 2D or 3D, A=Automatic, 3D/2D
/// 2.  Mode (1 = no fix, 2 = 2D fix, 3 = 3D fix)
/// 3.  ID of 1st satellite used for fix
/// 4.  ID of 2nd satellite used for fix
/// 5.  ID of 3rd satellite used for fix
/// 6.  ID of 4th satellite used for fix
/// 7.  ID of 5th satellite used for fix
/// 8.  ID of 6th satellite used for fix
/// 9.  ID of 7th satellite used for fix
/// 10. ID of 8th satellite used for fix
/// 11. ID of 9th satellite used for fix
/// 12. ID of 10th satellite used for fix
/// 13. ID of 11th satellite used for fix
/// 14. ID of 12th satellite used for fix
/// 15. PDOP
/// 16. HDOP
/// 17. VDOP
///
class gsa : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::GSA;
	constexpr static const char * TAG = "GSA";

	gsa();
	gsa(const gsa &) = default;
	gsa & operator=(const gsa &) = default;

	static std::unique_ptr<sentence> parse(
		const std::string & talker, fields::const_iterator first, fields::const_iterator last);

protected:
	gsa(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	constexpr static const int max_satellite_ids = 12;

	utils::optional<selection_mode> sel_mode; // A:automatic 2D/3D, M:manual
	utils::optional<uint32_t> mode; // 1 = no fix, 2 = 2D fix, 3 = 3D fix
	std::array<utils::optional<uint32_t>, max_satellite_ids> satellite_id;
	utils::optional<double> pdop;
	utils::optional<double> hdop;
	utils::optional<double> vdop;

	void check_index(int index) const;

public:
	NMEA_GETTER(sel_mode)
	NMEA_GETTER(mode)
	utils::optional<uint32_t> get_satellite_id(int index) const;
	NMEA_GETTER(pdop)
	NMEA_GETTER(hdop)
	NMEA_GETTER(vdop)

	void set_sel_mode(selection_mode t) noexcept { sel_mode = t; }
	void set_mode(uint32_t t) noexcept { mode = t; }
	void set_satellite_id(int index, uint32_t t);
	void set_pdop(double t) noexcept { pdop = t; }
	void set_hdop(double t) noexcept { hdop = t; }
	void set_vdop(double t) noexcept { vdop = t; }
};
}
}

#endif
