#include <marnav-io/device.hpp>
#include <marnav-io/selectable.hpp>
#include <memory>
#include <iostream>
#include <vector>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

namespace marnav_example
{
/// A named pipe, implementing device and selectable for demonstration purposes.
///
/// @note The created FIFO will not be removed.
class pipe : public marnav::io::device, virtual public marnav::io::selectable
{
	friend class selector;

public:
	pipe(std::string filename)
		: fd(-1)
		, filename(filename)
	{
	}

	virtual ~pipe() { close(); }

	void create() { ::mkfifo(filename.c_str(), 0666); }

	void open_read()
	{
		if (fd >= 0)
			return;
		fd = ::open(filename.c_str(), O_RDONLY | O_NONBLOCK);
	}

	void open_write()
	{
		if (fd >= 0)
			return;
		fd = ::open(filename.c_str(), O_WRONLY | O_NONBLOCK);
	}

	void open_read_write()
	{
		if (fd >= 0)
			return;
		fd = ::open(filename.c_str(), O_RDWR | O_NONBLOCK);
	}

	virtual void close() override
	{
		if (fd < 0)
			return;
		::close(fd);
		fd = -1;
	}

	virtual int read(char * buffer, uint32_t size) override
	{
		if (!buffer)
			throw std::invalid_argument{"buffer"};
		if (fd < 0)
			throw std::runtime_error{"pipe not open"};

		return ::read(fd, buffer, size);
	}

	virtual int write(const char * buffer, uint32_t size) override
	{
		if (!buffer)
			throw std::invalid_argument{"buffer"};
		if (fd < 0)
			throw std::runtime_error{"pipe not open"};

		return ::write(fd, buffer, size);
	}

protected:
	virtual void open() override {}
	virtual int get_fd() const override { return fd; }

private:
	int fd;
	std::string filename;
};

class selector
{
public:
	std::vector<std::shared_ptr<marnav::io::selectable>> operator()(
		const std::vector<std::shared_ptr<marnav::io::selectable>> & devices)
	{
		return select(devices);
	}

	static std::vector<std::shared_ptr<marnav::io::selectable>> select(
		const std::vector<std::shared_ptr<marnav::io::selectable>> & devices)
	{
		std::vector<std::shared_ptr<marnav::io::selectable>> result;

		if (devices.size() == 0)
			return result;

		// fill filedescriptor set for reading
		fd_set rfds;
		FD_ZERO(&rfds);
		int max_fd = -1;
		for (auto const & dev : devices) {
			auto fd = dev->get_fd();
			FD_SET(fd, &rfds);
			if (fd > max_fd)
				max_fd = fd;
		}

		// the actual select
		auto rc = ::select(max_fd + 1, &rfds, 0, 0, 0);
		if (rc < 0)
			throw std::runtime_error{"select"};

		// find out which device has caused the wakeup
		result.reserve(rc);
		for (auto const & dev : devices) {
			if (FD_ISSET(dev->get_fd(), &rfds)) {
				result.push_back(dev);
			}
		}
		return result;
	}
};
}

int main(int, char **)
{
	// create a named pipe
	auto dev0 = std::make_shared<marnav_example::pipe>("/tmp/foobar");
	dev0->create();
	dev0->open_read();

	// open it a second time as different device
	auto dev1 = std::make_shared<marnav_example::pipe>("/tmp/foobar");
	dev1->open_read_write();

	// write some data
	dev1->write("foo\0", 4);

	// wait on named pipe, receive and print data
	auto devs = marnav_example::selector::select({dev0});
	if (devs.size() == 0) {
		std::cout << "no devices ready for read, probably timeout\n";
		return -1;
	}

	for (auto & dev : devs) {
		char buffer[128];
		int rc = -1;

		if (dev0 == dev) {
			rc = dev0->read(buffer, sizeof(buffer));
		}
		if (dev1 == dev) {
			rc = dev1->read(buffer, sizeof(buffer));
		}

		if (rc > 0) {
			std::cout << "received: " << buffer << "\n";
		}
	}
	return 0;
}
