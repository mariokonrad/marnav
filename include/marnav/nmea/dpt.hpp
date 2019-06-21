#ifndef MARNAV__NMEA__DPT__HPP
#define MARNAV__NMEA__DPT__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

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
	virtual void append_data_to(std::string &) const override;

private:
	double depth_meter_ = 0.0;
	double transducer_offset_ = 0.0;
	utils::optional<double> max_depth_;

public:
	decltype(depth_meter_) get_depth_meter() const noexcept { return depth_meter_; }
	decltype(transducer_offset_) get_transducer_offset() const noexcept
	{
		return transducer_offset_;
	}
	decltype(max_depth_) get_max_depth() const noexcept { return max_depth_; }

	void set_depth_meter(double t) noexcept { depth_meter_ = t; }
	void set_transducer_offset(double t) noexcept { transducer_offset_ = t; }
	void set_max_depth(double t) noexcept { max_depth_ = t; }
};
}
}

#endif
