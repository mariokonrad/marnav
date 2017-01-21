#include "message.hpp"

namespace marnav
{
namespace ais
{
std::string trim_ais_string(const std::string & s)
{
	return s.substr(0, s.find_first_of("@"));
}
}
}
