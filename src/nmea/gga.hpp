#ifndef __NMEA__GGA__HPP__
#define __NMEA__GGA__HPP__

#include "sentence.hpp"
#include "angle.hpp"
#include "time.hpp"

namespace nmea
{

class gga : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::GGA;

	gga();
	gga(const gga&) = default;
	gga& operator=(const gga&) = default;

	static std::unique_ptr<sentence>
	parse(const std::string& talker,
		  const std::vector<std::string>& fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	optional<nmea::time> time;
	optional<geo::latitude> lat;
	optional<char> lat_hem; // N:north, S:south
	optional<geo::longitude> lon;
	optional<char> lon_hem; // E:east, W:west
	optional<uint32_t> quality;
	optional<uint32_t> n_satellites;
	optional<double> hor_dilution; // horizontal dilution of precision
	optional<double> height_antenna; // height of antenna over geoid
	optional<char> unit_antenna; // M:meter
	optional<double> geodial_separation; // geodial separation, sea level below the ellipsoid
	optional<char> unit_geodial_separation; // M:meter
	optional<double> dgps_age; // age of dgps data
	optional<uint32_t> dgps_ref; // dgps reference station 0000..1023

public:
	decltype(time) get_time() const { return time; }
	decltype(lat) get_lat() const { return lat; }
	decltype(lat_hem) get_lat_hem() const { return lat_hem; }
	decltype(lon) get_lon() const { return lon; }
	decltype(lon_hem) get_lon_hem() const { return lon_hem; }
	decltype(quality) get_quality() const { return quality; }
	decltype(n_satellites) get_n_satellites() const { return n_satellites; }
	decltype(hor_dilution) get_hor_dilution() const { return hor_dilution; }
	decltype(height_antenna) get_height_antenna() const { return height_antenna; }
	decltype(unit_antenna) get_unit_antenna() const { return unit_antenna; }
	decltype(geodial_separation) get_geodial_separation() const { return geodial_separation; }
	decltype(unit_geodial_separation) get_unit_geodial_separation() const
	{
		return unit_geodial_separation;
	}
	decltype(dgps_age) get_dgps_age() const { return dgps_age; }
	decltype(dgps_ref) get_dgps_ref() const { return dgps_ref; }

	void set_time(const nmea::time& t) { time = t; }
	void set_lat(const geo::latitude& t);
	void set_lon(const geo::longitude& t);
	void set_quality(uint32_t t) { quality = t; }
	void set_n_satellites(uint32_t t) { n_satellites = t; }
	void set_hor_dilution(double t) { hor_dilution = t; }
	void set_height_antenna(double t) { height_antenna = t; }
	void set_unit_antenna(char t) { unit_antenna = t; }
	void set_geodial_separation(double t) { geodial_separation = t; }
	void set_unit_geodial_separation(char t) { unit_geodial_separation = t; }
	void set_dgps_age(double t) { dgps_age = t; }
	void set_dgps_ref(uint32_t t) { dgps_ref = t; }
};

}

#endif
