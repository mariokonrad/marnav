#ifndef MARNAV_VERISION_HPP
#define MARNAV_VERISION_HPP

namespace marnav
{
struct meta {
	const char * version_major;
	const char * version_minor;
	const char * version_patch;
	const char * project_version;
	const char * project_name;
};

meta get_meta() noexcept;
}

#endif
