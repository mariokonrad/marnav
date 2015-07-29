#ifndef __NMEA__DSE__HPP__
#define __NMEA__DSE__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief DSE - Mean Temperature of Water
///
/// @code
///        1 2 3 4         5  6
///        | | | |         |  |
/// $--DSE,x,x,a,xxxxxxxxx,xx,c--c,...,xx,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Total number of messages
/// 2. Sentence number
/// 3. Query/Reply Flag
/// 4. MMSI
/// 5. Data set, code
/// 6. Data set, data
///
/// There may be a variable number of data sets (code, data)
///
/// @todo IMPLEMENTATION
///
class dse : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::DSE;
	constexpr static const char * TAG = "DSE";

	dse();
	dse(const dse &) = default;
	dse & operator=(const dse &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:

public:
};
}
}

#endif
