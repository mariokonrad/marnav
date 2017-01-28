#ifndef __MARNAV__NMEA__SENTENCE__HPP__
#define __MARNAV__NMEA__SENTENCE__HPP__

#include <functional>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>
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
		talker, fields::const_iterator, fields::const_iterator)>;

	/// Maximum length of a NMEA sentence (raw format as string).
	constexpr static int max_length = 82;

	/// The start token of normal NMEA sentences.
	constexpr static char start_token = '$';

	/// The start token of AIS related NMEA sentences.
	constexpr static char start_token_ais = '!';

	/// The end token (right before the checksum) of all NMEA sentences.
	constexpr static char end_token = '*';

	/// The start and end token of a tag block.
	constexpr static char tag_block_token = '\\';

	virtual ~sentence() = default;

	sentence() = delete;
	sentence(const sentence &) = default;
	sentence & operator=(const sentence &) = default;
	sentence(sentence &&) = default;
	sentence & operator=(sentence &&) = default;

	sentence_id id() const { return id_; }
	std::string tag() const { return tag_; }
	talker get_talker() const { return talker_; }

	/// Sets the talker of the sentence.
	///
	/// @note All subclasses specify a default talker at construction.
	///   This method is used to override the default or to set the
	///   talker ID explicitly.
	void set_talker(const talker & t) { talker_ = t; }

	/// Sets the tag block. This overwrites a possibly existent block.
	void set_tag_block(const std::string & t) { tag_block_ = t; }

	/// Returns the raw tag block string. Since tag blocks are not common
	/// at the moment, its handling is separated, @see tag_block.
	const std::string & get_tag_block() const { return tag_block_; }

	friend std::string to_string(const sentence &);

protected:
	sentence(sentence_id id, const std::string & tag, talker t);
	virtual std::vector<std::string> get_data() const = 0;
	virtual char get_start_token() const { return start_token; }
	virtual char get_end_token() const { return end_token; }

private:
	const sentence_id id_;
	const std::string tag_;
	talker talker_;
	std::string tag_block_;
};

// Class `sentence` must be an abstract class, this protectes
// against object slicing because it prevents an instance
// of `sentence` itself, e.g. const nmea::sentence = nmea::bod{};
static_assert(std::is_abstract<sentence>::value, "");

/// Helper function to parse a specific sentence.
template <class T>
std::unique_ptr<sentence> sentence_parse(talker talk, const sentence::fields & f)
{
	return std::unique_ptr<T>(new T{talk, f.begin(), f.end()});
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
	talker talk{talker_id::none};
	std::string tag;
	std::string tag_block;
	std::vector<std::string> fields;
	std::tie(talk, tag, tag_block, fields) = detail::extract_sentence_information(s);
	T result{talk, std::next(std::begin(fields)), std::prev(std::end(fields))};
	result.set_tag_block(tag_block);
	return result;
}

/// Renders the specified sentence into a string.
///
/// If the sentence is invalid, the returning string will be empty.
std::string to_string(const sentence & s);

/// @cond DEV
namespace detail
{
/// Checks if the specified cast is valid, throws `std::bad_cast` if not.
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

/// Raw pointer const variant.
///
/// @see sentence_cast(sentence * s)
template <class T> const T * sentence_cast(const sentence * s)
{
	return detail::check_cast<T>(s) ? static_cast<const T *>(s) : nullptr;
}

/// `std::unique_ptr` variant. If the cast is possible, the original `unique_ptr<sentence>`
/// will be invalidated and a new `unique_ptr<T>` will be returned. This has implications
/// within the calling code.
///
/// Code using a temporary `unique_ptr`:
/// @code
/// auto q = nmea::sentence_cast<nmea::mtw>(nmea::make_sentence("$IIMTW,9.5,C*2F"));
///   // here `q` is valid and an `unique_ptr`
/// @endcode
///
/// Possible undefined behaviour if not careful:
/// @code
/// auto p = nmea::make_sentence("$IIMTW,9.5,C*2F");
/// auto q = nmea::sentence_cast<nmea::mtw>(p);
///   // here `p` no is no longer valid, `q` is an `unique_ptr`.
///   // accessing `p` at this point is undefined behaviour.
/// @endcode
///
/// This can easily be resolved, when using the raw pointer variant of `sentence_cast`:
/// @code
/// auto p = nmea::make_sentence("$IIMTW,9.5,C*2F");
/// auto q = nmea::sentence_cast<nmea::mtw>(p.get());
///   // here `p` is still valid, `q` is a raw pointer.
/// @endcode
///
/// @param[in,out] s The sentence to cast.
/// @return The casted sentence. If the specified sentence was `nullptr`, the function
///   also returns `nullptr`.
/// @exception std::bad_cast This exception is thrown if the specified sentence is
///   not castable into the destination type `T`.
///
template <class T> std::unique_ptr<T> sentence_cast(std::unique_ptr<sentence> & s)
{
	return detail::check_cast<T>(s.get()) ? std::unique_ptr<T>(static_cast<T *>(s.release()))
										  : nullptr;
}

/// `unique_ptr` ref ref variant.
///
/// @see sentence_cast(std::unique_ptr<sentence> & s)
template <class T> std::unique_ptr<T> sentence_cast(std::unique_ptr<sentence> && s)
{
	return detail::check_cast<T>(s.get()) ? std::unique_ptr<T>(static_cast<T *>(s.release()))
										  : nullptr;
}

/// @}

/// @cond DEV

#define MARNAV_NMEA_SENTENCE_FRIENDS(s)                                                       \
	friend std::unique_ptr<sentence> detail::parse_##s(talker talk,                           \
		sentence::fields::const_iterator first, sentence::fields::const_iterator last);       \
	template <class T>                                                                        \
	friend std::unique_ptr<sentence> sentence_parse(talker talk, const sentence::fields & f); \
	template <typename T> friend T create_sentence(const std::string &);

#define MARNAV_NMEA_DECLARE_SENTENCE_PARSE_FUNC(s)                                           \
	namespace detail                                                                         \
	{                                                                                        \
	std::unique_ptr<sentence> parse_##s(talker talk, sentence::fields::const_iterator first, \
		sentence::fields::const_iterator last);                                              \
	}

#define MARNAV_NMEA_DEFINE_SENTENCE_PARSE_FUNC(s)                                            \
	namespace detail                                                                         \
	{                                                                                        \
	std::unique_ptr<sentence> parse_##s(talker talk, sentence::fields::const_iterator first, \
		sentence::fields::const_iterator last)                                               \
	{                                                                                        \
		return std::unique_ptr<s>(new s{talk, first, last});                                 \
	}                                                                                        \
	}

/// @endcond
}
}

#endif
