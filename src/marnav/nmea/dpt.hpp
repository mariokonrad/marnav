#ifndef __NMEA__DPT__HPP__
#define __NMEA__DPT__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief DPT - Depth of Water
///
/// Water depth relative to the transducer and offset of the measuring transducer.
///
/// @code
///        1   2
///        |   |
/// $--DPT,x.x,x.x*hh<CR><LF>
/// @endcode
///
/// Field Number:
///  1. Depth meters
///  2. Offset from transducer
///     - positive value means distance from tansducer to water line
///     - negative value means distance from transducer to keel
///
class dpt : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::DPT;
	constexpr static const char * TAG = "DPT";

	dpt();
	dpt(const dpt &) = default;
	dpt & operator=(const dpt &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<double> depth_meter;
	utils::optional<double> transducer_offset;

public:
	NMEA_GETTER(depth_meter)
	NMEA_GETTER(transducer_offset)

	void set_depth_meter(double t) { depth_meter = t; }
	void set_transducer_offset(double t) { transducer_offset = t; }
};
}
}

#endif
