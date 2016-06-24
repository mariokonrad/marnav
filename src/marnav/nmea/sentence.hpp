#ifndef __NMEA__SENTENCE__HPP__
#define __NMEA__SENTENCE__HPP__

#include <functional>
#include <memory>
#include <vector>
#include <string>
#include <marnav/nmea/constants.hpp>
#include <marnav/nmea/talker_id.hpp>
#include <marnav/nmea/sentence_id.hpp>
#include <marnav/nmea/detail.hpp>

namespace marnav
{
namespace nmea
{
/// @brief This is the base class for all sentences.
class sentence
{
public:
	/// Type for fields to process while reading data from raw sentences.
	using fields = std::vector<std::string>;

	/// This signature is used in all subclasses to parse data fields
	/// of a particular sentence.
	using parse_function = std::function<std::unique_ptr<sentence>(
		const std::string &, fields::const_iterator, fields::const_iterator)>;

	/// Maximum length of a NMEA sentence (raw format as string).
	constexpr static int max_length = 82;

	/// The start token of normal NMEA sentences.
	constexpr static char start_token = '$';

	/// The start token of AIS related NMEA sentences.
	constexpr static char start_token_ais = '!';

	/// The end token (right before the checksum) of all NMEA sentences.
	constexpr static char end_token = '*';

	sentence() = delete;

	virtual ~sentence() {}

	sentence_id id() const { return id_; }
	std::string tag() const { return tag_; }
	std::string talker() const { return talker_; }

	/// Sets the talker of the sentence.
	///
	/// @note All subclasses specify a default talker at construction.
	///   This method is used to override the default or to set the
	///   talker ID explicitly.
	void set_talker(const std::string & talker);

	friend std::string to_string(const sentence &);

protected:
	sentence(sentence_id id, const std::string & tag, const std::string & talker);
	virtual std::vector<std::string> get_data() const = 0;
	virtual char get_start_token() const { return start_token; }
	virtual char get_end_token() const { return end_token; }

private:
	const sentence_id id_;
	const std::string tag_;
	std::string talker_;
};

/// Helper function to parse a specific sentence.
template <class T>
std::unique_ptr<sentence> sentence_parse(const std::string & talker, const sentence::fields & f)
{
	return std::unique_ptr<T>(new T{talker, f.begin(), f.end()});
}

/// Creates the configured sentence object from the specified string.
/// If the string is invalid or describes a non-configured sentence,
/// an exception is thrown.
///
/// @note This function always checks the checksum and throws an
///   exception if not correct.
///
/// @tparam T The type of sentence to create. The type must be derived
///   from class sentence.
///
/// @param[in] s The raw NMEA sentence.
/// @return The initialized sentence derived object.
///
template <typename T> T create_sentence(const std::string & s)
{
	detail::create_sentence_base_class_check<T>();
	std::string talker;
	std::string tag;
	std::vector<std::string> fields;
	std::tie(talker, tag, fields) = detail::extract_sentence_information(s);
	// TODO: check (T::TAG == tag)? probably a bit too defensive...
	return T{talker, std::next(std::begin(fields)), std::prev(std::end(fields))};
}

/// Renders the specified sentence into a string.
///
/// If the sentence is invalid, the returning string will be empty.
std::string to_string(const sentence & s);

/// @cond DEV
namespace detail
{
/// Checks if the specified cast is valid, throws `bad_cast` if not.
/// If the pointer is `nullptr`, false returns.
template <class T> bool check_cast(const sentence * s)
{
	if (!s)
		return false;
	if (s->id() != T::ID)
		throw std::bad_cast{};
	return true;
}
}
/// @endcond

/// @{

/// Casts the specified sentence to the sentence given by the template parameter.
/// The object converted only if it is valid and of the correct type. It is not
/// possible to cast a sentence into a completley different one.
///
/// @note This function does not use 'dynamic_cast', therefore it does not
///   cast subclasses automatically. You will have to do checks and casts
///   explicitly.
///   This is considered a feature.
///
/// @param[in] s The sentence object to convert.
/// @retval nullptr The specified sentence is invalid.
/// @return The converted sentence.
/// @exception std::bad_cast The specified sentence has the wrong ID.
///
/// Examples:
/// @code
///   auto s = nmea::make_sentence("$IIMTW,9.5,C*2F");
///   auto mtw = nmea::sentence_cast<nmea::mtw>(s); // OK
/// @endcode
///
/// @code
///   auto s = nmea::make_sentence("$IIMTW,9.5,C*2F");
///   auto rmc = nmea::sentence_cast<nmea::rmc>(s); // Error, throws std::bad_cast
/// @endcode
template <class T> T * sentence_cast(sentence * s)
{
	return detail::check_cast<T>(s) ? static_cast<T *>(s) : nullptr;
}

/// const variant.
///
/// @see sentence_cast(sentence * s)
template <class T> const T * sentence_cast(const sentence * s)
{
	return detail::check_cast<T>(s) ? static_cast<const T *>(s) : nullptr;
}

/// `std::unique_ptr` variant. This is only for convenience. It is the same as:
/// @code
/// auto p = nmea::make_sentence("$IIMTW,9.5,C*2F");
/// auto q = nmea::sentence_cast<nmea::mtw>(p.get());
/// @endcode
///
/// @see sentence_cast(sentence * s)
template <class T> T * sentence_cast(std::unique_ptr<sentence> & s)
{
	return sentence_cast<T>(s.get());
}

/// `const std::unique_ptr` variant. This is only for convenience. It is the same as:
/// @code
/// const auto p = nmea::make_sentence("$IIMTW,9.5,C*2F");
/// auto q = nmea::sentence_cast<nmea::mtw>(p.get());
/// @endcode
///
/// @see sentence_cast(sentence * s)
template <class T> const T * sentence_cast(const std::unique_ptr<sentence> & s)
{
	return sentence_cast<const T>(s.get());
}

/// @}

/// @cond DEV

/// @brief This macro defines a getter method for NMEA sentence data.
///
/// Macros are avoided as far as possible, this one however improves readability.
/// All it does is declare and implement inline a getter method. Handy for
/// NMEA sentence member data.
///
#define NMEA_GETTER(attribute) \
	decltype(attribute) get_##attribute() const { return attribute; }

#define MARNAV_NMEA_SENTENCE_FRIENDS(s)                                                 \
	friend std::unique_ptr<sentence> detail::parse_##s(const std::string & talker,      \
		sentence::fields::const_iterator first, sentence::fields::const_iterator last); \
	template <class T>                                                                  \
	friend std::unique_ptr<sentence> sentence_parse(                                    \
		const std::string & talker, const sentence::fields & f);                        \
	template <typename T> friend T create_sentence(const std::string & s);

#define MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(s)                                      \
	namespace detail                                                                    \
	{                                                                                   \
	std::unique_ptr<sentence> parse_##s(const std::string & talker,                     \
		sentence::fields::const_iterator first, sentence::fields::const_iterator last); \
	}

#define MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(s)                                      \
	namespace detail                                                                   \
	{                                                                                  \
	std::unique_ptr<sentence> parse_##s(const std::string & talker,                    \
		sentence::fields::const_iterator first, sentence::fields::const_iterator last) \
	{                                                                                  \
		return std::unique_ptr<s>(new s{talker, first, last});                         \
	}                                                                                  \
	}

/// @endcond
}
}

#endif
