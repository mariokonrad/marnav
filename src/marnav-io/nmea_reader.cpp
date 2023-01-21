#include <marnav-io/nmea_reader.hpp>
#include <algorithm>
#include <stdexcept>

namespace marnav::io
{
/// Initializes the reader, opens the device (if valid).
///
/// @param[in] d The device to read data from, will be opened.
nmea_reader::nmea_reader(std::unique_ptr<device> && d)
	: dev_(std::move(d))
{
	sentence_.reserve(nmea::sentence::max_length + 1);
	if (dev_)
		dev_->open();
}

void nmea_reader::close()
{
	if (dev_)
		dev_->close();
	dev_.reset();
}

/// Reads data from the device.
///
/// @retval true  Success.
/// @retval false End of file.
/// @exception std::runtime_error The device was invalid or read error.
bool nmea_reader::read_data()
{
	if (!dev_)
		throw std::runtime_error{"device invalid"};
	int rc = dev_->read(&raw_, sizeof(raw_));
	if (rc == 0)
		return false;
	if (rc < 0)
		throw std::runtime_error{"read error"};
	if (rc != sizeof(raw_))
		throw std::runtime_error{"read error"};
	return true;
}

/// Processes the data read from the device.
///
/// @exception std::length_error Too many characters read for the sentence.
///   Maybe the end of line was missed or left out.
void nmea_reader::process_nmea()
{
	switch (raw_) {
		case '\r':
			break;
		case '\n': // end of sentence
			process_sentence(sentence_);
			sentence_.clear();
			break;
		default:
			// ignore invalid characters. if this makes the sentence incomplete,
			// the sentence would have been invalid anyway. the result will be
			// an invalid sentence or a std::length_error.
			if ((raw_ < 32) || (raw_ >= 127))
				return;

			if (sentence_.size() > nmea::sentence::max_length)
				throw std::length_error{"sentence size to large. receiving NMEA data?"};
			sentence_ += raw_;
			break;
	}
}

/// Reads data from the device and processes it. If a complete NMEA
/// sentence was received the method process_message will be executed.
/// This method automatcially synchronizes with NMEA data.
///
/// @retval true  Success.
/// @retval false End of file.
/// @exception std::runtime_error Device or processing error.
/// @exception std::length_error Synchronization issue.
bool nmea_reader::read()
{
	if (!read_data())
		return false;
	process_nmea();
	return true;
}
}
