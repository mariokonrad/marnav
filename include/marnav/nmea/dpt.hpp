#ifndef MARNAV_NMEA_DPT_HPP
#define MARNAV_NMEA_DPT_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/units/units.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
/// @brief DPT - Depth of Water
///
/// Water depth relative to the transducer and offset of the measuring transducer.
///
/// @code
///        1   2   3
///        |   |   |
/// $--DPT,x.x,x.x,x.x*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Depth meters
/// 2. Offset from transducer
///    - positive value means distance from tansducer to water line
///    - negative value means distance from transducer to keel
/// 3. Max depth in meters, might be empty. This field exists allegedly since NMEA 3.0
///
class dpt : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::DPT;
	constexpr static const char * TAG = "DPT";

	dpt();
	dpt(talker talk);
	dpt(const dpt &) = default;
	dpt & operator=(const dpt &) = default;
	dpt(dpt &&) = default;
	dpt & operator=(dpt &&) = default;

protected:
	dpt(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	units::meters depth_meter_ = units::meters{0.0};
	units::meters transducer_offset_ = units::meters{0.0};
	std::optional<units::meters> max_depth_;

public:
	units::length get_depth_meter() const noexcept { return {depth_meter_}; }
	units::length get_transducer_offset() const noexcept { return {transducer_offset_}; }
	std::optional<units::length> get_max_depth() const noexcept;

	void set_depth_meter(units::length t);
	void set_transducer_offset(units::length t);
	void set_max_depth(units::length t);
};
}
}

#endif
