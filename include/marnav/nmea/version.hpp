#ifndef MARNAV_NMEA_VERSION_HPP
#define MARNAV_NMEA_VERSION_HPP

#include <limits>
#include <cstdint>

namespace marnav::nmea
{
class version
{
public:
	using value_type = uint32_t;

	version() = default;

	constexpr version(value_type major, value_type minor) noexcept
		: major_(major)
		, minor_(minor)
	{
	}

	constexpr version(const version &) noexcept = default;
	constexpr version & operator=(const version &) noexcept = default;

	constexpr version(version &&) noexcept = default;
	constexpr version & operator=(version &&) noexcept = default;

	constexpr value_type major() const noexcept { return major_; }
	constexpr value_type minor() const noexcept { return minor_; }

	constexpr bool operator==(const version & other) const
	{
		return (major_ == other.major_) && (minor_ == other.minor_);
	}

	constexpr bool operator!=(const version & other) const noexcept
	{
		return !(*this == other);
	}

	constexpr bool operator<(const version & other) const noexcept
	{
		return (major_ < other.major_) || ((major_ == other.major_) && (minor_ < other.minor_));
	}

	constexpr bool operator<=(const version & other) const noexcept
	{
		return (*this == other) || (*this < other);
	}

	constexpr bool operator>(const version & other) const noexcept { return !(*this <= other); }

	constexpr bool operator>=(const version & other) const noexcept { return !(*this < other); }

	static constexpr version latest() noexcept
	{
		return {std::numeric_limits<value_type>::max(), std::numeric_limits<value_type>::max()};
	}

private:
	value_type major_ = 0;
	value_type minor_ = 0;
};
}

#endif
