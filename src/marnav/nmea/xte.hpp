#ifndef __NMEA__XTE__HPP__
#define __NMEA__XTE__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

class xte : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::XTE;

	xte();
	xte(const xte &) = default;
	xte & operator=(const xte &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<char> status1;
	utils::optional<char> status2;
	utils::optional<double> cross_track_error_magnitude;
	utils::optional<char> direction_to_steer;
	utils::optional<char> cross_track_units;
	utils::optional<char> faa_mode_indicator;

public:
	decltype(status1) get_status1() const { return status1; }
	decltype(status2) get_status2() const { return status2; }
	decltype(cross_track_error_magnitude) get_cross_track_error_magnitude() const
	{
		return cross_track_error_magnitude;
	}
	decltype(direction_to_steer) get_direction_to_steer() const { return direction_to_steer; }
	decltype(cross_track_units) get_cross_track_units() const { return cross_track_units; }
	decltype(faa_mode_indicator) get_faa_mode_indicator() const { return faa_mode_indicator; }

	void set_status1(char t) { status1 = t; }
	void set_status2(char t) { status2 = t; }
	void set_cross_track_error_magnitude(double t) { cross_track_error_magnitude = t; }
	void set_direction_to_steer(char t) { direction_to_steer = t; }
	void set_cross_track_units(char t) { cross_track_units = t; }
	void set_faa_mode_indicato(char t) { faa_mode_indicator = t; }
};
}
}

#endif

