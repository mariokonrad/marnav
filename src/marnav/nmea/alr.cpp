#include <marnav/nmea/alr.hpp>
#include <marnav/nmea/io.hpp>

namespace marnav
{
namespace nmea
{
/// @cond DEV
namespace
{
static alr::condition condition_mapping(
	typename std::underlying_type<alr::condition>::type value)
{
	switch (value) {
		case 'A':
			return alr::condition::threshold_exceeded;
		case 'V':
			return alr::condition::threshold_not_exceeded;
	}
	throw std::invalid_argument{"invalid value for conversion to alr::condition"};
}

static alr::acknowledge acknowledge_mapping(
	typename std::underlying_type<alr::acknowledge>::type value)
{
	switch (value) {
		case 'A':
			return alr::acknowledge::acknowledged;
		case 'V':
			return alr::acknowledge::not_acknowledged;
	}
	throw std::invalid_argument{"invalid value for conversion to alr::acknowledge"};
}
}
/// @endcond

std::string to_string(alr::condition t)
{
	switch (t) {
		case alr::condition::threshold_exceeded:
			return "A";
		case alr::condition::threshold_not_exceeded:
			return "V";
	}
	throw std::invalid_argument{"invalid value for conversion from alr::condition"};
}

std::string to_string(alr::acknowledge t)
{
	switch (t) {
		case alr::acknowledge::acknowledged:
			return "A";
		case alr::acknowledge::not_acknowledged:
			return "V";
	}
	throw std::invalid_argument{"invalid value for conversion from alr::acknowledge"};
}

std::string to_name(alr::condition t)
{
	switch (t) {
		case alr::condition::threshold_exceeded:
			return "Threshold Exceeded";
		case alr::condition::threshold_not_exceeded:
			return "Threshold Not Exceeded";
	}
	throw std::invalid_argument{"invalid value for conversion from alr::condition"};
}

std::string to_name(alr::acknowledge t)
{
	switch (t) {
		case alr::acknowledge::acknowledged:
			return "Acknowledged";
		case alr::acknowledge::not_acknowledged:
			return "Not Acknowledged";
	}
	throw std::invalid_argument{"invalid value for conversion from alr::acknowledge"};
}

constexpr sentence_id alr::ID;
constexpr const char * alr::TAG;

alr::alr()
	: sentence(ID, TAG, talker::integrated_instrumentation)
{
}

alr::alr(talker talk)
	: sentence(ID, TAG, talk)
{
}

alr::alr(talker talk, fields::const_iterator first, fields::const_iterator last)
	: sentence(ID, TAG, talk)
{
	if (std::distance(first, last) != 5)
		throw std::invalid_argument{"invalid number of fields in alr"};

	read(*(first + 0), time_utc_);
	read(*(first + 1), number_);
	read(*(first + 2), condition_, condition_mapping);
	read(*(first + 3), acknowledge_, acknowledge_mapping);
	read(*(first + 4), text_);
}

void alr::append_data_to(std::string & s, const version &) const
{
	append(s, to_string(time_utc_));
	append(s, to_string(number_));
	append(s, to_string(condition_));
	append(s, to_string(acknowledge_));
	append(s, to_string(text_));
}

void alr::set_text(const std::string & t)
{
	// test size of string plus oder fields should not exceed the sentence max length
	if ((t.size() + 28u) > sentence::max_length)
		throw std::invalid_argument{"alarm text size too large in arl::set_text"};

	text_ = t;
}
}
}
