#ifndef __NMEA__VHW__HPP__
#define __NMEA__VHW__HPP__

#include "sentence.hpp"

namespace nmea
{

class vhw : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::VHW;

	vhw();
	vhw(const vhw&) = default;
	vhw& operator=(const vhw&) = default;

	static std::unique_ptr<sentence>
	parse(const std::string& talker,
		  const std::vector<std::string>& fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	optional<char> heading_empty; // heading (empty)
	optional<char> degrees_true; // T:true
	optional<double> heading; // heading in degrees, 0..359
	optional<char> degrees_mag; // M:magnetic
	optional<double> speed_knots; // speed in knots
	optional<char> speed_knots_unit; // N:knots
	optional<double> speed_kmh; // speed in kilometers per hour
	optional<char> speed_kmh_unit; // K:kmh

public:
	decltype(heading_empty) get_heading_empty() const { return heading_empty; }
	decltype(degrees_true) get_degrees_true() const { return degrees_true; }
	decltype(heading) get_heading() const { return heading; }
	decltype(degrees_mag) get_degrees_mag() const { return degrees_mag; }
	decltype(speed_knots) get_speed_knots() const { return speed_knots; }
	decltype(speed_knots_unit) get_speed_knots_unit() const { return speed_knots_unit; }
	decltype(speed_kmh) get_speed_kmh() const { return speed_kmh; }
	decltype(speed_kmh_unit) get_speed_kmh_unit() const { return speed_kmh_unit; }

	void set_heading(double t);
	void set_speed_knots(double t);
	void set_speed_kmh(double t);
};

}

#endif
