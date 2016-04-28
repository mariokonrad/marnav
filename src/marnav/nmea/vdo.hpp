#ifndef __NMEA__VDO__HPP__
#define __NMEA__VDO__HPP__

#include <marnav/nmea/vdm.hpp>

namespace marnav
{
namespace nmea
{

/// @brief VDO - AIS VHF Data-Link Own-Vessel Report
///
/// This sentence is basically the same as marnav::nmea::vdm, it just indicates the source
/// of the information, not the information itself.
///
class vdo : public vdm
{
public:
	constexpr static const sentence_id ID = sentence_id::VDO;
	constexpr static const char * TAG = "VDO";

	vdo();
	vdo(const vdo &) = default;
	vdo & operator=(const vdo &) = default;

	static std::unique_ptr<sentence> parse(
		const std::string & talker, fields::const_iterator first, fields::const_iterator last);
};
}
}

#endif
