#ifndef __NMEA__DSC__HPP__
#define __NMEA__DSC__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

/// @brief DSC - Mean Temperature of Water
///
/// @code
/// @endcode
///
/// Field Number:
///
class dsc : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::DSC;
	constexpr static const char * TAG = "DSC";

	dsc();
	dsc(const dsc &) = default;
	dsc & operator=(const dsc &) = default;

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
