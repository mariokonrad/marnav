#ifndef __NMEA__RMC__HPP__
#define __NMEA__RMC__HPP__

#include "sentence.hpp"
#include "date.hpp"
#include "time.hpp"
#include "angle.hpp"

namespace nmea
{

class rmc : public sentence
{
public:
	constexpr static const SentenceID ID = SentenceID::RMC;

	rmc(const std::string& talker);

	static std::unique_ptr<sentence>
	parse(const std::string& talker,
		  const std::vector<std::string>& fields) throw(std::invalid_argument);

protected:
	virtual void append_data(std::ostream& os, const std::string& delimiter) const override;

private:
	optional<nmea::time> time_utc;
	optional<char> status;
	optional<nmea::latitude> lat;
	optional<char> lat_hem;
	optional<nmea::longitude> lon;
	optional<char> lon_hem;
	optional<double> sog;
	optional<double> heading;
	optional<nmea::date> date;
	optional<double> mag;
	optional<char> mag_hem;
	optional<char> faa_mode_indicator;

public:
	decltype(time_utc) get_time_utc() const { return time_utc; }
	decltype(status) get_status() const { return status; }
	decltype(lat) get_lat() const { return lat; }
	decltype(lat_hem) get_lat_hem() const { return lat_hem; }
	decltype(lon) get_lon() const { return lon; }
	decltype(lon_hem) get_lon_hem() const { return lon_hem; }
	decltype(sog) get_sog() const { return sog; }
	decltype(heading) get_heading() const { return heading; }
	decltype(date) get_date() const { return date; }
	decltype(mag) get_mag() const { return mag; }
	decltype(mag_hem) get_mag_hem() const { return mag_hem; }
	decltype(faa_mode_indicator) get_faa_mode_indicator() const { return faa_mode_indicator; }
};

}

#endif
