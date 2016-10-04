#ifndef __NMEA__TFI__HPP__
#define __NMEA__TFI__HPP__

#include <array>
#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(tfi)

/// @brief TFI - Trawl Filling Indicator
///
/// @code
///        1 2 3
///        | | |
/// $--TFI,x,y,z*hh<CR><LF>
/// @endcode
///
/// Field number:
/// 1. Catch sensor #1 (0 = off, 1 = on, 2 = no answer)
/// 2. Catch sensor #2 (0 = off, 1 = on, 2 = no answer)
/// 3. Catch sensor #3 (0 = off, 1 = on, 2 = no answer)
///
class tfi : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(tfi)

public:
	constexpr static const sentence_id ID = sentence_id::TFI;
	constexpr static const char * TAG = "TFI";

	static constexpr const int num_sensors = 3;

	enum class state : uint32_t {
		off, ///< NMEA representation: 0
		on, ///< NMEA representation: 1
		no_answer ///< NMEA representation: 2
	};

	tfi();
	tfi(const tfi &) = default;
	tfi & operator=(const tfi &) = default;
	tfi(tfi &&) = default;
	tfi & operator=(tfi &&) = default;

protected:
	tfi(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	std::array<state, num_sensors> sensors;

	void check_index(int index) const;

public:
	state get_sensor(int index) const;

	void set_sensor(int index, state t);
};

std::string to_string(tfi::state value);
}
}

#endif
