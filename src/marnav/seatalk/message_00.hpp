#ifndef MARNAV__SEATALK__MESSAGE_00__HPP
#define MARNAV__SEATALK__MESSAGE_00__HPP

#include <marnav/seatalk/message.hpp>

namespace marnav
{
namespace seatalk
{

/// @brief Depth below transducer
///
/// @code
/// 00  02  YZ  XX XX
///
/// Depth below transducer: XXXX/10 feet
///    Flags in Y: Y&8 = 8: Anchor Alarm is active
///                Y&4 = 4: Metric display units or
///                         Fathom display units if followed by command 65
///                Y&2 = 2: Used, unknown meaning
///    Flags in Z: Z&4 = 4: Transducer defective
///                Z&2 = 2: Deep Alarm is active
///                Z&1 = 1: Shallow Depth Alarm is active
/// @endcode
///
/// Corresponding NMEA sentences: DPT, DBT
///
class message_00 : public message
{
public:
	constexpr static message_id ID = message_id::depth_below_transducer;
	constexpr static size_t SIZE = 5;

	message_00();
	message_00(const message_00 &) = default;
	message_00 & operator=(const message_00 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	bool anchor_alarm_active_;
	bool metric_display_units_;
	bool transducer_defective_;
	bool depth_alarm_active_;
	bool shallow_depth_alarm_active_;
	uint16_t depth_; // in 1/10th of feet, 1 m = 3.2808 feet

public:
	bool get_anchor_alarm_active() const noexcept { return anchor_alarm_active_; }
	bool get_metric_display_units() const noexcept { return metric_display_units_; }
	bool get_transducer_defective() const noexcept { return transducer_defective_; }
	bool get_depth_alarm_active() const noexcept { return depth_alarm_active_; }
	bool get_shallow_depth_alarm_active() const noexcept { return shallow_depth_alarm_active_; }
	uint16_t get_depth() const noexcept { return depth_; }

	void set_anchor_alarm_active(bool t) noexcept { anchor_alarm_active_ = t; }
	void set_metric_display_units(bool t) noexcept { metric_display_units_ = t; }
	void set_transducer_defective(bool t) noexcept { transducer_defective_ = t; }
	void set_depth_alarm_active(bool t) noexcept { depth_alarm_active_ = t; }
	void set_shallow_depth_alarm_active(bool t) noexcept { shallow_depth_alarm_active_ = t; }
	void set_depth(uint16_t t) noexcept { depth_ = t; }

public:
	double get_depth_meters() const noexcept;
	void set_depth_meters(double t) noexcept;
};
}
}

#endif
