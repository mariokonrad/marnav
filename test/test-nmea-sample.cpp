#include <marnav/nmea/nmea.hpp>
#include <marnav/nmea/sentence.hpp>
#include <fstream>
#include <iostream>
#include <string>

namespace stackoverflow
{
// source:
// http://stackoverflow.com/questions/6089231/getting-std-ifstream-to-handle-lf-cr-and-crlf
//
// changes:
// - old-style C type cast changed to c++ cast
// - reformatting
// - renaming and put into the namespace
// - break inserted for the default option of switch
std::istream & getline(std::istream & is, std::string & t)
{
	t.clear();

	// The characters in the stream are read one-by-one using a std::streambuf.
	// That is faster than reading them one-by-one using the std::istream.
	// Code that uses streambuf this way must be guarded by a sentry object.
	// The sentry object performs various tasks,
	// such as thread synchronization and updating the stream state.

	std::istream::sentry se(is, true);
	std::streambuf * sb = is.rdbuf();

	for (;;) {
		int c = sb->sbumpc();
		switch (c) {
			case '\n':
				return is;
			case '\r':
				if (sb->sgetc() == '\n')
					sb->sbumpc();
				return is;
			case EOF:
				// Also handle the case when the last line has no line ending
				if (t.empty())
					is.setstate(std::ios::eofbit);
				return is;
			default:
				t += static_cast<char>(c);
				break;
		}
	}
}
}

