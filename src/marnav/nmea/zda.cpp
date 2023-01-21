#include <marnav/nmea/zda.hpp>
#include <marnav/nmea/io.hpp>
#include <stdexcept>

namespace marnav::nmea
{
constexpr sentence_id zda::ID;
constexpr const char * zda::TAG;

zda::zda()
	: sentence(ID, TAG, talker::global_positioning_system)
{
}

zda::zda(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 6)
		throw std::invalid_argument{"invalid number of fields in zda"};

	std::optional<uint32_t> d;
	std::optional<uint32_t> m;
	std::optional<uint32_t> y;

	read(*(first + 0), time_utc_);
	read(*(first + 1), d);
	read(*(first + 2), m);
	read(*(first + 3), y);
	read(*(first + 4), local_zone_hours_);
	read(*(first + 5), local_zone_minutes_);

	if (d && m && y)
		date_ = nmea::date{*y, to_month(*m), *d};
}

void zda::append_data_to(std::string & s, const version &) const
{
	std::optional<uint32_t> d;
	std::optional<uint32_t> m;
	std::optional<uint32_t> y;

	if (date_) {
		d = date_->day();
		m = to_numeric(date_->mon());
		y = date_->year();
	}

	append(s, to_string(time_utc_));
	append(s, format(d, 2));
	append(s, format(m, 2));
	append(s, format(y, 4));
	append(s, format(local_zone_hours_, 2));
	append(s, format(local_zone_minutes_, 2));
}
}
