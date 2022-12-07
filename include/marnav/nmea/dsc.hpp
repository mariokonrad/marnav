#ifndef MARNAV_NMEA_DSC_HPP
#define MARNAV_NMEA_DSC_HPP

#include <marnav/nmea/sentence.hpp>
#include <marnav/utils/mmsi.hpp>
#include <marnav/geo/region.hpp>
#include <optional>

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
/// 8.  MMSI of the ship in distress
/// 9.  Distress Cause
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
		geographical_area = 102, ///< Geographical, specifies an area
		distress = 112, ///< Distress
		common_interest = 114, ///< Selective call to a group of ships having a common interest
		all_ships = 116, ///< All Ships
		individual_station = 120, ///< Individual Station
		individual_automatic_serivce = 123, ///< Particular individual using automatic service
	};

	/// Category
	enum class category : uint32_t {
		routine = 100, ///< Routine Call
		safety = 108, ///< Safety Call
		urgency = 110, ///< Urgency Call
		distress = 112, ///< Distress
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
		unassigned_11 = 111, ///< Unassinged, take no action
		epirb = 112, ///< EPIRB emission
		unassigned_13 = 113 , ///< Unassigned, take no action
		unassigned_14 = 114 , ///< Unassigned, take no action
		unassigned_15 = 115 , ///< Unassigned, take no action
		unassigned_16 = 116 , ///< Unassigned, take no action
		unassigned_17 = 117 , ///< Unassigned, take no action
		unassigned_18 = 118 , ///< Unassigned, take no action
		unassigned_19 = 119 , ///< Unassigned, take no action
		unassigned_20 = 120, ///< Unassigned, take no action
		unassigned_21 = 121, ///< Unassigned, take no action
		unassigned_22 = 122, ///< Unassigned, take no action
		unassigned_23 = 123, ///< Unassigned, take no action
		unassigned_24 = 124, ///< Unassigned, take no action
		unassigned_25 = 125, ///< Unassigned, take no action
		unassigned_26 = 126, ///< Unassigned, take no action
		unassigned_27 = 127, ///< Unassigned, take no action
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
		no_information = 126, ///< No Information
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
	virtual void append_data_to(std::string &, const version &) const override;

private:
	format_specifier fmt_spec_ = format_specifier::distress;
	uint64_t address_ = 0; // space for 10 decimal digits
	category cat_ = category::distress;
	std::optional<uint32_t> command_1_; // distress_designation if cat_ == category::distress or telecommand 1
	std::optional<second_telecommand> command_2_;
	std::optional<std::string> position_or_channel_;
	std::optional<std::string> time_or_phonenumber_;
	std::optional<uint64_t> mmsi_ship_in_distress_;
	std::optional<uint32_t> distress_cause_;
	std::optional<acknowledgement> ack_;
	extension_indicator extension_ = extension_indicator::none;

public:
	format_specifier get_fmt_spec() const { return fmt_spec_; }
	category get_cat() const { return cat_; }
	utils::mmsi get_mmsi() const;
	geo::region get_geographical_area() const;
	std::optional<uint32_t> get_command_1() const { return command_1_; }
	std::optional<second_telecommand> get_command_2() const { return command_2_; }
	std::optional<std::string> get_position_or_channel() const { return position_or_channel_; }
	std::optional<std::string> get_time_or_phonenumber() const { return time_or_phonenumber_; }
	std::optional<utils::mmsi> get_mmsi_ship_in_distress() const;
	std::optional<uint32_t> get_distress_cause() const { return distress_cause_; }
	std::optional<acknowledgement> get_ack() const { return ack_; }
	extension_indicator get_extension() const { return extension_; }

	// TODO: implemente setters
};

std::string to_string(dsc::format_specifier value);
std::string to_string(dsc::category value);
std::string to_string(dsc::acknowledgement value);
std::string to_string(dsc::extension_indicator value);
std::string to_string(dsc::second_telecommand value);

std::string to_name(dsc::format_specifier value);
std::string to_name(dsc::category value);
std::string to_name(dsc::acknowledgement value);
std::string to_name(dsc::extension_indicator value);
std::string to_name(dsc::second_telecommand value);
}
}

#endif
