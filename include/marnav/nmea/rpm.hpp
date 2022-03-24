#ifndef MARNAV_NMEA_RPM_HPP
#define MARNAV_NMEA_RPM_HPP

#include <marnav/nmea/sentence.hpp>
#include <optional>

namespace marnav
{
namespace nmea
{
/// @brief RPM - Revolutions
///
/// @code
///        1 2 3   4   5 6
///        | | |   |   | |
/// $--RPM,a,x,x.x,x.x,A*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Source, S = Shaft, E = Engine
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
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::RPM;
	constexpr static const char * TAG = "RPM";

	enum class source_id : char {
		shaft, ///< NMEA representation: 'S'
		engine, ///< NMEA representation: 'E'
	};

	rpm();
	rpm(const rpm &) = default;
	rpm & operator=(const rpm &) = default;
	rpm(rpm &&) = default;
	rpm & operator=(rpm &&) = default;

protected:
	rpm(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	std::optional<source_id> source_;
	std::optional<uint32_t> source_number_;
	std::optional<double> revolutions_;
	std::optional<double> propeller_pitch_;
	std::optional<status> data_valid_;

public:
	std::optional<source_id> get_source() const { return source_; }
	std::optional<uint32_t> get_source_number() const { return source_number_; }
	std::optional<double> get_revolutions() const { return revolutions_; }
	std::optional<double> get_propeller_pitch() const { return propeller_pitch_; }
	std::optional<status> get_data_valid() const { return data_valid_; }

	void set_source(source_id id, uint32_t num);
	void set_revolutions(double t) noexcept { revolutions_ = t; }
	void set_propeller_pitch(double t) noexcept { propeller_pitch_ = t; }
	void set_data_valid(status t) noexcept { data_valid_ = t; }
};

std::string to_string(rpm::source_id value);
}
}

#endif
