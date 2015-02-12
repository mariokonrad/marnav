#include <iostream>
#include <algorithm>

namespace nmea
{

template <class T> class optional
{
public:
	using value_type = T;

	constexpr optional()
		: flag(false)
		, data()
	{
	}

	constexpr optional(const T& data)
		: flag(true)
		, data(data)
	{
	}

	constexpr optional(T&& data)
		: flag(true)
		, data(std::move(data))
	{
	}

	optional(optional&&) = default;
	optional(const optional&) = default;

	void reset()
	{
		data = T{};
		flag = false;
	}

	bool available() const { return flag; }
	explicit operator bool() const { return flag; }

	constexpr const T& value() const { return data; }
	T& value() { return data; }

	optional& operator=(const optional& other)
	{
		this->data = other.data;
		this->flag = other.flag;
		return *this;
	}

	optional& operator=(optional&& other)
	{
		this->data = std::move(other.data);
		this->flag = std::move(other.flag);
		return *this;
	}

	template <class U>
	optional& operator=(U&& data)
	{
		this->data = std::move(data);
		flag = true;
		return *this;
	}

	constexpr const T* operator->() const { return &data; }
	T* operator->() { return &data; }
	constexpr const T& operator*() const { return data; }
	T& operator*() { return data; }

private:
	bool flag;
	T data;
};


class latitude
{
public:
	latitude() = default;

	latitude(double value)
		: value(value)
	{
	}

	friend std::string to_string(const latitude&);

private:
	double value;
};

template <class T>
std::string to_string(const optional<T>& v)
{
	using namespace std;
	if (v)
		return to_string(v.value());
	return std::string{};
}

std::string to_string(const latitude& lat)
{
	return std::to_string(lat.value);
}

}

static void test_memcpy(double value)
{
	using std::cout;
	using namespace nmea;

	optional<latitude> lat1;
	optional<latitude> lat2;

	if (value != 0.0)
		lat1 = value;

	cout << "\n";
	cout << "size lat   : " << sizeof(lat1) << "\n";
	cout << "size double: " << sizeof(double) << "\n";
	char buf[256];

	std::fill_n(buf, sizeof(buf), 0);
	std::copy_n(reinterpret_cast<char*>(&lat1), sizeof(lat1), buf);
	std::copy_n(buf, sizeof(lat2), reinterpret_cast<char*>(&lat2));

	cout << "lat1: " << lat1.available() << " / " << to_string(lat1) << "\n";
	cout << "lat2: " << lat2.available() << " / " << to_string(lat2) << "\n";
}

int main(int, char**)
{
	using std::cout;

	nmea::optional<double> head;
	cout << head.available() << " / " << head.value() << "\n";
	head = 5.0;
	cout << head.available() << " / " << head.value() << "\n";
	head = 6.0;
	cout << head.available() << " / " << head.value() << "\n";
	head.reset();
	cout << head.available() << " / " << head.value() << "\n";
	double tmp = head.value();
	cout << "tmp = " << tmp << "\n";
	head = 3.2;
	tmp = head.value();
	cout << "tmp = " << tmp << "\n";

	nmea::optional<double> sog{5.5};
	cout << sog.available() << " / " << sog.value() << "\n";

	using namespace nmea;

	optional<latitude> lat0;
	cout << lat0.available() << " / " << to_string(lat0) << "\n";
	optional<latitude> lat1(47.345);
	cout << lat1.available() << " / " << to_string(lat1) << "\n";
	lat1 = latitude(35.67);
	cout << lat1.available() << " / " << to_string(lat1) << "\n";
	lat1.reset();
	cout << lat1.available() << " / " << to_string(lat1) << "\n";

	test_memcpy(0.0);
	test_memcpy(34.56);

	return 0;
}
