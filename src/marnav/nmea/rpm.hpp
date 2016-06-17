#ifndef __NMEA__RPM__HPP__
#define __NMEA__RPM__HPP__

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{
MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(rpm)

/// @brief RPM - Revolutions
///
/// @code
///        1 2 3   4   5 6
///        | | |   |   | |
/// $--RPM,a,x,x.x,x.x,A*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Sourse, S = Shaft, E = Engine
///    - S = Shaft
///    - E = Engine
/// 2. Engine or shaft number
/// 3. Speed, Revolutions per minute
/// 4. Propeller pitch, % of maximum, "-" means astern
/// 5. Status
///    - A = data is valid
///
class rpm : public sentence
{
	MARNAV_NMEA_SENTENCE_FRIENDS(rpm)

public:
	constexpr static const sentence_id ID = sentence_id::RPM;
	constexpr static const char * TAG = "RPM";

	enum class source_id : char {
		shaft, ///< NMEA representation: 'S'
		engine, ///< NMEA representation: 'E'
	};

	virtual ~rpm() {}

	rpm();
	rpm(const rpm &) = default;
	rpm & operator=(const rpm &) = default;

protected:
	rpm(const std::string & talker, fields::const_iterator first, fields::const_iterator last);
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<source_id> source;
	utils::optional<uint32_t> source_number;
	utils::optional<double> revolutions;
	utils::optional<double> propeller_pitch;
	utils::optional<status> data_valid;

public:
	NMEA_GETTER(source)
	NMEA_GETTER(source_number)
	NMEA_GETTER(revolutions)
	NMEA_GETTER(propeller_pitch)
	NMEA_GETTER(data_valid)

	void set_source(source_id id, uint32_t num);
	void set_revolutions(double t) noexcept { revolutions = t; }
	void set_propeller_pitch(double t) noexcept { propeller_pitch = t; }
	void set_data_valid(status t) noexcept { data_valid = t; }
};

std::string to_string(rpm::source_id value);
}
}

#endif
