#ifndef MARNAV_NMEA_ROUTE_HPP
#define MARNAV_NMEA_ROUTE_HPP

#include <string>

namespace marnav
{
namespace nmea
{
/// This represents a route ID. They must be at least 1 character,
/// but can only be 8 long.
///
class route
{
public:
	using value_type = std::string;
	using size_type = value_type::size_type;

	/// default constructed, invalid route.
	route() {}

	explicit route(const std::string & id);

	route(const route &) = default;
	route & operator=(const route &) = default;

	route(route &&) = default;
	route & operator=(route &&) = default;

	value_type get() const { return id_; }
	operator value_type() const { return id_; }

	const char * c_str() const { return id_.c_str(); }

	size_type size() const { return id_.size(); }
	bool empty() const { return id_.empty(); }

private:
	value_type id_;
};
}
}

#endif
