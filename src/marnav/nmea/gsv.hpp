#ifndef __NMEA__GSV__HPP__
#define __NMEA__GSV__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>
#include <array>

namespace marnav
{
namespace nmea
{

class gsv : public sentence
{
public:
	struct satellite_info {
		uint32_t id;
		uint32_t elevation;
		uint32_t azimuth; // azimuth against true
		uint32_t snr;
	};

	constexpr static const sentence_id ID = sentence_id::GSV;

	gsv();
	gsv(const gsv &) = default;
	gsv & operator=(const gsv &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<uint32_t> n_messages;
	utils::optional<uint32_t> message_number;
	utils::optional<uint32_t> n_satellites_in_view;
	std::array<utils::optional<satellite_info>, 4> sat;

	void check_index(int index) const throw(std::out_of_range);

public:
	decltype(n_messages) get_n_messages() const { return n_messages; }
	decltype(message_number) get_message_number() const { return message_number; }
	decltype(n_satellites_in_view) get_n_satellites_in_view() const
	{
		return n_satellites_in_view;
	}
	utils::optional<satellite_info> get_sat(int index) const throw(std::out_of_range);

	void set_n_messages(uint32_t t) { n_messages = t; }
	void set_message_number(uint32_t t) { message_number = t; }
	void set_n_satellites_in_view(uint32_t t) { n_satellites_in_view = t; }
	void set_sat(int index, const satellite_info & info) throw(std::out_of_range);
};
}
}

#endif
