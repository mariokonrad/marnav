#ifndef MARNAV__NMEA__VDO__HPP
#define MARNAV__NMEA__VDO__HPP

#include <marnav/nmea/vdm.hpp>

#include <marnav/marnav_export.h>

namespace marnav
{
namespace nmea
{
/// @brief VDO - AIS VHF Data-Link Own-Vessel Report
///
/// This sentence is basically the same as marnav::nmea::vdm, it just indicates the source
/// of the information, not the information itself.
///
class MARNAV_EXPORT vdo : public vdm
{
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::VDO;
	constexpr static const char * TAG = "VDO";

	vdo();
	vdo(const vdo &) = default;
	vdo & operator=(const vdo &) = default;
	vdo(vdo &&) = default;
	vdo & operator=(vdo &&) = default;

protected:
	vdo(talker talk, fields::const_iterator first, fields::const_iterator last);
};
}
}

#endif
