#ifndef __NMEA__GLL__HPP__
#define __NMEA__GLL__HPP__

#include "sentence.hpp"
#include "angle.hpp"
#include "time.hpp"

namespace nmea
{
class gll : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::RMC;

	gll();
	gll(const gll&) = default;
	gll& operator=(const gll&) = default;

	static std::unique_ptr<sentence>
	parse(const std::string& talker,
		  const std::vector<std::string>& fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	optional<nmea::latitude> lat;
	optional<char> lat_hem;
	optional<nmea::longitude> lon;
	optional<char> lon_hem;
	optional<nmea::time> time_utc;
	optional<char> status;

public:
	decltype(lat) get_lat() const { return lat; }
	decltype(lat_hem) get_lat_hem() const { return lat_hem; }
	decltype(lon) get_lon() const { return lon; }
	decltype(lon_hem) get_lon_hem() const { return lon_hem; }
	decltype(time_utc) get_time_utc() const { return time_utc; }
	decltype(status) get_status() const { return status; }

	void set_lat(const latitude& t);
	void set_lon(const longitude& t);
	void set_time_utc(const time& t) { time_utc = t; }
	void set_status(char t) { status = t; }
};
}

#endif
