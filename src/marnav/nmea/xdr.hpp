#ifndef __NMEA__XDR__HPP__
#define __NMEA__XDR__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief XDR - Transducer Measurement
///
/// @code
///        1 2   3 4
///        | |   | |
/// $--XDR,a,x.x,a,c--c, ..... *hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Transducer Type
/// 2. Measurement Data
/// 3. Units of measurement
/// 4. Name of transducer
///
/// There may be any number of quadruplets like this, each describing a sensor.
/// The last field will be a checksum as usual.
///
class xdr : public sentence
{
public:
	struct transducer_info {
		char transducer_type;
		double measurement_data;
		char units_of_measurement;
		std::string name;
	};

	constexpr static const sentence_id ID = sentence_id::XDR;
	constexpr static const char * TAG = "XDR";

	xdr();
	xdr(const xdr &) = default;
	xdr & operator=(const xdr &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	constexpr static const int MAX_TRANSDUCER_INFO = 10;

	std::array<utils::optional<transducer_info>, MAX_TRANSDUCER_INFO> transducer_data;

	void check_index(int index) const throw(std::out_of_range);

public:
	utils::optional<transducer_info> get_info(int index) const throw(std::out_of_range);

	void set_info(int index, const transducer_info & info) throw(std::out_of_range);
};
}
}

#endif

