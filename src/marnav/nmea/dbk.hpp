#ifndef MARNAV__NMEA__DBK__HPP
#define MARNAV__NMEA__DBK__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace nmea
{
/// @brief DBK - Depth Below Keel
///
/// @note This sentence appears to be deprected, use @ref marnav::nmea::dpt "DPT" instead.
///
/// @code
///        1   2 3   4 5   6
///        |   | |   | |   |
/// $--DBK,x.x,f,x.x,M,x.x,F*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Depth feet
/// 2. Depth feet unit
///    - f = feet
/// 3. Depth meters
/// 4. Depth meters unit
///    - M = meters
/// 5. Depth Fathoms
/// 6. Depth Fathoms
///    - F = Fathoms
///
class MARNAV_EXPORT dbk : public sentence
{
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::DBK;
	constexpr static const char * TAG = "DBK";

	dbk();
	dbk(const dbk &) = default;
	dbk & operator=(const dbk &) = default;
	dbk(dbk &&) = default;
	dbk & operator=(dbk &&) = default;

protected:
	dbk(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable: 4251)
#endif
	utils::optional<double> depth_feet_;
	utils::optional<unit::distance> depth_feet_unit_;
	utils::optional<double> depth_meter_;
	utils::optional<unit::distance> depth_meter_unit_;
	utils::optional<double> depth_fathom_;
	utils::optional<unit::distance> depth_fathom_unit_;
#ifdef _MSC_VER
#pragma warning(pop)
#endif

public:
	decltype(depth_feet_) get_depth_feet() const { return depth_feet_; }
	decltype(depth_feet_unit_) get_depth_feet_unit() const { return depth_feet_unit_; }
	decltype(depth_meter_) get_depth_meter() const { return depth_meter_; }
	decltype(depth_meter_unit_) get_depth_meter_unit() const { return depth_meter_unit_; }
	decltype(depth_fathom_) get_depth_fathom() const { return depth_fathom_; }
	decltype(depth_fathom_unit_) get_depth_fathom_unit() const { return depth_fathom_unit_; }

	void set_depth_feet(double t) noexcept;
	void set_depth_meter(double t) noexcept;
	void set_depth_fathom(double t) noexcept;
};
}
}

#endif
