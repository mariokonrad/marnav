#ifndef MARNAV_NMEA_GSA_HPP
#define MARNAV_NMEA_GSA_HPP

#include <marnav/nmea/sentence.hpp>
#include <array>
#include <optional>

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
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::GSA;
	constexpr static const char * TAG = "GSA";

	constexpr static int max_satellite_ids = 12;

	gsa();
	gsa(const gsa &) = default;
	gsa & operator=(const gsa &) = default;
	gsa(gsa &&) = default;
	gsa & operator=(gsa &&) = default;

protected:
	gsa(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<selection_mode> sel_mode_; // A:automatic 2D/3D, M:manual
	std::optional<uint32_t> mode_; // 1 = no fix, 2 = 2D fix, 3 = 3D fix, TODO: enum
	std::array<std::optional<uint32_t>, max_satellite_ids> satellite_id_;
	std::optional<double> pdop_; // positional dilution of precision
	std::optional<double> hdop_; // horizontal dilution of precision
	std::optional<double> vdop_; // vertical dilution of precision

	void check_index(int index) const;

public:
	std::optional<selection_mode> get_sel_mode() const { return sel_mode_; }
	std::optional<uint32_t> get_mode() const { return mode_; }
	std::optional<uint32_t> get_satellite_id(int index) const;
	std::optional<double> get_pdop() const { return pdop_; }
	std::optional<double> get_hdop() const { return hdop_; }
	std::optional<double> get_vdop() const { return vdop_; }

	void set_sel_mode(selection_mode t) noexcept { sel_mode_ = t; }
	void set_mode(uint32_t t) noexcept { mode_ = t; }
	void set_satellite_id(int index, uint32_t t);
	void set_pdop(double t) noexcept { pdop_ = t; }
	void set_hdop(double t) noexcept { hdop_ = t; }
	void set_vdop(double t) noexcept { vdop_ = t; }
};
}
}

#endif
