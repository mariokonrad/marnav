#ifndef __NMEA__MTW__HPP__
#define __NMEA__MTW__HPP__

#include "sentence.hpp"

namespace nmea
{
class mtw : public sentence
{
public:
	constexpr static const SentenceID ID = SentenceID::MTW;

	mtw(const std::string& talker);

	static std::unique_ptr<sentence>
	parse(const std::string& talker,
		  const std::vector<std::string>& fields) throw(std::invalid_argument);

protected:
	virtual void append_data(std::ostream& os, const std::string& delimiter) const override;

private:
	optional<double> temperature; // water temperature
	optional<char> unit; // unit degrees, C:celcius

public:
	decltype(temperature) get_temperature() const { return temperature; }
	decltype(unit) get_unit() const { return unit; }
};

}

#endif
