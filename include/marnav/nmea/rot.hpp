#ifndef MARNAV_NMEA_ROT_HPP
#define MARNAV_NMEA_ROT_HPP

#include <marnav/nmea/sentence.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
/// @brief ROT - Rate Of Turn
///
/// @code
///        1   2
///        |   |
/// $--ROT,x.x,A*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Rate Of Turn, degrees per minute, "-" means bow turns to port
/// 2. Status
///    - A = data is valid
///    - V = invalid
///
class rot : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::ROT;
	constexpr static const char * TAG = "ROT";

	rot();
	rot(const rot &) = default;
	rot & operator=(const rot &) = default;
	rot(rot &&) = default;
	rot & operator=(rot &&) = default;

protected:
	rot(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<double> deg_per_minute_;
	std::optional<status> data_valid_;

public:
	std::optional<double> get_deg_per_minute() const { return deg_per_minute_; }
	std::optional<status> get_data_valid() const { return data_valid_; }

	void set_deg_per_minute(double t) noexcept { deg_per_minute_ = t; }
	void set_data_valid(status t) noexcept { data_valid_ = t; }
};
}
}

#endif
