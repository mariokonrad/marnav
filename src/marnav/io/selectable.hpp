#ifndef __IO__SELECTABLE__HPP__
#define __IO__SELECTABLE__HPP__

namespace marnav
{
namespace io
{
/// Provides an interface for access (in various publicty degrees) to
/// the file descriptor.
///
/// @example select.cpp
class selectable
{
public:
	/// Returns the filedescriptor.
	virtual int get_fd() const = 0;
};
}
}

#endif
