#include <iostream>
#include <set>
#include <stdint.h>

using std::cout;
using std::endl;

// Any specialization of EnableType, execpt for the explicit int64_t
// specialization below, will fall here and fail to compile due to
// the missing "type" member.
template <typename T>
struct EnableType
{
};

template <>
struct EnableType<int64_t>
{
	typedef int64_t type;
};

template <typename T>
class MyClass
{
public:
	std::set<typename EnableType<T>::type> s;
};

int main()
{
	MyClass<int64_t> c;
	//MyClass<int32_t> c2; // this will fail to compile
	c.s.insert(1);
	c.s.insert(3);
	int32_t size = static_cast<int32_t>(c.s.size());
	cout << "Set size = " << size << endl;
	return 0;
}
