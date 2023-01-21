#include <marnav/ais/message_24.hpp>
#include <marnav/utils/mmsi.hpp>

namespace marnav::ais
{
constexpr message_id message_24::ID;
constexpr std::size_t message_24::SIZE_BITS;
constexpr std::size_t message_24::SIZE_BITS_IGNORED_SPARES_OF_TYPE_A;

message_24::message_24()
	: message_24(ID)
{
}

message_24::message_24(message_id id)
	: message(id)
	, shipname_("@@@@@@@@@@@@@@@@@@@@")
	, vendor_id_("@@@")
	, callsign_("@@@@@@@")
{
}

message_24::message_24(const raw & bits)
	: message_24(ID)
{
	if ((bits.size() != SIZE_BITS) && (bits.size() != SIZE_BITS_IGNORED_SPARES_OF_TYPE_A))
		throw std::invalid_argument{"invalid number of bits in ais/message_24"};

	get(bits, part_number_);
	if ((part_number_ != part::A) && (part_number_ != part::B))
		throw std::invalid_argument{"invalid part number ais/message_24"};
	read_data(bits);
}

bool message_24::is_auxiliary_vessel() const
{
	return utils::mmsi{mmsi_}.is_auxiliary();
}

void message_24::read_data(const raw & bits)
{
	get(bits, repeat_indicator_);
	get(bits, mmsi_);
	get(bits, part_number_);

	if (part_number_ == part::A) {
		get(bits, shipname_);
	} else {
		get(bits, shiptype_);
		get(bits, vendor_id_);
		get(bits, model_);
		get(bits, serial_);
		get(bits, callsign_);
		if (is_auxiliary_vessel()) {
			get(bits, mothership_mmsi_);
		} else {
			get(bits, to_bow_);
			get(bits, to_stern_);
			get(bits, to_port_);
			get(bits, to_starboard_);
		}
	}
}

raw message_24::get_data() const
{
	raw bits(SIZE_BITS);

	bits.set(type(), 0, 6);
	set(bits, repeat_indicator_);
	set(bits, mmsi_);
	set(bits, part_number_);

	if (part_number_ == part::A) {
		set(bits, shipname_);
	} else {
		set(bits, shiptype_);
		set(bits, vendor_id_);
		set(bits, model_);
		set(bits, serial_);
		set(bits, callsign_);
		if (is_auxiliary_vessel()) {
			set(bits, mothership_mmsi_);
		} else {
			set(bits, to_bow_);
			set(bits, to_stern_);
			set(bits, to_port_);
			set(bits, to_starboard_);
		}
	}

	return bits;
}

std::string message_24::get_shipname() const
{
	return trim_ais_string(shipname_);
}

std::string message_24::get_vendor_id() const
{
	return trim_ais_string(vendor_id_);
}

std::string message_24::get_callsign() const
{
	return trim_ais_string(callsign_);
}

void message_24::set_shipname(const std::string & t)
{
	if (t.size() > 20) {
		shipname_ = t.substr(0, 20);
	} else {
		shipname_ = t;
	}
}

void message_24::set_vendor_id(const std::string & t)
{
	if (t.size() > 3) {
		callsign_ = t.substr(0, 3);
	} else {
		callsign_ = t;
	}
}

void message_24::set_callsign(const std::string & t)
{
	if (t.size() > 7) {
		callsign_ = t.substr(0, 7);
	} else {
		callsign_ = t;
	}
}

vessel_dimension message_24::get_vessel_dimension() const noexcept
{
	return {to_bow_, to_stern_, to_port_, to_starboard_};
}

void message_24::set_vessel_dimension(const vessel_dimension & t)
{
	to_bow_ = t.get_raw_to_bow();
	to_stern_ = t.get_raw_to_stern();
	to_port_ = t.get_raw_to_port();
	to_starboard_ = t.get_raw_to_starboard();
}
}
