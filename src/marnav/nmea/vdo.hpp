#ifndef __NMEA__VDO__HPP__
#define __NMEA__VDO__HPP__

#include "vdm.hpp"

namespace marnav
{
namespace nmea
{

/// This sentence is basically the same as VDM, it just indicates the source
/// of the information, not the information itself.
class vdo : public vdm
{
public:
	constexpr static const sentence_id ID = sentence_id::VDO;
	constexpr static const char * TAG = "VDO";

	vdo();
	vdo(const vdo &) = default;
	vdo & operator=(const vdo &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);
};
}
}

#endif
