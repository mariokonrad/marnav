#ifndef MARNAV_NMEA_HDM_HPP
#define MARNAV_NMEA_HDM_HPP

#include <marnav/nmea/sentence.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
/// @brief HDM - Heading - Magnetic
///
/// Vessel heading in degrees with respect to magnetic north produced by any device
/// or system producing magnetic heading.
///
/// @note As of 2009, this sentence is designaged 'obsolete'. Older devices may
///   support them, therefore it makes sense to implement it.
///
/// @code
///        1   2
///        |   |
/// $--HDM,x.x,M*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Heading Degrees magnetic
/// 2. Heading Degrees magnetic reference
///    - M = magnetic
///
class hdm : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::HDM;
	constexpr static const char * TAG = "HDM";

	hdm();
	hdm(const hdm &) = default;
	hdm & operator=(const hdm &) = default;
	hdm(hdm &&) = default;
	hdm & operator=(hdm &&) = default;

protected:
	hdm(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<double> heading_; // magnetic sensor heading in deg
	std::optional<reference> heading_mag_;

public:
	std::optional<double> get_heading() const { return heading_; }
	std::optional<reference> get_heading_mag() const { return heading_mag_; }

	void set_heading(double t) noexcept;
};
}
}

#endif
