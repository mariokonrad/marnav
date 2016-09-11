#include <fstream>
#include <iostream>
#include <vector>

#include <cxxopts/cxxopts.hpp>

#define FMT_HEADER_ONLY
#include <fmt/format.h>

#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/ais_helper.hpp>
#include <marnav/nmea/checksum.hpp>
#include <marnav/nmea/sentence.hpp>
#include <marnav/nmea/waypoint.hpp>

#include <marnav/nmea/aam.hpp>
#include <marnav/nmea/apb.hpp>
#include <marnav/nmea/bod.hpp>
#include <marnav/nmea/dbt.hpp>
#include <marnav/nmea/dtm.hpp>
#include <marnav/nmea/gga.hpp>
#include <marnav/nmea/gll.hpp>
#include <marnav/nmea/gsa.hpp>
#include <marnav/nmea/gsv.hpp>
#include <marnav/nmea/hdg.hpp>
#include <marnav/nmea/mtw.hpp>
#include <marnav/nmea/mwv.hpp>
#include <marnav/nmea/rmb.hpp>
#include <marnav/nmea/rmc.hpp>
#include <marnav/nmea/rte.hpp>
#include <marnav/nmea/vhw.hpp>
#include <marnav/nmea/vlw.hpp>
#include <marnav/nmea/vtg.hpp>
#include <marnav/nmea/vwr.hpp>
#include <marnav/nmea/zda.hpp>
#include <marnav/nmea/vdm.hpp>
#include <marnav/nmea/vdo.hpp>

#include <marnav/nmea/pgrme.hpp>
#include <marnav/nmea/pgrmm.hpp>
#include <marnav/nmea/pgrmz.hpp>

#include <marnav/ais/ais.hpp>

#include <marnav/ais/message_01.hpp>
#include <marnav/ais/message_02.hpp>
#include <marnav/ais/message_03.hpp>
#include <marnav/ais/message_04.hpp>
#include <marnav/ais/message_05.hpp>
#include <marnav/ais/message_11.hpp>
#include <marnav/ais/message_18.hpp>
#include <marnav/ais/message_21.hpp>
#include <marnav/ais/message_24.hpp>

