#include <marnav/nmea/vtg.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
constexpr sentence_id vtg::ID;
constexpr const char * vtg::TAG;

vtg::vtg()
	: sentence(ID, TAG, talker_id::global_positioning_system)
{
}

vtg::vtg(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	// before and after NMEA 2.3
	const auto size = std::distance(first, last);
	if ((size < 8) || (size > 9))
		throw std::invalid_argument{"invalid number of fields in vtg"};

	read(*(first + 0), track_true_);
	read(*(first + 1), type_true_);
	read(*(first + 2), track_magn_);
	read(*(first + 3), type_magn_);
	read(*(first + 4), speed_kn_);
	read(*(first + 5), speed_kn_unit_);
	read(*(first + 6), speed_kmh_);
	read(*(first + 7), speed_kmh_unit_);

	// NMEA 2.3 or newer
	if (size > 8)
		read(*(first + 8), mode_ind_);
}

void vtg::set_speed_kn(double t) noexcept
{
	speed_kn_ = t;
	speed_kn_unit_ = unit::velocity::knot;
}

void vtg::set_speed_kmh(double t) noexcept
{
	speed_kmh_ = t;
	speed_kmh_unit_ = unit::velocity::kmh;
}

void vtg::set_track_magn(double t) noexcept
{
	track_magn_ = t;
	type_magn_ = reference::MAGNETIC;
}

void vtg::set_track_true(double t) noexcept
{
	track_true_ = t;
	type_true_ = reference::TRUE;
}

void vtg::append_data_to(std::string & s) const
{
	append(s, to_string(track_true_));
	append(s, to_string(type_true_));
	append(s, to_string(track_magn_));
	append(s, to_string(type_magn_));
	append(s, to_string(speed_kn_));
	append(s, to_string(speed_kn_unit_));
	append(s, to_string(speed_kmh_));
	append(s, to_string(speed_kmh_unit_));
	append(s, to_string(mode_ind_));
}
}
}
