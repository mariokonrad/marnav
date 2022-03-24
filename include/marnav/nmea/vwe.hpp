#ifndef MARNAV_NMEA_VWE_HPP
#define MARNAV_NMEA_VWE_HPP

#include <marnav/nmea/sentence.hpp>

namespace marnav
{
namespace nmea
{
/// @brief VWE - Wind Track Efficiency
///
/// @code
///        1
///        |
/// $--VWE,x.x*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Efficiency in Percent
///
class vwe : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::VWE;
	constexpr static const char * TAG = "VWE";

	vwe();
	vwe(const vwe &) = default;
	vwe & operator=(const vwe &) = default;
	vwe(vwe &&) = default;
	vwe & operator=(vwe &&) = default;

protected:
	vwe(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	double efficiency_ = 0.0;

public:
	double get_efficiency() const { return efficiency_; }

	void set_efficiency(double t);
};
}
}

#endif
