#include <type_traits>
#include <Framework/Input/MouseButton.h>

std::underlying_type<MouseButtons>::type operator *(const MouseButtons &button)
{
	return static_cast<std::underlying_type<MouseButtons>::type>(button);
}

MouseButtons operator |(const MouseButtons &a, const  MouseButtons &b)
{
	return static_cast<MouseButtons>(*a | *b);
}

MouseButtons operator &(const MouseButtons &a, const  MouseButtons &b)
{
	return static_cast<MouseButtons>(*a & *b);
}

MouseButtons operator ~(const MouseButtons &a)
{
	return static_cast<MouseButtons>(~*a);
}

MouseButtons& operator |=(MouseButtons &a, const  MouseButtons &b)
{
	a = a | b;
	return a;
}

MouseButtons& operator &=(MouseButtons &a, const  MouseButtons &b)
{
	a = a & b;
	return a;
}