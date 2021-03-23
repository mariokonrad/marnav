#include <marnav/nmea/vtg.hpp>
#include <marnav/nmea/io.hpp>
#include "checks.hpp"

namespace marnav
{
namespace nmea
{
constexpr sentence_id vtg::ID;
constexpr const char * vtg::TAG;

vtg::vtg()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

vtg::vtg(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	// before and after NMEA 2.3
	const auto size = std::distance(first, last);
	if ((size < 8) || (size > 9))
		throw std::invalid_argument{"invalid number of fields in vtg"};

	std::optional<reference> track_true_ref;
	std::optional<reference> track_magn_ref;
	std::optional<unit::velocity> speed_kn_unit;
	std::optional<unit::velocity> speed_kmh_unit;

	read(*(first + 0), track_true_);
	read(*(first + 1), track_true_ref);
	read(*(first + 2), track_magn_);
	read(*(first + 3), track_magn_ref);
	read(*(first + 4), speed_kn_);
	read(*(first + 5), speed_kn_unit);
	read(*(first + 6), speed_kmh_);
	read(*(first + 7), speed_kmh_unit);

	// NMEA 2.3 or newer
	if (size > 8)
		read(*(first + 8), mode_ind_);

	check_value(track_true_ref, {reference::TRUE}, "track true ref");
	check_value(track_magn_ref, {reference::MAGNETIC}, "track mangetic ref");
	check_value(speed_kn_unit, {unit::velocity::knot}, "speed_kn_unit");
	check_value(speed_kmh_unit, {unit::velocity::kmh}, "speed_kmh_unit");
}

void vtg::set_speed_kn(units::velocity t) noexcept
{
	speed_kn_ = t.get<units::knots>();
}

void vtg::set_speed_kmh(units::velocity t) noexcept
{
	speed_kmh_ = t.get<units::kilometers_per_hour>();
}

void vtg::set_track_magn(double t) noexcept
{
	track_magn_ = t;
}

void vtg::set_track_true(double t) noexcept
{
	track_true_ = t;
}

std::optional<units::knots> vtg::get_speed_kn() const
{
	if (!speed_kn_)
		return {};
	return {*speed_kn_};
}

std::optional<units::kilometers_per_hour> vtg::get_speed_kmh() const
{
	if (!speed_kmh_)
		return {};
	return {*speed_kmh_};
}

void vtg::append_data_to(std::string & s) const
{
	append(s, to_string(track_true_));
	append(s, to_string_if(reference::TRUE, track_true_));
	append(s, to_string(track_magn_));
	append(s, to_string_if(reference::MAGNETIC, track_magn_));
	append(s, to_string(speed_kn_));
	append(s, to_string_if(unit::velocity::knot, speed_kn_));
	append(s, to_string(speed_kmh_));
	append(s, to_string_if(unit::velocity::kmh, speed_kmh_));
	append(s, to_string(mode_ind_));
}
}
}
