#ifndef __SEATALK__MESSAGE_00__HPP__
#define __SEATALK__MESSAGE_00__HPP__

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
	constexpr static const message_id ID = message_id::depth_below_transducer;

	message_00();
	message_00(const message_00 &) = default;
	message_00 & operator=(const message_00 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data);

private:
	bool anchor_alarm_active;
	bool metric_display_units;
	bool transducer_defective;
	bool depth_alarm_active;
	bool shallow_depth_alarm_active;
	uint16_t depth; // in 1/10th of feet, 1 m = 3.2808 feet

public:
	bool get_anchor_alarm_active() const noexcept { return anchor_alarm_active; }
	bool get_metric_display_units() const noexcept { return metric_display_units; }
	bool get_transducer_defective() const noexcept { return transducer_defective; }
	bool get_depth_alarm_active() const noexcept { return depth_alarm_active; }
	bool get_shallow_depth_alarm_active() const noexcept { return shallow_depth_alarm_active; }
	uint16_t get_depth() const noexcept { return depth; }

	void set_anchor_alarm_active(bool t) noexcept { anchor_alarm_active = t; }
	void set_metric_display_units(bool t) noexcept { metric_display_units = t; }
	void set_transducer_defective(bool t) noexcept { transducer_defective = t; }
	void set_depth_alarm_active(bool t) noexcept { depth_alarm_active = t; }
	void set_shallow_depth_alarm_active(bool t) noexcept { shallow_depth_alarm_active = t; }
	void set_depth(uint16_t t) noexcept { depth = t; }

public:
	double get_depth_meters() const noexcept;
};
}
}

#endif
