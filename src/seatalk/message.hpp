#ifndef __SEATALK__MESSAGE__HPP__
#define __SEATALK__MESSAGE__HPP__

#include <vector>
#include <functional>
#include <utils/unique.hpp>

namespace seatalk
{

enum class message_id : uint8_t {
	depth_below_transducer = 0,
	equipment_id = 1,
};

using raw = std::vector<uint8_t>;

class message
{
public:
	using parse_function = std::function<std::unique_ptr<message>(const raw&)>;

	message_id type() const;
	virtual raw get_data() const = 0;

protected:
	message(message_id id);

private:
	message_id message_type;
};

template <class T> std::unique_ptr<T> message_cast(std::unique_ptr<message>& s)
{
	if (!s)
		return nullptr;
	if (s->type() != T::ID)
		return nullptr;

	return std::unique_ptr<T>{static_cast<T*>(s.release())};
}

}

#endif
