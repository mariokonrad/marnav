#include <marnav/nmea/hdg.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav::nmea
{
constexpr sentence_id hdg::ID;
constexpr const char * hdg::TAG;

hdg::hdg()
	: sentence(ID, TAG, talker::magnetic_compass)
{
}

hdg::hdg(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in hdg"};

	read(*(first + 0), heading_);
	read(*(first + 1), magn_dev_);
	read(*(first + 2), magn_dev_hem_);
	read(*(first + 3), magn_var_);
	read(*(first + 4), magn_var_hem_);
}

void hdg::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(heading_));
	append(s, to_string(magn_dev_));
	append(s, to_string(magn_dev_hem_));
	append(s, to_string(magn_var_));
	append(s, to_string(magn_var_hem_));
}

std::optional<magnetic> hdg::get_magn_dev() const
{
	return (magn_dev_ && magn_dev_hem_) ? magnetic(*magn_dev_, *magn_dev_hem_)
										: std::optional<magnetic>{};
}

std::optional<magnetic> hdg::get_magn_var() const
{
	return (magn_var_ && magn_var_hem_) ? magnetic(*magn_var_, *magn_var_hem_)
										: std::optional<magnetic>{};
}

void hdg::set_magn_dev(const magnetic & t)
{
	magn_dev_ = t.angle();
	magn_dev_hem_ = t.hemisphere();
}

void hdg::set_magn_var(const magnetic & t)
{
	magn_var_ = t.angle();
	magn_var_hem_ = t.hemisphere();
}
}
