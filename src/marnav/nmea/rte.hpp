#ifndef __NMEA__RTE__HPP__
#define __NMEA__RTE__HPP__

#include "sentence.hpp"
#include <marnav/utils/optional.hpp>

namespace marnav
{
namespace nmea
{

class rte : public sentence
{
public:
	constexpr static const sentence_id ID = sentence_id::RTE;

	rte();
	rte(const rte &) = default;
	rte & operator=(const rte &) = default;

	static std::unique_ptr<sentence> parse(const std::string & talker,
		const std::vector<std::string> & fields) throw(std::invalid_argument);

protected:
	virtual std::vector<std::string> get_data() const override;

private:
	utils::optional<uint32_t> n_messages;
	utils::optional<uint32_t> message_number;
	utils::optional<char> message_mode; // C:complete route, W:working route
	utils::optional<std::string> waypoint_id[10]; // names or numbers of the active route

public:
	decltype(n_messages) get_n_messages() const { return n_messages; }
	decltype(message_number) get_message_number() const { return message_number; }
	decltype(message_mode) get_message_mode() const { return message_mode; }
	utils::optional<std::string> get_waypoint_id(int index) const;

	void set_n_messages(uint32_t t) { n_messages = t; }
	void set_message_number(uint32_t t) { message_number = t; }
	void set_message_mode(char t) { message_mode = t; }
	void set_waypoint_id(int index, const std::string & id);
};
}
}

#endif
