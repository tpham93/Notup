#pragma once

/**********************************************************************************************
* 										declaration
**********************************************************************************************/


/*!
* 	\brief	enum to specify the mousebutton for the input class
* 			can be used to specify multiple mousebuttons like : (LeftMouseButton | MiddleMouseButton) to check both buttons
*/
enum class MouseButtons : unsigned int
{
	None = 0,
	LeftMouseButton = 1 << 0,
	MiddleMouseButton = 1 << 1,
	RightMouseButton = 1 << 2,
	LMMouseButton = LeftMouseButton | MiddleMouseButton,
	LRMouseButton = LeftMouseButton | RightMouseButton,
	MRMouseButton = MiddleMouseButton | RightMouseButton,
	LMRMouseButton = LeftMouseButton | MiddleMouseButton | RightMouseButton,
};

/*
*	\brief			convert buttons into the underlying representation
*	\param button	the button which should be converted
*	\return			the internal representation of button
*/
std::underlying_type<MouseButtons>::type operator *(const MouseButtons &button);

/*
*	\brief		bitwise orring of both button constellation
*	\param a	the first button constellation
*	\param b	the second button constellation
*	\return		the buttons, as if a and b were pressed together
*/
MouseButtons operator |(const MouseButtons &a, const  MouseButtons &b);

/*
*	\brief		bitwise and for both buttons
*	\param a	the first button constellation
*	\param b	the second button constellation
*	\return		the buttons, as if only the buttons were pressed, which are pressed in a and b
*/
MouseButtons operator &(const MouseButtons &a, const  MouseButtons &b);

/*
*	\brief		bitwise not for the button constellation
*	\param a	all pressed buttons
*	\return		inverted pressed buttons
*/
MouseButtons operator ~(const MouseButtons &a);

/*
*	\brief		bitwise orring of both button constellation with an assignment
*	\param a	the first button constellation
*	\param b	the second button constellation
*	\return		the buttons, as if a and b were pressed together
*/
MouseButtons& operator |=(MouseButtons &a, const  MouseButtons &b);

/*
*	\brief		bitwise orring of both button constellation with an assignment
*	\param a	the first button constellation
*	\param b	the second button constellation
*	\return		the buttons, as if a and b were pressed together
*/
MouseButtons& operator &=(MouseButtons &a, const  MouseButtons &b);