namespace marnav_test
{
void process_nmea_sentence(
	const std::unique_ptr<marnav::nmea::sentence> & sentence, const std::string & line)
{
	using namespace marnav;
	using namespace std;

	// TODO: use `to_name()`
	switch (sentence->id()) {
		case nmea::sentence_id::AAM:
			cout << "AAM - Waypoint Arrival Alarm";
			break;
		case nmea::sentence_id::ALM:
			cout << "ALM - GPS Almanac Data";
			break;
		case nmea::sentence_id::APA:
			cout << "APA - Autopilot Sentence 'A'";
			break;
		case nmea::sentence_id::APB:
			cout << "APB - Autopilot Sentence 'B'";
			break;
		case nmea::sentence_id::BOD:
			cout << "BOD - Bearing - Waypoint to Waypoint";
			break;
		case nmea::sentence_id::BWC:
			cout << "BWC - Bearing & Distance to Waypoint - Geat Circle";
			break;
		case nmea::sentence_id::BWR:
			cout << "BWR - Bearing and Distance to Waypoint - Rhumb Line";
			break;
		case nmea::sentence_id::BWW:
			cout << "BWW - Bearing - Waypoint to Waypoint";
			break;
		case nmea::sentence_id::DBK:
			cout << "DBK - Depth Below Keel";
			break;
		case nmea::sentence_id::DBS:
			cout << "DBS - Depth Below Surface";
			break;
		case nmea::sentence_id::DBT:
			cout << "DBT - Depth below transducer (II)";
			break;
		case nmea::sentence_id::DCN:
			cout << "DCN - Decca Position";
			break;
		case nmea::sentence_id::DPT:
			cout << "DPT - Depth of Water";
			break;
		case nmea::sentence_id::DTM:
			cout << "DTM - Datum Reference";
			break;
		case nmea::sentence_id::FSI:
			cout << "FSI - Frequency Set Information";
			break;
		case nmea::sentence_id::GBS:
			cout << "GBS - GPS Satellite Fault Detection";
			break;
		case nmea::sentence_id::GGA:
			cout << "GGA - Global Positioning System Fix Data";
			break;
		case nmea::sentence_id::GLC:
			cout << "GLC - Geographic Position, Loran-C";
			break;
		case nmea::sentence_id::GLL:
			cout << "GLL - Geographic Position - Latitude/Longitude";
			break;
		case nmea::sentence_id::GNS:
			cout << "GNS - Fix data";
			break;
		case nmea::sentence_id::GRS:
			cout << "GRS - GPS Range Residuals";
			break;
		case nmea::sentence_id::GST:
			cout << "GST - GPS Pseudorange Noise Statistics";
			break;
		case nmea::sentence_id::GSA:
			cout << "GSA - GPS DOP and active satellites";
			break;
		case nmea::sentence_id::GSV:
			cout << "GSV - Satellites in view";
			break;
		case nmea::sentence_id::GTD:
			cout << "GTD - Geographic Location in Time Differences";
			break;
		case nmea::sentence_id::GXA:
			cout << "GXA - TRANSIT Position - Latitude/Longitude";
			break;
		case nmea::sentence_id::HDG:
			cout << "HDG - Heading - Deviation & Variation (vendor extension)";
			break;
		case nmea::sentence_id::HDM:
			cout << "HDM - Heading - Magnetic";
			break;
		case nmea::sentence_id::HDT:
			cout << "HDT - Heading - True";
			break;
		case nmea::sentence_id::HFB:
			cout << "HFB - Trawl Headrope to Footrope and Bottom";
			break;
		case nmea::sentence_id::HSC:
			cout << "HSC - Heading Steering Command";
			break;
		case nmea::sentence_id::ITS:
			cout << "ITS - Trawl Door Spread 2 Distance";
			break;
		case nmea::sentence_id::LCD:
			cout << "LCD - Loran-C Signal Data";
			break;
		case nmea::sentence_id::MSK:
			cout << "MSK - Control for a Beacon Receiver";
			break;
		case nmea::sentence_id::MSS:
			cout << "MSS - Beacon Receiver Status";
			break;
		case nmea::sentence_id::MWD:
			cout << "MWD - Wind Directinon and Speed";
			break;
		case nmea::sentence_id::MTA:
			cout << "MTA - Air Temperature";
			break;
		case nmea::sentence_id::MTW:
			cout << "MTW - Mean Temperature of Water (II)";
			break;
		case nmea::sentence_id::MWV:
			cout << "MWV - Wind Speed and Angle (II)";
			break;
		case nmea::sentence_id::OLN:
			cout << "OLN - Omega Lane Numbers";
			break;
		case nmea::sentence_id::OSD:
			cout << "OSD - Own Ship Data";
			break;
		case nmea::sentence_id::R00:
			cout << "R00 - Waypoints in active route";
			break;
		case nmea::sentence_id::RMA:
			cout << "RMA - Recommended Minimum Navigation Information";
			break;
		case nmea::sentence_id::RMB:
			cout << "RMB - Recommended Minimum Navigation Information";
			break;
		case nmea::sentence_id::RMC:
			cout << "RMC - Recommended Minimum Navigation Information";
			break;
		case nmea::sentence_id::ROT:
			cout << "ROT - Rate Of Turn";
			break;
		case nmea::sentence_id::RPM:
			cout << "RPM - Revolutions";
			break;
		case nmea::sentence_id::RSA:
			cout << "RSA - Rudder Sensor Angle";
			break;
		case nmea::sentence_id::RSD:
			cout << "RSD - RADAR System Data";
			break;
		case nmea::sentence_id::RTE:
			cout << "RTE - Routes";
			break;
		case nmea::sentence_id::SFI:
			cout << "SFI - Scanning Frequency Information";
			break;
		case nmea::sentence_id::STN:
			cout << "STN - Multiple Data ID";
			break;
		case nmea::sentence_id::TDS:
			cout << "TDS - Trawl Door Spread Distance";
			break;
		case nmea::sentence_id::TFI:
			cout << "TFI - Trawl Filling Indicator";
			break;
		case nmea::sentence_id::TPC:
			cout << "TPC - Trawl Position Cartesian Coordinates";
			break;
		case nmea::sentence_id::TPR:
			cout << "TPR - Trawl Position Relative Vessel";
			break;
		case nmea::sentence_id::TPT:
			cout << "TPT - Trawl Position True";
			break;
		case nmea::sentence_id::TRF:
			cout << "TRF - TRANSIT Fix Data";
			break;
		case nmea::sentence_id::TTM:
			cout << "TTM - Tracked Target Message";
			break;
		case nmea::sentence_id::VBW:
			cout << "VBW - Dual Ground/Water Speed";
			break;
		case nmea::sentence_id::VDR:
			cout << "VDR - Set and Drift";
			break;
		case nmea::sentence_id::VHW:
			cout << "VHW - Water speed and heading (II)";
			break;
		case nmea::sentence_id::VLW:
			cout << "VLW - Distance Traveled through Water (II)";
			break;
		case nmea::sentence_id::VPW:
			cout << "VPW - Speed - Measured Parallel to Wind";
			break;
		case nmea::sentence_id::VTG:
			cout << "VTG - Track made good and Ground speed";
			break;
		case nmea::sentence_id::VWR:
			cout << "VWR - Relative Wind Speed and Angle (II)";
			break;
		case nmea::sentence_id::WCV:
			cout << "WCV - Waypoint Closure Velocity";
			break;
		case nmea::sentence_id::WDR:
			cout << "WDR - Distance to Waypoint, Rumb line";
			break;
		case nmea::sentence_id::WNC:
			cout << "WNC - Distance - Waypoint to Waypoint";
			break;
		case nmea::sentence_id::WPL:
			cout << "WPL - Waypoint Location";
			break;
		case nmea::sentence_id::XDR:
			cout << "XDR - Transducer Measurement";
			break;
		case nmea::sentence_id::XTE:
			cout << "XTE - Cross-Track Error, Measured";
			break;
		case nmea::sentence_id::XTR:
			cout << "XTR - Cross Track Error - Dead Reckoning";
			break;
		case nmea::sentence_id::ZDA:
			cout << "ZDA - Time & Date - UTC, day, month, year and local time zone";
			break;
		case nmea::sentence_id::ZFO:
			cout << "ZFO - UTC & Time from origin Waypoint";
			break;
		case nmea::sentence_id::ZTG:
			cout << "ZTG - UTC & Time to Destination Waypoint";
			break;
		case nmea::sentence_id::PGRME:
			cout << "PGRME - Estimated Error Information (Garmin Extension)";
			break;
		case nmea::sentence_id::PGRMM:
			cout << "PGRMM - Map Datum (Garmin Extension)";
			break;
		case nmea::sentence_id::PGRMZ:
			cout << "PGRMZ - Altitude (Garmin Extension)";
			break;
		case nmea::sentence_id::VWT:
			cout << "VWT - wind true";
			break;
		case nmea::sentence_id::VDM:
			cout << "VDM - AIS";
			break;
		case nmea::sentence_id::VDO:
			cout << "VDO - AIS";
			break;
		default:
			cout << "NMEA unknown: " << line << "\n";
			break;
	}
	cout << "\n";
}
}

int main(int, char **)
{
	using namespace marnav;

	std::ifstream ifs{"nmea-sample.txt"};
	std::string line;

	// this function implements almost the same as examples/read_ais.cpp

	while (stackoverflow::getline(ifs, line)) {
		try {
			if (line.empty())
				continue;

			if (line[0] == '#')
				continue;

			auto sentence = nmea::make_sentence(line);
			marnav_test::process_nmea_sentence(sentence, line);
		} catch (nmea::unknown_sentence & e) {
			std::cout << "NMEA unknown: " << e.what() << ": " << line << "\n";
		} catch (std::exception & e) {
			std::cout << "NMEA error: " << e.what() << " in sentence: " << line << "\n";
		}
	}

	return 0;
}
