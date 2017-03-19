#ifndef MARNAV__NMEA__DSE__HPP
#define MARNAV__NMEA__DSE__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav
{
namespace nmea
{
/// @brief DSE - Extended DSC
///
/// @note This class is @b EXPERIMENTAL
///
/// @code
///        1 2 3 4         5  6
///        | | | |         |  |
/// $--DSE,x,x,a,xxxxxxxxx,xx,c--c,...,xx,c--c*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1. Total number of messages
/// 2. Sentence number
/// 3. Query/Reply Flag
///    - Q = Query
///    - R = Reply
///    - A = ?
/// 4. Address (identical to DSC)
/// 5. Data set, code
/// 6. Data set, data
///
/// There may be a variable number of data sets (code, data)
///
/// @todo Implementation of data set fields
///
class dse : public sentence
{
	friend class detail::factory;

public:
	constexpr static const sentence_id ID = sentence_id::DSE;
	constexpr static const char * TAG = "DSE";

	enum class query_flag : char { query, reply, a };

	enum class code_id : uint32_t {
		enhanced_position_resolution, ///< 100
		source_and_data_of_position, ///< 101
		current_speed_of_vessel, ///< 102
		current_course_of_vessel, ///< 103
		additional_station_identification, ///< 104
		enhanced_geographic_area, ///< 105
		number_of_persons_on_board ///< 106
	};

	struct dataset {
		code_id code;
		std::string data;
	};

	dse();
	dse(const dse &) = default;
	dse & operator=(const dse &) = default;
	dse(dse &&) = default;
	dse & operator=(dse &&) = default;

protected:
	dse(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	uint32_t number_of_messages = 1;
	uint32_t sentence_number = 1;
	query_flag flag = query_flag::query;
	uint64_t address = 0;

public:
	decltype(number_of_messages) get_number_of_messages() const { return number_of_messages; }
	decltype(sentence_number) get_sentence_number() const { return sentence_number; }
	decltype(flag) get_flag() const { return flag; }
	utils::mmsi get_mmsi() const;

	void set_number_of_messages(uint32_t t) noexcept { number_of_messages = t; }
	void set_sentence_number(uint32_t t) noexcept { sentence_number = t; }
	void set_flag(query_flag t) noexcept { flag = t; }
	void set_mmsi(const utils::mmsi & t) noexcept;
};

std::string to_string(dse::query_flag value);
std::string to_string(dse::code_id value);
}
}

#endif
