#include "checks.hpp"
#include "constants.hpp"
#include <algorithm>
#include <sstream>

namespace marnav
{
namespace nmea
{

/// Checks the validity of the specified waypoint ID.
///
/// @param[in] id The waypoint ID to check.
///
/// @exception std::invalid_argument The waypoint ID is invalid.
void check_waypoint_id(const std::string & id) throw(std::invalid_argument)
{
	if (id.size() > 8)
		throw std::invalid_argument{"string size to large, only 8 characters allowed for id"};
}

/// Checks the value agains a list of possible values.
///
/// @param[in] value Value to check.
/// @param[in] options Possible values to check against.
/// @param[in] name Optional name of the value to check. This name will be mentioned
///   in thrown exception, if the value is invalid.
///
/// @exception std::invalid_argument The value is not listed in the options.
void check_value(char value, std::initializer_list<char> options, const char * name) throw(
	std::invalid_argument)
{
	using namespace std;
	if (find_if(begin(options), end(options), [value](char opt) { return value == opt; })
		== end(options)) {
		ostringstream os;
		os << "invalid argument, value '" << value << "' not in options:{";
		for (auto const & opt : options)
			os << " " << opt;
		os << " }";
		if (name)
			os << " for '" << name << "'";
		throw invalid_argument{os.str()};
	}
}

void check_status(char value, const char * name) throw(std::invalid_argument)
{
	check_value(value, {status::OK, status::WARNING}, name);
}

void check_status(const utils::optional<char> & value, const char * name) throw(
	std::invalid_argument)
{
	if (value)
		check_status(value.value(), name);
}
}
}
