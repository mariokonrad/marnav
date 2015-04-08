#ifndef __NMEA__MWV__HPP__
#define __NMEA__MWV__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

class mwv : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::MWV;

	mwv();
	mwv(const mwv &) = default;
	mwv & operator=(const mwv &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> angle; // wind angle, 0..359 right of bow
	utils::optional<char> type; // R:relative, T:true
	utils::optional<double> speed; // wind speed
	utils::optional<char> speed_unit; // wind speed unit, K:knots, M:mph
	utils::optional<char> status; // status, A:valid

public:
	decltype(angle) get_angle() const { return angle; }
	decltype(type) get_type() const { return type; }
	decltype(speed) get_speed() const { return speed; }
	decltype(speed_unit) get_speed_unit() const { return speed_unit; }
	decltype(status) get_status() const { return status; }

	void set_angle(double deg, char type);
	void set_speed(double speed, char unit);
	void set_status(char t) { status = t; }
};
}
}

#endif