namespace nmeadump
{
namespace terminal
{
static constexpr const char * normal = "\033[0m";
static constexpr const char * black = "\033[30m";
static constexpr const char * red = "\033[31m";
static constexpr const char * green = "\033[32m";
static constexpr const char * yellow = "\033[33m";
static constexpr const char * blue = "\033[34m";
static constexpr const char * magenta = "\033[35m";
static constexpr const char * cyan = "\033[36m";
static constexpr const char * white = "\033[37m";
}

namespace
{
template <class Container>
static bool contains(
	const Container & container, const typename Container::value_type & element)
{
	return std::find(std::begin(container), std::end(container), element)
		!= std::end(container);
}
}

static struct {
	struct {
		std::string port;
		uint32_t port_speed = 0;
		std::string file;
	} config;
} global;

static bool parse_options(int argc, char ** argv)
{
	// clang-format off
	cxxopts::Options options{argv[0], "NMEA Dump"};
	options.add_options()
		("h,help",
			"Shows help information.")
		("p,port",
			"Specifies the port to use.",
			cxxopts::value<std::string>(global.config.port))
		("s,speed",
			"Specifies the port speed. Valid values: 4800, 38400",
			cxxopts::value<uint32_t>(global.config.port_speed))
		("f,file",
			"Specifies the file to use.",
			cxxopts::value<std::string>(global.config.file))
		;
	// clang-format on

	options.parse(argc, argv);

	if (options.count("help")) {
		fmt::printf("%s\n", options.help());
		fmt::printf("If no file or port is specified, stdin is used to read data from.\n\n");
		return true;
	}

	// validation

	static const std::vector<uint32_t> valid_port_speeds = {4800, 38400};

	if (options.count("port") && options.count("file"))
		throw std::runtime_error{"specifying port and file is illegal"};
	if (options.count("port") && !contains(valid_port_speeds, global.config.port_speed))
		throw std::runtime_error{"invalid port speed"};

	return false;
}

static std::string trim(const std::string & s)
{
	static const char * whitespace = "\n\r\t ";
	const auto begin = s.find_first_not_of(whitespace);
	const auto end = s.find_last_not_of(whitespace);
	return begin != std::string::npos ? s.substr(begin, end - begin + 1) : "";
}

namespace detail
{
template <typename T> static std::string render(const T & t)
{
	return marnav::nmea::to_string(t);
}

static std::string render(const std::string & t) { return t; }

static std::string render(bool t) { return t ? "true" : "false"; }

static std::string render(char t) { return fmt::sprintf("%c", t); }

static std::string render(const uint32_t t) { return fmt::sprintf("%u", t); }

static std::string render(const int32_t t) { return fmt::sprintf("%d", t); }

static std::string render(const int8_t t) { return fmt::sprintf("%d", t); }

static std::string render(const uint8_t t) { return fmt::sprintf("%u", t); }

static std::string render(const double t) { return fmt::sprintf("%-8.3f", t); }

static std::string render(const marnav::utils::mmsi & t)
{
	return fmt::sprintf("%09u", static_cast<marnav::utils::mmsi::value_type>(t));
}

static std::string render(const marnav::nmea::time & t)
{
	return fmt::sprintf("%02u:%02u:%02u", t.hour(), t.minutes(), t.seconds());
}

static std::string render(const marnav::geo::latitude & t)
{
	using namespace marnav::nmea;
	return fmt::sprintf(
		" %02u\u00b0%02u'%04.1f%s", t.degrees(), t.minutes(), t.seconds(), to_string(t.hem()));
}

static std::string render(const marnav::geo::longitude & t)
{
	using namespace marnav::nmea;
	return fmt::sprintf(
		"%03u\u00b0%02u'%04.1f%s", t.degrees(), t.minutes(), t.seconds(), to_string(t.hem()));
}

static std::string render(const marnav::ais::message_24::part t)
{
	switch (t) {
		case marnav::ais::message_24::part::A:
			return "A";
		case marnav::ais::message_24::part::B:
			return "B";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::ais::ship_type t)
{
	switch (t) {
		case marnav::ais::ship_type::not_available:
			return "Not Available";
		case marnav::ais::ship_type::wing_in_ground:
			return "Wing in ground";
		case marnav::ais::ship_type::wing_in_ground_hazardous_cat_a:
			return "Wing in ground hazardous Cat A";
		case marnav::ais::ship_type::wing_in_ground_hazardous_cat_b:
			return "Wing in ground hazardous Cat B";
		case marnav::ais::ship_type::wing_in_ground_hazardous_cat_c:
			return "Wing in ground hazardous Cat C";
		case marnav::ais::ship_type::wing_in_ground_hazardous_cat_d:
			return "Wing in ground hazardous Cat D";
		case marnav::ais::ship_type::fishing:
			return "Fishing";
		case marnav::ais::ship_type::towing:
			return "Towing";
		case marnav::ais::ship_type::towing_large:
			return "Towing large";
		case marnav::ais::ship_type::dredging_or_underwater_ops:
			return "Dredging or underwater ops";
		case marnav::ais::ship_type::diving_ops:
			return "Diving ops";
		case marnav::ais::ship_type::military_ops:
			return "Military ops";
		case marnav::ais::ship_type::sailing:
			return "Sailing";
		case marnav::ais::ship_type::pleasure_craft:
			return "Pleasure Craft";
		case marnav::ais::ship_type::high_speed_craft:
			return "High speed craft";
		case marnav::ais::ship_type::high_speed_craft_hazardous_cat_a:
			return "High speed craft hazardous Cat A";
		case marnav::ais::ship_type::high_speed_craft_hazardous_cat_b:
			return "High speed craft hazardous Cat B";
		case marnav::ais::ship_type::high_speed_craft_hazardous_cat_c:
			return "High speed craft hazardous Cat C";
		case marnav::ais::ship_type::high_speed_craft_hazardous_cat_d:
			return "High speed craft hazardous Cat D";
		case marnav::ais::ship_type::high_speed_craft_no_info:
			return "High speed craft no_info";
		case marnav::ais::ship_type::pilot_vessel:
			return "Pilot Vessel";
		case marnav::ais::ship_type::search_and_rescue_vessel:
			return "Search and Rescue Vessel";
		case marnav::ais::ship_type::tug:
			return "Tug";
		case marnav::ais::ship_type::port_tender:
			return "Port Tender";
		case marnav::ais::ship_type::anti_pollution_equipment:
			return "Anti Pollution Equipment";
		case marnav::ais::ship_type::law_enforcement:
			return "Law Enforcement";
		case marnav::ais::ship_type::medical_transport:
			return "Medical Transport";
		case marnav::ais::ship_type::noncombatant:
			return "Noncombatant";
		case marnav::ais::ship_type::passenger:
			return "Passenger";
		case marnav::ais::ship_type::passenger_hazardous_cat_a:
			return "Passenger hazardous Cat A";
		case marnav::ais::ship_type::passenger_hazardous_cat_b:
			return "Passenger hazardous Cat B";
		case marnav::ais::ship_type::passenger_hazardous_cat_c:
			return "Passenger hazardous Cat C";
		case marnav::ais::ship_type::passenger_hazardous_cat_d:
			return "Passenger hazardous Cat D";
		case marnav::ais::ship_type::passenger_no_info:
			return "Passenger no info";
		case marnav::ais::ship_type::cargo:
			return "Cargo";
		case marnav::ais::ship_type::cargo_hazardous_cat_a:
			return "Cargo hazardous Cat A";
		case marnav::ais::ship_type::cargo_hazardous_cat_b:
			return "Cargo hazardous Cat B";
		case marnav::ais::ship_type::cargo_hazardous_cat_c:
			return "Cargo hazardous Cat C";
		case marnav::ais::ship_type::cargo_hazardous_cat_d:
			return "Cargo hazardous Cat D";
		case marnav::ais::ship_type::cargo_no_info:
			return "Cargo no info";
		case marnav::ais::ship_type::tanker:
			return "Tanker";
		case marnav::ais::ship_type::tanker_hazardous_cat_a:
			return "Tanker hazardous Cat A";
		case marnav::ais::ship_type::tanker_hazardous_cat_b:
			return "Tanker hazardous Cat B";
		case marnav::ais::ship_type::tanker_hazardous_cat_c:
			return "Tanker hazardous Cat C";
		case marnav::ais::ship_type::tanker_hazardous_cat_d:
			return "Tanker hazardous Cat D";
		case marnav::ais::ship_type::tanker_no_info:
			return "Tanker no info";
		case marnav::ais::ship_type::other:
			return "Other";
		case marnav::ais::ship_type::other_hazardous_cat_a:
			return "Other hazardous Cat A";
		case marnav::ais::ship_type::other_hazardous_cat_b:
			return "Other hazardous Cat B";
		case marnav::ais::ship_type::other_hazardous_cat_c:
			return "Other hazardous Cat C";
		case marnav::ais::ship_type::other_hazardous_cat_d:
			return "Other hazardous Cat D";
		case marnav::ais::ship_type::other_no_info:
			return "Other no info";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::ais::epfd_fix_type t)
{
	switch (t) {
		case marnav::ais::epfd_fix_type::undefined:
			return "undefined";
		case marnav::ais::epfd_fix_type::gps:
			return "GPS";
		case marnav::ais::epfd_fix_type::glonass:
			return "GLONASS";
		case marnav::ais::epfd_fix_type::combined_gps_glonass:
			return "Combined GPS GLONASS";
		case marnav::ais::epfd_fix_type::loran_c:
			return "Loran C";
		case marnav::ais::epfd_fix_type::chayka:
			return "Chayka";
		case marnav::ais::epfd_fix_type::integrated_navigation_system:
			return "Integrated Navigation System";
		case marnav::ais::epfd_fix_type::surveyed:
			return "surveyed";
		case marnav::ais::epfd_fix_type::galileo:
			return "Galileo";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::ais::message_21::off_position_indicator t)
{
	switch (t) {
		case marnav::ais::message_21::off_position_indicator::on_position:
			return "On Position";
		case marnav::ais::message_21::off_position_indicator::off_position:
			return "Off Position";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::ais::message_21::virtual_aid t)
{
	switch (t) {
		case marnav::ais::message_21::virtual_aid::real_aid:
			return "Real Aid";
		case marnav::ais::message_21::virtual_aid::virtual_aid:
			return "Virtual Aid";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::ais::message_21::aid_type_id t)
{
	switch (t) {
		case marnav::ais::message_21::aid_type_id::unspecified:
			return "unspecified";
		case marnav::ais::message_21::aid_type_id::reference_point:
			return "Reference point";
		case marnav::ais::message_21::aid_type_id::racon:
			return "RACON (radar transponder marking a navigation hazard)";
		case marnav::ais::message_21::aid_type_id::fixed_structure:
			return "Fixed structure";
		case marnav::ais::message_21::aid_type_id::reserved:
			return "Spare, Reserved for future use";
		case marnav::ais::message_21::aid_type_id::light_no_sectors:
			return "Light, without sectors";
		case marnav::ais::message_21::aid_type_id::light_sectors:
			return "Light, with sectors";
		case marnav::ais::message_21::aid_type_id::leading_light_fromt:
			return "Leading Light Front";
		case marnav::ais::message_21::aid_type_id::leading_light_rear:
			return "Leading Light Rear";
		case marnav::ais::message_21::aid_type_id::beacon_cardinal_n:
			return "Beacon, Cardinal N";
		case marnav::ais::message_21::aid_type_id::beacon_cardinal_e:
			return "Beacon, Cardinal E";
		case marnav::ais::message_21::aid_type_id::beacon_cardinal_s:
			return "Beacon, Cardinal S";
		case marnav::ais::message_21::aid_type_id::beacon_cardinal_w:
			return "Beacon, Cardinal W";
		case marnav::ais::message_21::aid_type_id::beacon_port_hand:
			return "Beacon, Port hand";
		case marnav::ais::message_21::aid_type_id::beacon_starboard_hand:
			return "Beacon, Starboard hand";
		case marnav::ais::message_21::aid_type_id::beacon_preferred_channel_port_hand:
			return "Beacon, Preferred Channel port hand";
		case marnav::ais::message_21::aid_type_id::beacon_preferred_channel_starboard_hand:
			return "Beacon, Preferred Channel starboard hand";
		case marnav::ais::message_21::aid_type_id::beacon_isolated_danger:
			return "Beacon, Isolated danger";
		case marnav::ais::message_21::aid_type_id::beacon_safe_water:
			return "Beacon, Safe water";
		case marnav::ais::message_21::aid_type_id::beacon_sepcial_mark:
			return "Beacon, Special mark";
		case marnav::ais::message_21::aid_type_id::cardinal_n:
			return "Cardinal Mark N";
		case marnav::ais::message_21::aid_type_id::cardinal_e:
			return "Cardinal Mark E";
		case marnav::ais::message_21::aid_type_id::cardinal_s:
			return "Cardinal Mark S";
		case marnav::ais::message_21::aid_type_id::cardinal_w:
			return "Cardinal Mark W";
		case marnav::ais::message_21::aid_type_id::mark_port_hand:
			return "Port hand Mark";
		case marnav::ais::message_21::aid_type_id::mark_starboard_hand:
			return "Starboard hand Mark";
		case marnav::ais::message_21::aid_type_id::preferred_channel_port_hand:
			return "Preferred Channel Port hand";
		case marnav::ais::message_21::aid_type_id::preferred_channel_starboard_hand:
			return "Preferred Channel Starboard hand";
		case marnav::ais::message_21::aid_type_id::isolated_danger:
			return "Isolated danger";
		case marnav::ais::message_21::aid_type_id::safe_water:
			return "Safe Water";
		case marnav::ais::message_21::aid_type_id::special_mark:
			return "Special Mark";
		case marnav::ais::message_21::aid_type_id::light_vessel:
			return "Light Vessel / LANBY / Rigs";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::unit::distance t)
{
	switch (t) {
		case marnav::nmea::unit::distance::meter:
			return "m";
		case marnav::nmea::unit::distance::feet:
			return "ft";
		case marnav::nmea::unit::distance::nm:
			return "nm";
		case marnav::nmea::unit::distance::km:
			return "km";
		case marnav::nmea::unit::distance::fathom:
			return "fathom";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::unit::temperature t)
{
	switch (t) {
		case marnav::nmea::unit::temperature::celsius:
			return "\u00b0C";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::unit::velocity t)
{
	switch (t) {
		case marnav::nmea::unit::velocity::knot:
			return "kn";
		case marnav::nmea::unit::velocity::kmh:
			return "km/h";
		case marnav::nmea::unit::velocity::mps:
			return "m/s";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::side t)
{
	switch (t) {
		case marnav::nmea::side::left:
			return "Left";
		case marnav::nmea::side::right:
			return "Rigth";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::reference t)
{
	switch (t) {
		case marnav::nmea::reference::RELATIVE:
			return "relative";
		case marnav::nmea::reference::TRUE:
			return "true";
		case marnav::nmea::reference::MAGNETIC:
			return "magnetic";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::quality t)
{
	switch (t) {
		case marnav::nmea::quality::invalid:
			return "invaild";
		case marnav::nmea::quality::gps_fix:
			return "GPS fix";
		case marnav::nmea::quality::dgps_fix:
			return "DGPS fix";
		case marnav::nmea::quality::guess:
			return "guess";
		case marnav::nmea::quality::simulation:
			return "simulation";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::direction t)
{
	switch (t) {
		case marnav::nmea::direction::north:
			return "N";
		case marnav::nmea::direction::south:
			return "S";
		case marnav::nmea::direction::west:
			return "W";
		case marnav::nmea::direction::east:
			return "E";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::selection_mode t)
{
	switch (t) {
		case marnav::nmea::selection_mode::manual:
			return "manual";
		case marnav::nmea::selection_mode::automatic:
			return "automatic";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::status t)
{
	switch (t) {
		case marnav::nmea::status::ok:
			return "OK";
		case marnav::nmea::status::warning:
			return "Warning";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::route t)
{
	switch (t) {
		case marnav::nmea::route::complete:
			return "complete";
		case marnav::nmea::route::working:
			return "working";
		default:
			break;
	}
	return "-";
}

static std::string render(const marnav::nmea::waypoint & t) { return t.c_str(); }

static std::string render(const marnav::nmea::mode_indicator t)
{
	switch (t) {
		case marnav::nmea::mode_indicator::invalid:
			return "invalid";
		case marnav::nmea::mode_indicator::autonomous:
			return "autonomous";
		case marnav::nmea::mode_indicator::differential:
			return "differential";
		case marnav::nmea::mode_indicator::estimated:
			return "estimated";
		case marnav::nmea::mode_indicator::manual_input:
			return "manual input";
		case marnav::nmea::mode_indicator::simulated:
			return "simulated";
		case marnav::nmea::mode_indicator::data_not_valid:
			return "not valid";
		case marnav::nmea::mode_indicator::precise:
			return "precise";
		default:
			break;
	}
	return "-";
}

template <typename T> static std::string render(const marnav::utils::optional<T> & t)
{
	if (!t)
		return "-";
	return render(*t);
}

static void print(const std::string & name, const std::string & value)
{
	fmt::printf("\t%-30s : %s\n", name, value);
}

static void print_detail_hdg(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::hdg>(s);
	print("Heading", render(t->get_heading()));
	print("Magn Deviation",
		fmt::sprintf("%s %s", render(t->get_magn_dev()), render(t->get_magn_dev_hem())));
	print("Magn Variation",
		fmt::sprintf("%s %s", render(t->get_magn_var()), render(t->get_magn_var_hem())));
}

static void print_detail_rmb(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::rmb>(s);
	print("Active", render(t->get_active()));
	print("Cross Track Error", render(t->get_cross_track_error()));
	print("Waypoint To", render(t->get_waypoint_to()));
	print("Waypoint From", render(t->get_waypoint_from()));
	print("Latitude", render(t->get_latitude()));
	print("Longitude", render(t->get_longitude()));
	print("Range", render(t->get_range()));
	print("Bearing", render(t->get_bearing()));
	print("Dest. Velocity", render(t->get_dst_velocity()));
	print("Arrival Status", render(t->get_arrival_status()));
	print("Mode Indicator", render(t->get_mode_ind()));
}

static void print_detail_rmc(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::rmc>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Status", render(t->get_status()));
	print("Latitude", render(t->get_latitude()));
	print("Longitude", render(t->get_longitude()));
	print("SOG", render(t->get_sog()));
	print("Heading", render(t->get_heading()));
	print("Date", render(t->get_date()));
	print("Magn Dev", fmt::sprintf("%s %s", render(t->get_mag()), render(t->get_mag_hem())));
	print("Mode Ind ", render(t->get_mode_ind()));
}

static void print_detail_vtg(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::vtg>(s);
	print("Track True", render(t->get_track_true()));
	print("Track Magn", render(t->get_track_magn()));
	print("Speed Knots", render(t->get_speed_kn()));
	print("Speed kmh", render(t->get_speed_kmh()));
	print("Mode Indicator", render(t->get_mode_ind()));
}

static void print_detail_gll(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gll>(s);
	print("Latitude", render(t->get_latitude()));
	print("Longitude", render(t->get_longitude()));
	print("Time UTC", render(t->get_time_utc()));
	print("Status", render(t->get_data_valid()));
	print("Mode Indicator", render(t->get_mode_ind()));
}

static void print_detail_bod(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::bod>(s);
	print("Bearing True", render(t->get_bearing_true()));
	print("Bearing Magn", render(t->get_bearing_magn()));
	print("Waypoint To", render(t->get_waypoint_to()));
	print("Waypoint From", render(t->get_waypoint_from()));
}

static void print_detail_gsa(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gsa>(s);
	print("Selection Mode", render(t->get_sel_mode()));
	print("Mode", render(t->get_mode()));
	for (auto i = 0; i < marnav::nmea::gsa::max_satellite_ids; ++i) {
		print(fmt::sprintf("Satellite %02u", i), render(t->get_satellite_id(i)));
	}
	print("PDOP", render(t->get_pdop()));
	print("HDOP", render(t->get_hdop()));
	print("VDOP", render(t->get_vdop()));
}

static void print_detail_gga(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gga>(s);
	print("Time", render(t->get_time()));
	print("Latitude", render(t->get_latitude()));
	print("Longitude", render(t->get_longitude()));
	print("Quality Ind", render(t->get_quality_indicator()));
	print("Num Satellites", render(t->get_n_satellites()));
	print("Horiz Dilution", render(t->get_hor_dilution()));
	print("Altitude",
		fmt::sprintf("%s %s", render(t->get_altitude()), render(t->get_altitude_unit())));
	print("Geodial Sep", fmt::sprintf("%s %s", render(t->get_geodial_separation()),
							 render(t->get_geodial_separation_unit())));
	print("DGPS Age", render(t->get_dgps_age()));
	print("DGPS Ref", render(t->get_dgps_ref()));
}

static void print_detail_mwv(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::mwv>(s);
	print("Angle", fmt::sprintf("%s %s", render(t->get_angle()), render(t->get_angle_ref())));
	print("Speed", fmt::sprintf("%s %s", render(t->get_speed()), render(t->get_speed_unit())));
	print("Data Valid", render(t->get_data_valid()));
}

static void print_detail_gsv(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::gsv>(s);
	print("Num Messages", render(t->get_n_messages()));
	print("Messages Number", render(t->get_message_number()));
	print("Num Sat in View", render(t->get_n_satellites_in_view()));
	for (int i = 0; i < 4; ++i) {
		const auto sat = t->get_sat(i);
		if (sat) {
			print("Sat", fmt::sprintf("ID:%02u ELEV:%02u AZIMUTH:%03u SNR:%02u", sat->id,
							 sat->elevation, sat->azimuth, sat->snr));
		}
	}
}

static void print_detail_zda(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::zda>(s);
	print("Time UTC", render(t->get_time_utc()));
	print("Day", render(t->get_day()));
	print("Month", render(t->get_month()));
	print("Year", render(t->get_year()));
	print("Local Zone Hours", render(t->get_local_zone_hours()));
	print("Local Zone Min", render(t->get_local_zone_minutes()));
}

static void print_detail_dtm(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::dtm>(s);
	print("Ref", render(t->get_ref()));
	print("Subcode", render(t->get_subcode()));
	print("Latitude Offset", render(t->get_lat_offset()));
	print("Latitude Hem", render(t->get_lat_hem()));
	print("Longitude Offset", render(t->get_lon_offset()));
	print("Longitude Hem", render(t->get_lon_hem()));
	print("Altitude", render(t->get_altitude()));
	print("Name", render(t->get_name()));
}

static void print_detail_aam(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::aam>(s);
	print("Arrival Circle Entred", render(t->get_arrival_circle_entered()));
	print("Perpendicular Passed", render(t->get_perpendicualar_passed()));
	print("Arrival Circle Radius", fmt::sprintf("%s %s", render(t->get_arrival_circle_radius()),
									   render(t->get_arrival_circle_radius_unit())));
	print("Waypoint", render(t->get_waypoint_id()));
}

static void print_detail_rte(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::rte>(s);
	print("Number of Messages", render(t->get_n_messages()));
	print("Message Number", render(t->get_message_number()));
	print("Message Mode", render(t->get_message_mode()));
	for (int i = 0; i < marnav::nmea::rte::max_waypoints; ++i) {
		const auto wp = t->get_waypoint_id(i);
		if (wp)
			print(fmt::sprintf("Waypoint %i", i), render(wp));
	}
}

static void print_detail_mtw(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::mtw>(s);
	print("Water Temperature",
		fmt::sprintf("%s %s", render(t->get_temperature()), render(t->get_temperature_unit())));
}

static void print_detail_dbt(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::dbt>(s);
	print("Depth Feet", render(t->get_depth_feet()));
	print("Depth Meter", render(t->get_depth_meter()));
	print("Depth Fathom", render(t->get_depth_fathom()));
}

static void print_detail_apb(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::apb>(s);
	print("Loran C blink warn", render(t->get_loran_c_blink_warning()));
	print("Loran C cycle lock warn", render(t->get_loran_c_cycle_lock_warning()));
	print("Cross Track Error Magnitude", render(t->get_cross_track_error_magnitude()));
	print("Direction to Steer", render(t->get_direction_to_steer()));
	print("Cross Track Unit", render(t->get_cross_track_unit()));
	print("Status Arrival", render(t->get_status_arrival()));
	print("Status Perpendicular Pass", render(t->get_status_perpendicular_passing()));
	print("Bearing Org to Dest", render(t->get_bearing_origin_to_destination()));
	print("Bearing Org to Dest Ref", render(t->get_bearing_origin_to_destination_ref()));
	print("Waypoint", render(t->get_waypoint_id()));
	print("Bearing Pos to Dest", render(t->get_bearing_pos_to_destination()));
	print("Bearing Pos to Dest Ref", render(t->get_bearing_pos_to_destination_ref()));
	print("Heading to Steer to Dest", render(t->get_heading_to_steer_to_destination()));
	print("Heading to Steer to Dest Ref", render(t->get_heading_to_steer_to_destination_ref()));
	print("Mode Indicator", render(t->get_mode_ind()));
}

static void print_detail_pgrme(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::pgrme>(s);
	print("HPE", render(t->get_horizontal_position_error()));
	print("VPE", render(t->get_vertical_position_error()));
	print("O.sph.eq.pos err", render(t->get_overall_spherical_equiv_position_error()));
}

static void print_detail_pgrmm(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::pgrmm>(s);
	print("Map Datum", render(t->get_map_datum()));
}

static void print_detail_pgrmz(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::pgrmz>(s);
	print("Altitude", render(t->get_altitude()));
	print("Fix Type", render(t->get_fix()));
}

static void print_detail_vwr(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::vwr>(s);
	print("Angle", fmt::sprintf("%s %s", render(t->get_angle()), render(t->get_angle_side())));
	print("Speed Knots", render(t->get_speed_knots()));
	print("Speed m/s", render(t->get_speed_mps()));
	print("Speed km/h", render(t->get_speed_kmh()));
}

static void print_detail_vlw(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::vlw>(s);
	print("Distance Cumulative nm", render(t->get_distance_cum()));
	print("Distance since Rest nm", render(t->get_distance_reset()));
}

static void print_detail_vhw(const marnav::nmea::sentence * s)
{
	const auto t = marnav::nmea::sentence_cast<marnav::nmea::vhw>(s);
	print("Heading True", render(t->get_heading_empty()));
	print("Heading Magn", render(t->get_heading()));
	print("Speed kn", render(t->get_speed_knots()));
	print("Speed km/h", render(t->get_speed_kmh()));
}

static void print_detail_message_01_common( const marnav::ais::message_01 * t)
{
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("ROT", render(t->get_rot()));
	print("SOG", render(t->get_sog()));
	print("Pos Accuracy", render(t->get_position_accuracy()));
	print("Latitude", render(t->get_latitude()));
	print("Longitude", render(t->get_longitude()));
	print("COG", render(t->get_cog()));
	print("HDG", render(t->get_hdg()));
	print("Time Stamp", render(t->get_timestamp()));
	print("RAIM", render(t->get_raim()));
	print("Radio Status", render(t->get_radio_status()));
}

static void print_detail_message_01(const marnav::ais::message * m)
{
	print_detail_message_01_common(marnav::ais::message_cast<marnav::ais::message_01>(m));
}

static void print_detail_message_02(const marnav::ais::message * m)
{
	print_detail_message_01_common(marnav::ais::message_cast<marnav::ais::message_02>(m));
}

static void print_detail_message_03(const marnav::ais::message * m)
{
	print_detail_message_01_common(marnav::ais::message_cast<marnav::ais::message_03>(m));
}

static void print_detail_message_04_common(const marnav::ais::message_04 * t)
{
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("Year", render(t->get_year()));
	print("Month", render(t->get_month()));
	print("Day", render(t->get_day()));
	print("Hour", render(t->get_hour()));
	print("Minute", render(t->get_minute()));
	print("Second", render(t->get_second()));
	print("Pos Accuracy", render(t->get_position_accuracy()));
	print("Latitude", render(t->get_latitude()));
	print("Longitude", render(t->get_longitude()));
	print("EPFD Fix", render(t->get_epfd_fix()));
	print("RAIM", render(t->get_raim()));
	print("Radio Status", render(t->get_radio_status()));
}

static void print_detail_message_04(const marnav::ais::message * m)
{
	print_detail_message_04_common(marnav::ais::message_cast<marnav::ais::message_04>(m));
}

static void print_detail_message_11(const marnav::ais::message * m)
{
	print_detail_message_04_common(marnav::ais::message_cast<marnav::ais::message_11>(m));
}

static void print_detail_message_05(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_05>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("AIS Version", render(t->get_ais_version()));
	print("IMO", render(t->get_imo_number()));
	print("Callsign", render(t->get_callsign()));
	print("Shipname", render(t->get_shipname()));
	print("Shiptype", render(t->get_shiptype()));
	print("Length", render(t->get_to_bow() + t->get_to_stern()));
	print("Width", render(t->get_to_port() + t->get_to_starboard()));
	print("Draught", render(t->get_draught()));
	print("EPFD Fix", render(t->get_epfd_fix()));
	print("ETA Month", render(t->get_eta_month()));
	print("ETA Day", render(t->get_eta_day()));
	print("ETA Hour", render(t->get_eta_hour()));
	print("ETA Minute", render(t->get_eta_minute()));
	print("Destination", render(t->get_destination()));
	print("DTE", render(t->get_dte()));
}

static void print_detail_message_18(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_18>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("SOG", render(t->get_sog()));
	print("Pos Accuracy", render(t->get_position_accuracy()));
	print("Latitude", render(t->get_latitude()));
	print("Longitude", render(t->get_longitude()));
	print("COG", render(t->get_cog()));
	print("HDG", render(t->get_hdg()));
	print("Time Stamp", render(t->get_timestamp()));
	print("CS Unit", render(t->get_cs_unit()));
	print("Display Flag", render(t->get_display_flag()));
	print("DSC Flag", render(t->get_dsc_flag()));
	print("Band Flag", render(t->get_band_flag()));
	print("Message 22 Flag", render(t->get_message_22_flag()));
	print("Assigned", render(t->get_assigned()));
	print("RAIM", render(t->get_raim()));
	print("Radio Status", render(t->get_radio_status()));
}

static void print_detail_message_21(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_21>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("Aid Type", render(t->get_aid_type()));
	print("Name", render(t->get_name()));
	print("Pos Accuracy", render(t->get_position_accuracy()));
	print("Latitude", render(t->get_latitude()));
	print("Longitude", render(t->get_longitude()));
	print("Length", render(t->get_to_bow() + t->get_to_stern()));
	print("Width", render(t->get_to_port() + t->get_to_starboard()));
	print("EPFD Fix", render(t->get_epfd_fix()));
	print("UTC Second", render(t->get_utc_second()));
	print("Off Pos Indicator", render(t->get_off_position()));
	print("Regional", render(t->get_regional()));
	print("RAIM", render(t->get_raim()));
	print("Virtual Aid Flag", render(t->get_virtual_aid_flag()));
	print("Assigned", render(t->get_assigned()));
	print("Name Extension", render(t->get_name_extension()));
}

static void print_detail_message_24(const marnav::ais::message * m)
{
	const auto t = marnav::ais::message_cast<marnav::ais::message_24>(m);
	print("Repeat Indicator", render(t->get_repeat_indicator()));
	print("MMSI", render(t->get_mmsi()));
	print("Part", render(t->get_part_number()));
	if (t->get_part_number() == marnav::ais::message_24::part::A) {
		print("Ship Name", render(t->get_shipname()));
	} else {
		print("Ship Type", render(t->get_shiptype()));
		print("Vendor ID", render(t->get_vendor_id()));
		print("Model", render(t->get_model()));
		print("Serial", render(t->get_serial()));
		print("Callsign", render(t->get_callsign()));
		if (t->is_auxiliary_vessel()) {
			print("Mothership MMSI", render(t->get_mothership_mmsi()));
		} else {
			print("Length", render(t->get_to_bow() + t->get_to_stern()));
			print("Width", render(t->get_to_port() + t->get_to_starboard()));
		}
	}
}
}

static void dump_nmea(const std::string & line)
{
#define ADD_SENTENCE(s)                               \
	{                                                 \
		marnav::nmea::s::ID, detail::print_detail_##s \
	}
	struct entry {
		marnav::nmea::sentence_id id;
		std::function<void(const marnav::nmea::sentence *)> func;
	};
	using container = std::vector<entry>;
	// clang-format off
	static const container sentences = {
		// standard
		ADD_SENTENCE(aam),
		ADD_SENTENCE(apb),
		ADD_SENTENCE(bod),
		ADD_SENTENCE(dbt),
		ADD_SENTENCE(dtm),
		ADD_SENTENCE(gga),
		ADD_SENTENCE(gll),
		ADD_SENTENCE(gsa),
		ADD_SENTENCE(gsv),
		ADD_SENTENCE(hdg),
		ADD_SENTENCE(mtw),
		ADD_SENTENCE(mwv),
		ADD_SENTENCE(rmb),
		ADD_SENTENCE(rmc),
		ADD_SENTENCE(rte),
		ADD_SENTENCE(vhw),
		ADD_SENTENCE(vlw),
		ADD_SENTENCE(vtg),
		ADD_SENTENCE(vwr),
		ADD_SENTENCE(zda),

		// proprietary
		ADD_SENTENCE(pgrme),
		ADD_SENTENCE(pgrmm),
		ADD_SENTENCE(pgrmz)
	};
	// clang-format on
#undef ADD_SENTENCE

	using namespace marnav;

	try {
		auto s = nmea::make_sentence(line);
		auto i = std::find_if(std::begin(sentences), std::end(sentences),
			[&s](const container::value_type & item) { return item.id == s->id(); });
		if (i == std::end(sentences)) {
			fmt::printf(
				"%s%s%s\n\tnot implemented\n\n", terminal::magenta, line, terminal::normal);
		} else {
			fmt::printf("%s%s%s\n", terminal::green, line, terminal::normal);
			i->func(s.get());
			fmt::printf("\n");
		}
	} catch (nmea::unknown_sentence & error) {
		fmt::printf("%s%s%s\n\terror: unknown sentence: %s\n\n", terminal::red, line,
			terminal::normal, error.what());
	} catch (nmea::checksum_error & error) {
		fmt::printf("%s%s%s\n\terror: checksum error: %s\n\n", terminal::red, line,
			terminal::normal, error.what());
	} catch (std::invalid_argument & error) {
		fmt::printf(
			"%s%s%s\n\terror: %s\n\n", terminal::red, line, terminal::normal, error.what());
	}
}

static void dump_ais(const std::vector<std::unique_ptr<marnav::nmea::sentence>> & sentences)
{
#define ADD_MESSAGE(m)                               \
	{                                                 \
		marnav::ais::m::ID, detail::print_detail_##m \
	}
	struct entry {
		marnav::ais::message_id id;
		std::function<void(const marnav::ais::message *)> func;
	};
	using container = std::vector<entry>;
	// clang-format off
	static const container messages = {
		ADD_MESSAGE(message_01),
		ADD_MESSAGE(message_02),
		ADD_MESSAGE(message_03),
		ADD_MESSAGE(message_04),
		ADD_MESSAGE(message_05),
		ADD_MESSAGE(message_11),
		ADD_MESSAGE(message_18),
		ADD_MESSAGE(message_21),
		ADD_MESSAGE(message_24)
	};
	// clang-format on
#undef ADD_MESSAGE

	using namespace marnav;

	try {
		auto m = ais::make_message(nmea::collect_payload(sentences.begin(), sentences.end()));
		auto i = std::find_if(std::begin(messages), std::end(messages),
			[&m](const container::value_type & item) { return item.id == m->type(); });
		if (i == std::end(messages)) {
			fmt::printf("%smessage_%02u%s\n\tnot implemented\n\n", terminal::magenta,
				static_cast<uint8_t>(m->type()), terminal::normal);
		} else {
			i->func(m.get());
			fmt::printf("\n");
		}
	} catch (std::exception & error) {
		fmt::printf("\t%serror:%s %s\n\n", terminal::red, terminal::normal, error.what());
	}
}

static void dump_stream(std::istream & is)
{
	using namespace marnav;

	std::vector<std::unique_ptr<nmea::sentence>> sentences;

	while (is) {
		std::string line;
		std::getline(is, line);
		line = trim(line);

		if (line.empty())
			continue;
		if (line[0] == '#')
			continue;

		if (line[0] == nmea::sentence::start_token) {
			dump_nmea(line);
		} else if (line[0] == nmea::sentence::start_token_ais) {
			fmt::printf("%s%s%s\n", terminal::blue, line, terminal::normal);
			auto s = nmea::make_sentence(line);

			nmea::vdm * v = nullptr; // VDM is the common denominator for AIS relevant messages

			if (s->id() == nmea::sentence_id::VDO) {
				v = nmea::sentence_cast<nmea::vdo>(s);
			} else if (s->id() == nmea::sentence_id::VDM) {
				v = nmea::sentence_cast<nmea::vdm>(s);
			} else {
				// something strange happened, no VDM nor VDO
				fmt::printf("%s%s%s\n\terror: ignoring AIS sentence, dropping collection.\n\n",
					terminal::red, line, terminal::normal);
				sentences.clear();
				continue;
			}

			// check sentences if a discontuniation has occurred
			if (sentences.size() && (sentences.back()->id() != v->id())) {
				sentences.clear(); // there was a discontinuation, start over collecting
				fmt::printf(
					"\t%swarning:%s dropping collection.\n", terminal::cyan, terminal::normal);
			}

			// check if a previous message was not complete
			const auto n_fragments = v->get_n_fragments();
			const auto fragment = v->get_fragment();
			if (sentences.size() >= fragment) {
				sentences.clear();
				fmt::printf(
					"\t%swarning:%s dropping collection.\n", terminal::cyan, terminal::normal);
			}

			sentences.push_back(std::move(s));
			if (fragment == n_fragments) {
				dump_ais(sentences);
				sentences.clear();
			}
		} else {
			fmt::printf("%s%s%s\n\terror: ignoring AIS sentence.\n\n", terminal::red, line,
				terminal::normal);
		}
	}
}

static void dump_file(const std::string & filename)
{
	std::ifstream ifs{filename.c_str()};
	dump_stream(ifs);
}

static void dump_port(const std::string &, uint32_t)
{
	throw std::runtime_error{"NOT IMPLEMENTED"};
}

static void dump_stdin() { dump_stream(std::cin); }
}

int main(int argc, char ** argv)
{
	using namespace nmeadump;

	if (parse_options(argc, argv))
		return EXIT_SUCCESS;

	if (!global.config.file.empty()) {
		dump_file(global.config.file);
	} else if (!global.config.port.empty()) {
		dump_port(global.config.port, global.config.port_speed);
	} else {
		dump_stdin();
	}

	return EXIT_SUCCESS;
}
