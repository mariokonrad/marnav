#ifndef __NMEA__VDO__HPP__
#define __NMEA__VDO__HPP__

#include <marnav/nmea/vdm.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(vdo)

/// @brief VDO - AIS VHF Data-Link Own-Vessel Report
///
/// This sentence is basically the same as marnav::nmea::vdm, it just indicates the source
/// of the information, not the information itself.
///
class vdo : public vdm
{
	MARNAV_NMEA_SENTENCE_FRIENDS(vdo)

public:
	constexpr static const sentence_id ID = sentence_id::VDO;
	constexpr static const char * TAG = "VDO";

	virtual ~vdo() {}

	vdo();
	vdo(const vdo &) = default;
	vdo & operator=(const vdo &) = default;

protected:
	vdo(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
};
}
}

#endif
