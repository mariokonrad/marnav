#ifndef MARNAV__IO__SELECTABLE__HPP
#define MARNAV__IO__SELECTABLE__HPP

#include <marnav/marnav_export.h>

namespace marnav
{
namespace io
{
/// Provides an interface for access (in various publicty degrees) to
/// the file descriptor.
///
/// @example select.cpp
class MARNAV_EXPORT selectable
{
public:
	virtual ~selectable() {}

	/// Returns the filedescriptor.
	virtual int get_fd() const = 0;
};
}
}

#endif
