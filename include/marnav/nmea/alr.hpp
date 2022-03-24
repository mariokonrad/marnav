#ifndef MARNAV_NMEA_ALR_HPP
#define MARNAV_NMEA_ALR_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/time.hpp>

namespace marnav
{
namespace nmea
{
/// @brief ALR - Set Alarm State
///
/// @code
///        1         2   3 4 5
///        |         |   | | |
/// $--ALR,hhmmss.ss,xxx,a,a,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Time UTC
/// 2. Alarm number
/// 3. Alarm condition
///    - A = Exceeded threshold
///    - V = Not exceeded threshold
/// 4. Alarm acknowledge state
///    - A = Acknoledged
///    - V = Unacknowledged
/// 5. Alarm text
///
class alr : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::ALR;
	constexpr static const char * TAG = "ALR";

	/// Alarm condition
	enum class condition : char {
		threshold_exceeded, ///< NMEA representation: 'A'
		threshold_not_exceeded, ///< NMEA representation: 'V'
	};

	/// Alarm acknowledge state
	enum class acknowledge : char {
		acknowledged, ///< NMEA representation: 'A'
		not_acknowledged, ///< NMEA representation: 'V'
	};

	alr();
	alr(talker talk);
	alr(const alr &) = default;
	alr & operator=(const alr &) = default;
	alr(alr &&) = default;
	alr & operator=(alr &&) = default;

protected:
	alr(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &, const version &) const override;

private:
	nmea::time time_utc_;
	uint32_t number_ = 0u;
	condition condition_ = condition::threshold_exceeded;
	acknowledge acknowledge_ = acknowledge::acknowledged;
	std::string text_;

public:
	nmea::time get_time_utc() const { return time_utc_; }
	uint32_t get_number() const { return number_; }
	condition get_condition() const { return condition_; }
	acknowledge get_acknowledge() const { return acknowledge_; }
	const std::string & get_text() const { return text_; }

	void set_time_utc(const nmea::time & t) { time_utc_ = t; }
	void set_number(uint32_t n) { number_ = n; }
	void set_condition(condition c) { condition_ = c; }
	void set_acknowledge(acknowledge a) { acknowledge_ = a; }
	void set_text(const std::string & t);
};

std::string to_string(alr::condition t);
std::string to_string(alr::acknowledge t);

std::string to_name(alr::condition t);
std::string to_name(alr::acknowledge t);
}
}

#endif
