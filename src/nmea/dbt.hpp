#ifndef __NMEA__DBT__HPP__
#define __NMEA__DBT__HPP__

#include "sentence.hpp"

namespace nmea
{

class dbt : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::DBT;

	dbt();
	dbt(const dbt&) = default;
	dbt& operator=(const dbt&) = default;

	static std::unique_ptr<sentence>
	parse(const std::string& talker,
		  const std::vector<std::string>& fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	optional<double> depth_feet; // water depth in feet
	optional<char> depth_unit_feet; // f:feet
	optional<double> depth_meter; // water depth in meter
	optional<char> depth_unit_meter; // M:meter
	optional<double> depth_fathom; // water depth in fathom
	optional<char> depth_unit_fathom; // F:fathom

public:
	decltype(depth_feet) get_depth_feet() const { return depth_feet; }
	decltype(depth_unit_feet) get_depth_unit_feet() const { return depth_unit_feet; }
	decltype(depth_meter) get_depth_meter() const { return depth_meter; }
	decltype(depth_unit_meter) get_depth_unit_meter() const { return depth_unit_meter; }
	decltype(depth_fathom) get_depth_fathom() const { return depth_fathom; }
	decltype(depth_unit_fathom) get_depth_unit_fathom() const { return depth_unit_fathom; }

	void set_depth_feet(double t);
	void set_depth_meter(double t);
	void set_depth_fathom(double t);
};

}

#endif
