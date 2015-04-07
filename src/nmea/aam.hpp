#ifndef __NMEA__AAM__HPP__
#define __NMEA__AAM__HPP__

#include "sentence.hpp"
#include <utils/optional.hpp>

namespace marnav
{
namespace nmea
{

class aam : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::AAM;

	aam();
	aam(const aam &) = default;
	aam & operator=(const aam &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	void check_waypoint_id(const std::string & id) const throw(std::invalid_argument);

	utils::optional<char> arrival_circle_entered;
	utils::optional<char> perpendicualar_passed;
	utils::optional<double> arrival_circle_radius;
	utils::optional<char> arrival_circle_radius_unit;
	utils::optional<std::string> waypoint_id;

public:
	decltype(arrival_circle_entered) get_arrival_circle_entered() const
	{
		return arrival_circle_entered;
	}
	decltype(perpendicualar_passed) get_perpendicualar_passed() const
	{
		return perpendicualar_passed;
	}
	decltype(arrival_circle_radius) get_arrival_circle_radius() const
	{
		return arrival_circle_radius;
	}
	decltype(arrival_circle_radius_unit) get_arrival_circle_radius_unit() const
	{
		return arrival_circle_radius_unit;
	}
	decltype(waypoint_id) get_waypoint_id() const { return waypoint_id; }

	void set_arrival_circle_entered() { arrival_circle_entered = status::OK; }
	void set_perpendicular_passed() { perpendicualar_passed = status::OK; }
	void set_arrival_circle_radius(double t);
	void set_waypoint_id(const std::string & id);
};
}
}

#endif
