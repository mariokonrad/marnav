#ifndef __NMEA__RMB__HPP__
#define __NMEA__RMB__HPP__

#include "sentence.hpp"
#include "angle.hpp"

namespace nmea
{

class rmb : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::RMB;

	rmb();
	rmb(const rmb&) = default;
	rmb& operator=(const rmb&) = default;

	static std::unique_ptr<sentence>
	parse(const std::string& talker,
		  const std::vector<std::string>& fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	void check_waypoint_id(const std::string& id) const throw(std::invalid_argument);

	optional<char> status; // V:warning
	optional<double> cross_track_error; // cross track error in nautical miles
	optional<char> steer_dir; // direction to steer, left or right
	optional<std::string> waypoint_to; // TO waypoint ID
	optional<std::string> waypoint_from; // FROM waypoint ID
	optional<geo::latitude> lat; // destination waypoint latitude
	optional<char> lat_hem; // destination waypoint latitude dir, N:north, S:south
	optional<geo::longitude> lon; // destination waypoint longitude
	optional<char> lon_hem; // destination waypoint longitude dir, E:east, W:west
	optional<double> range; // range to destination in nautical miles
	optional<double> bearing; // bearing to destination in degrees to true
	optional<double> dst_velocity; // destination closing velocity in knots
	optional<char> arrival_status; // arrival status, A:arrival circle entered

public:
	decltype(status) get_status() const { return status; }
	decltype(cross_track_error) get_cross_track_error() const { return cross_track_error; }
	decltype(steer_dir) get_steer_dir() const { return steer_dir; }
	decltype(waypoint_to) get_waypoint_to() const { return waypoint_to; }
	decltype(waypoint_from) get_waypoint_from() const { return waypoint_from; }
	decltype(lat) get_lat() const { return lat; }
	decltype(lat_hem) get_lat_hem() const { return lat_hem; }
	decltype(lon) get_lon() const { return lon; }
	decltype(lon_hem) get_lon_hem() const { return lon_hem; }
	decltype(range) get_range() const { return range; }
	decltype(bearing) get_bearing() const { return bearing; }
	decltype(dst_velocity) get_dst_velocity() const { return dst_velocity; }
	decltype(arrival_status) get_arrival_status() const { return arrival_status; }

	void set_status(char t) { status = t; }
	void set_cross_track_error(double t) { cross_track_error = t; }
	void set_steer_dir(char t) { steer_dir = t; }
	void set_waypoint_to(const std::string& id);
	void set_waypoint_from(const std::string& id);
	void set_lat(const geo::latitude& t);
	void set_lon(const geo::longitude& t);
	void set_range(double t) { range = t; }
	void set_bearing(double t) { bearing = t; }
	void set_dst_velocity(double t) { dst_velocity = t; }
	void set_arrival_status(char t) { arrival_status = t; }
};

}

#endif
