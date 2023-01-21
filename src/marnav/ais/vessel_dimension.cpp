#include <marnav/ais/vessel_dimension.hpp>
#include <stdexcept>

namespace marnav::ais
{
vessel_dimension::vessel_dimension(units::meters to_bow, units::meters to_stern,
	units::meters to_port, units::meters to_starboard)
{
	set_to_bow(to_bow);
	set_to_stern(to_stern);
	set_to_port(to_port);
	set_to_starboard(to_starboard);
}

units::meters vessel_dimension::length() const noexcept
{
	return get_to_bow() + get_to_stern();
}

units::meters vessel_dimension::width() const noexcept
{
	return get_to_port() + get_to_starboard();
}

units::meters vessel_dimension::get_to_bow() const noexcept
{
	return units::meters(to_bow_);
}

units::meters vessel_dimension::get_to_stern() const noexcept
{
	return units::meters(to_stern_);
}

units::meters vessel_dimension::get_to_port() const noexcept
{
	return units::meters(to_port_);
}

units::meters vessel_dimension::get_to_starboard() const noexcept
{
	return units::meters(to_starboard_);
}

void vessel_dimension::set_to_bow(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"length less than zero"};
	to_bow_ = math::float_cast<decltype(to_bow_)>(round(t.get<units::meters>()).value());
}

void vessel_dimension::set_to_stern(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"length less than zero"};
	to_stern_ = math::float_cast<decltype(to_stern_)>(round(t.get<units::meters>()).value());
}

void vessel_dimension::set_to_port(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"length less than zero"};
	to_port_ = math::float_cast<decltype(to_port_)>(round(t.get<units::meters>()).value());
}

void vessel_dimension::set_to_starboard(units::length t)
{
	if (t.value() < 0.0)
		throw std::invalid_argument{"length less than zero"};
	to_starboard_
		= math::float_cast<decltype(to_starboard_)>(round(t.get<units::meters>()).value());
}
}
