#ifndef MARNAV__NMEA__XDR__HPP
#define MARNAV__NMEA__XDR__HPP

#include <marnav/nmea/sentence.hpp>
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
	friend class detail::factory;

public:
	struct transducer_info {
		char transducer_type;
		double measurement_data;
		char units_of_measurement;
		std::string name;
	};

	constexpr static sentence_id ID = sentence_id::XDR;
	constexpr static const char * TAG = "XDR";

	constexpr static int max_transducer_info = 10;

	xdr();
	xdr(const xdr &) = default;
	xdr & operator=(const xdr &) = default;
	xdr(xdr &&) = default;
	xdr & operator=(xdr &&) = default;

protected:
	xdr(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	std::array<utils::optional<transducer_info>, max_transducer_info> transducer_data_;

	void check_index(int index) const;

public:
	utils::optional<transducer_info> get_info(int index) const;

	void set_info(int index, const transducer_info & info);
};
}
}

#endif
