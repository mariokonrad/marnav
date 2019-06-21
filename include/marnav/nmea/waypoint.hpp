#ifndef MARNAV__NMEA__WAYPOINT__HPP
#define MARNAV__NMEA__WAYPOINT__HPP

#include <string>

namespace marnav
{
namespace nmea
{
/// This represents a waypoint ID. They must be at least 1 character,
/// but can only be 8 long.
///
class waypoint
{
public:
	using value_type = std::string;
	using size_type = value_type::size_type;

	/// default constructed, invalid waypoint.
	waypoint() {}

	explicit waypoint(const std::string & id);

	waypoint(const waypoint &) = default;
	waypoint & operator=(const waypoint &) = default;

	waypoint(waypoint &&) = default;
	waypoint & operator=(waypoint &&) = default;

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
