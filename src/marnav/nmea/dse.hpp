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
/// @endcode
///
/// Field Number:
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
