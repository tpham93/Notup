#pragma once


/********************************************************************************************** 
* 										includes
**********************************************************************************************/

#include <vector>
#include <glm/glm.hpp>
#include <Framework/Input/MouseButton.h>
#include <memory>
#include <NvGamepad/NvGamepad.h>
#include <NvGamepad/NvGamepadXInput.h>

/********************************************************************************************** 
* 										class declaration
**********************************************************************************************/

/*!!
* 	\brief	a input handler to catch all the key presses,
* 			mousebutton presses and mouse motion
*/
class Input
{
public:

	/*!
	* 	\brief				standard constructor
	*	\param isVirtual	true if the mouse cursor should be captured at each frame
	*/
	Input(bool isVirtual = true, glm::ivec2 screenSize = glm::ivec2(0));

	/*!
	* 	\brief	process all received input
	* 	\pre	correct initialized input
	* 	\post	the keys from the last frame will be set as the prssed/released ones
	*/
	void update();

	/*!
	* 	\brief			add a button to the button which got pressed this frame
	* 	\param key		the char corresponding to the key
	* 	\param state	if true the key is indicated as pressed
	*/
	void updateKey(char key, bool state);

	/*!
	* 	\brief		sets the new mouse position
	* 	\param x	the x coordinate of the mouse
	* 	\param y	the y coordinate of the mouse
	*/
	void updateMousePosition(int x, int y);

	/*!
	* 	\brief			sets the new mouse position
	* 	\param button	the button you want to update the state
	* 	\param state	the flag indicates if the button was pressed or released
	* 	\param state	if true the button is indicated as pressed otherwise as released
	*/
	void updateMouseButton(MouseButtons button, bool state);

	/*!
	* 	\brief		updates the mousewheel
	* 	\param dir	the direction of the mousewheel
	*/
	void updateMouseWheel(int dir);

	/*!
	* 	\brief	get pressed keys
	* 	\return the pressed keys
	*/
	std::vector<char> getPressedKeys() const;

	/*!
	* 	\brief check if the key is pressed
	* 	\param key the keycode corresponding to the key you want to check
	* 	\return true if the key is pressed
	*/
	bool keyPressed(char key) const;

	/*!
	* 	\brief check if the key is clicked
	* 	\param key the keycode corresponding to the key you want to check
	* 	\return true if the key is clicked
	*/
	bool keyClicked(char key) const;

	/*!
	* 	\brief check if the key is released
	* 	\param key the keycode corresponding to the key you want to check
	* 	\return true if the key is released
	*/
	bool keyReleased(char key) const;

	/*!
	* 	\brief check if mouseButton(s) is pressed
	* 	\param buttons the mousebuttons
	* 	\param allPressed a flag to modify the output if true all buttons have to be pressed simultaneously otherwise at least one button has to be pressed
	* 	\return true if the mouseButton(s) is pressed
	*/
	bool mouseButtonPressed(MouseButtons buttons, bool allPressed = false) const;

	/*!
	* 	\brief check if mouseButton(s) is clicked
	* 	\param buttons the mousebuttons
	* 	\param allClicked a flag to modify the output if true all buttons have to be pressed simultaneously otherwise at least one button has to be clicked
	* 	\return true if the mouseButton(s) is clicked
	*/
	bool mouseButtonClicked(MouseButtons buttons, bool allClicked = false) const;

	/*!
	* 	\brief check if mouseButton(s) is released
	* 	\param buttons the mousebuttons
	* 	\param allReleased a flag to modify the output if true all buttons have to be pressed simultaneously otherwise at least one button has to be released
	* 	\return true if the mouseButton(s) is released
	*/
	bool mouseButtonReleased(MouseButtons buttons, bool allReleased = false) const;

	/*!
	* 	\brief checks if the mouse has moved in the last frame
	* 	\return true if the mouse has moved
	*/
	bool mouseMoved() const;

	/*!
	* 	\brief get the mouse position
	* 	\return the current mouse position
	*/
	glm::ivec2 getMousePosition() const;

	/*!
	* 	\brief get the mouse position
	* 	\return the current mouse position
	*/
	glm::vec2 getMousePositionV2() const;

	/*!
	* 	\brief get the mouse position
	* 	\return the current mouse movement
	*/
	glm::ivec2 getMouseMovement() const;

	/*!
	* 	\brief get the mouse position
	* 	\return the current mouse movement
	*/
	glm::vec2 getMouseMovementV2() const;

	/*!
	* 	\brief get the mouse buttons
	* 	\return the current pressed mousebuttons
	*/
	MouseButtons getPressedMouseButtons() const;

	/*!
	* 	\brief checks if the mousewheel has moved in the last frame
	* 	\return true if the mousewheel has moved
	*/
	bool mouseWheelMoved() const;

	/*!
	* 	\brief checks if the mousewheel has moved up in the last frame
	* 	\return true if the mousewheel has moved
	*/
	bool mouseWheelMovedUp() const;

	/*!
	* 	\brief checks if the mousewheel has moved down in the last frame
	* 	\return true if the mousewheel has moved
	*/
	bool mouseWheelMovedDown() const;

	/*!
	* 	\brief get the mousewheel movement
	* 	\return the current mousewheel movement
	*/
	int getMouseWheelMovement() const;

	/*!
	* 	\brief get the mousewheel value
	* 	\return the current mousewheel value
	*/
	int getMouseWheelValue() const;

	/*!
	* 	\brief						set the mouse position
	* 	\param x					the new x coordinate of the mouse
	* 	\param y					the new y coordinate of the mouse
	* 	\param resetMouseMovement	if true the movement change of the mouse will be (0/0)
	* 	\param setVirtualMouse		if true the virtual cursor will be set too
	* 	\param setMouseMovement		if true the current cursor position should be set too
	*/
	void setMousePosition(int x, int y, bool resetMouseMovement, bool setVirtualMouse = true, bool setCurrentMousePosition = true);

	/*!
	* 	\brief		get the state of a controller
	*	\param id	the id of the controller
	*	\return state of the controller
	*/
	NvGamepad::State getControllerState(int controllerId);

	/*!
	* 	\brief		check if a controller is connected
	*	\param id	the id of the controller
	*	\return true if connected
	*/
	bool isControllerConnected(int controllerId);

private:

	/*!
	* 	\brief check if the key is inside of the vector
	* 	\param vect the vector you want to sarch
	* 	\param key the key you want to know if the vect contains it
	* 	\return true if vect contains the key
	*/
	bool containsKey(std::vector<char> vect, char key) const;

	//!	vectors to store the pressed keys
	std::vector<char> m_keyBuffer;
	std::vector<char> m_currentPressedKeys;
	std::vector<char> m_lastPressesKeys;

	//!	points to store the mouse positions
	glm::ivec2 m_mousePositionBuffer;
	glm::ivec2 m_currentMousePosition;
	glm::ivec2 m_lastMousePosition;

	//!	chars to store the mouse press
	MouseButtons m_mouseButtonBuffer;
	MouseButtons m_currentPressedButtons;
	MouseButtons m_lastPressedButtons;

	//!	ints to store the mousewheel value
	int m_mouseWheelBuffer;
	int m_currentMouseWheelValue;
	int m_lastMouseWheelValue;

	//! capturing the mouse inside of the window
	bool m_isVirtual;
	glm::ivec2 m_screenSize;
	glm::ivec2 m_outputMousePosition;

	//! conntroller
	std::unique_ptr<NvGamepad> m_controller;
};
