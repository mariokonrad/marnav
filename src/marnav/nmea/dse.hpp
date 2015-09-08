#ifndef __NMEA__DSE__HPP__
#define __NMEA__DSE__HPP__

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

	static std::unique_ptr<sentence> parse(
		const std::string & talker, const std::vector<std::string> & fields);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	uint32_t number_of_messages;
	uint32_t sentence_number;
	query_flag flag;
	uint64_t address;

public:
	NMEA_GETTER(number_of_messages)
	NMEA_GETTER(sentence_number)
	NMEA_GETTER(flag)
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
