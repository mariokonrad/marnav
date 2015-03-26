#ifndef __NMEA__DPT__HPP__
#define __NMEA__DPT__HPP__

#include "sentence.hpp"
#include <utils/optional.hpp>

namespace nmea
{

class dpt : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::DPT;

	dpt();
	dpt(const dpt&) = default;
	dpt& operator=(const dpt&) = default;

	static std::unique_ptr<sentence>
	parse(const std::string& talker,
		  const std::vector<std::string>& fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> depth_meter;
	utils::optional<double> transducer_offset;

public:
	decltype(depth_meter) get_depth_meter() const { return depth_meter; }
	decltype(transducer_offset) get_transducer_offset() const { return transducer_offset; }

	void set_depth_meter(double t) { depth_meter = t; }
	void set_transducer_offset(double t) { transducer_offset = t; }
};

}

#endif
