#ifndef MARNAV__NMEA__DSC__HPP
#define MARNAV__NMEA__DSC__HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/optional.hpp>
#include <marnav/utils/mmsi.hpp>
#include <marnav/geo/region.hpp>

namespace marnav
{
namespace nmea
{
/// @brief DSC - Digital Selective Calling Information
///
/// @note This class is @b EXPERIMENTAL
///
/// @code
///                                                     11
///        1  2          3  4  5  6          7    8 9 10|
///        |  |          |  |  |  |          |    | | | |
/// $--DSC,xx,xxxxxxxxxx,xx,xx,xx,xxxxxxxxxx,xxxx,?,?,a,a*hh<CR><LF>
/// @endcode
///
/// Field Number:
/// 1.  Format Specifier
/// 2.  Address (MMSI or geographical area), 10 digits
/// 3.  Category
/// 4.  Nature of distress or Telecommand 1
/// 5.  Telecommand 2
/// 6.  Position or Channel/Frequency
/// 7.  Time (HHMM)
/// 8.  ?
/// 9.  ?
/// 10. Acknowledgment
///     - B
///     - R
///     - S = End of Sequence
/// 11. Extension Indicator
///     - E = extension sentence (DSE) will follow, if not the field is null
///
/// @todo IMPLEMENTATION
///
class dsc : public sentence
{
	friend class detail::factory;

public:
	constexpr static sentence_id ID = sentence_id::DSC;
	constexpr static const char * TAG = "DSC";

	/// Format Specifier
	enum class format_specifier : uint32_t {
		geographical_area, ///< 102: Geographical, specifies an area
		distress, ///< 112: Distress
		all_ships, ///< 116: All Ships
		individual_station, ///< 120: Individual Station
	};

	/// Category
	enum class category : uint32_t {
		routine, ///< 100: Routine Call
		safety, ///< 108: Safety Call
		urgency, ///< 110: Urgency Call
		distress ///< 112: Distress
	};

	/// Nature of distress
	enum class distress_designation : uint32_t {
		fire = 100, ///< Fire/explosion
		flooding = 101, ///< Flooding
		collision = 102, ///< Collision
		grounding = 103, ///< Grounding
		listing = 104, ///< Listing, danger of capsizing
		sinking = 105, ///< Sinking
		adrift = 106, ///< Disabled and adrift
		undesignated = 107, ///< Undesignated Distress
		abandoning = 108, ///< Abandoning ship
		piracy = 109, ///< Piracy / armed robbery attack
		mob = 110, ///< Man over board
		epirb = 112, ///< EPIRB emission
	};

	/// First Telecommand
	enum class first_telecommand : uint32_t {
		polling = 103, ///< Polling
		unable_to_comply = 104, ///< Unable to comply
		end_of_call = 105, ///< End of call
		data = 106, ///< Data
		distress_ack = 110, ///< Distress acknowledgement
		distress_relay = 112, ///< Distress relay
		test = 118, ///< Test
		no_information = 126, ///< No Information
	};

	/// Second Telecommand
	enum class second_telecommand : uint32_t {
		no_information, ///< 126: No Information
	};

	enum class acknowledgement : char {
		B, ///< ?
		R, ///< ?
		end_of_sequence ///< NMEA representation: 'S'
	};

	enum class extension_indicator : char {
		none, ///< no NMEA representation
		extension_follows ///< NMEA representation: 'E'
	};

	dsc();
	dsc(const dsc &) = default;
	dsc & operator=(const dsc &) = default;
	dsc(dsc &&) = default;
	dsc & operator=(dsc &&) = default;

protected:
	dsc(talker talk, fields::const_iterator first, fields::const_iterator last);
	virtual void append_data_to(std::string &) const override;

private:
	format_specifier fmt_spec_ = format_specifier::distress;
	uint64_t address_ = 0; // space for 10 decimal digits
	category cat_ = category::distress;
	// @todo Implement other 6 data members
	acknowledgement ack_ = acknowledgement::end_of_sequence;
	extension_indicator extension_ = extension_indicator::none;

public:
	decltype(fmt_spec_) get_fmt_spec() const { return fmt_spec_; }
	decltype(cat_) get_cat() const { return cat_; }
	utils::mmsi get_mmsi() const;
	geo::region get_geographical_area() const;
	decltype(ack_) get_ack() const { return ack_; }
	decltype(extension_) get_extension() const { return extension_; }
};

std::string to_string(dsc::format_specifier value);
std::string to_string(dsc::category value);
std::string to_string(dsc::acknowledgement value);
std::string to_string(dsc::extension_indicator value);
}
}

#endif
