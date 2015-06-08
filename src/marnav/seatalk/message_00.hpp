#ifndef __SEATALK__MESSAGE_00__HPP__
#define __SEATALK__MESSAGE_00__HPP__

#include "message.hpp"

namespace marnav
{
namespace seatalk
{

class message_00 : public message
{
public:
	constexpr static const message_id ID = message_id::depth_below_transducer;

	message_00();
	message_00(const message_00 &) = default;
	message_00 & operator=(const message_00 &) = default;

	virtual raw get_data() const override;

	static std::unique_ptr<message> parse(const raw & data) throw(std::invalid_argument);

private:
	bool anchor_alarm_active;
	bool metric_display_units;
	bool transducer_defective;
	bool depth_alarm_active;
	bool shallow_depth_alarm_active;
	uint16_t depth; // in 1/10th of feet, 1 m = 3.2808 feet

public:
	bool get_anchor_alarm_active() const { return anchor_alarm_active; }
	bool get_metric_display_units() const { return metric_display_units; }
	bool get_transducer_defective() const { return transducer_defective; }
	bool get_depth_alarm_active() const { return depth_alarm_active; }
	bool get_shallow_depth_alarm_active() const { return shallow_depth_alarm_active; }
	uint16_t get_depth() const { return depth; }

	void set_anchor_alarm_active(bool t) { anchor_alarm_active = t; }
	void set_metric_display_units(bool t) { metric_display_units = t; }
	void set_transducer_defective(bool t) { transducer_defective = t; }
	void set_depth_alarm_active(bool t) { depth_alarm_active = t; }
	void set_shallow_depth_alarm_active(bool t) { shallow_depth_alarm_active = t; }
	void set_depth(uint16_t t) { depth = t; }

public:
	double get_depth_meters() const;
};
}
}

#endif
