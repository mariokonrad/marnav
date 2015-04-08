#ifndef __NMEA__VLW__HPP__
#define __NMEA__VLW__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

class vlw : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::VLW;

	vlw();
	vlw(const vlw &) = default;
	vlw & operator=(const vlw &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> distance_cum; // total cumulative distance
	utils::optional<char> distance_cum_unit; // N:nautical miles
	utils::optional<double> distance_reset; // distance since reset
	utils::optional<char> distance_reset_unit; // N:nautical miles

public:
	decltype(distance_cum) get_distance_cum() const { return distance_cum; }
	decltype(distance_cum_unit) get_distance_cum_unit() const { return distance_cum_unit; }
	decltype(distance_reset) get_distance_reset() const { return distance_reset; }
	decltype(distance_reset_unit) get_distance_reset_unit() const
	{
		return distance_reset_unit;
	}

	void set_distance_cum_nm(double t);
	void set_distance_reset_nm(double t);
};
}
}

#endif
