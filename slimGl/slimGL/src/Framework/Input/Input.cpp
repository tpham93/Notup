/**********************************************************************************************
* 										include
**********************************************************************************************/
#include <algorithm>
#include<GL/glut.h>
#include <Framework/Input/Input.h>

/**********************************************************************************************
* 										class definition
**********************************************************************************************/
Input::Input(bool isVirtual, glm::ivec2 screenSize)
	:m_keyBuffer(),
	m_currentPressedKeys(),
	m_lastPressesKeys(),
	m_mousePositionBuffer(),
	m_currentMousePosition(),
	m_lastMousePosition(),
	m_mouseButtonBuffer(),
	m_currentPressedButtons(),
	m_lastPressedButtons(),
	m_mouseWheelBuffer(),
	m_currentMouseWheelValue(),
	m_lastMouseWheelValue(),
	m_isVirtual(isVirtual),
	m_screenSize(screenSize),
	m_outputMousePosition(screenSize/2),
	m_controller(std::make_unique<NvGamepadXInput>())
{
	if (isVirtual)
	{
	
	}
}
#include <iostream>
void Input::update()
{
	// get the old states to the variables for the last frame
	m_lastPressesKeys = m_currentPressedKeys;
	m_lastMousePosition = m_outputMousePosition;
	m_lastPressedButtons = m_currentPressedButtons;
	m_lastMouseWheelValue = m_currentMouseWheelValue;

	// get the current states from the buffer
	m_currentPressedKeys = m_keyBuffer;
	m_currentMousePosition = m_mousePositionBuffer;
	m_currentPressedButtons = m_mouseButtonBuffer;
	m_currentMouseWheelValue = m_mouseWheelBuffer;

	// reset the buffer
	m_keyBuffer = std::vector<char>(m_currentPressedKeys);
	/*
	not needed but for the completeness
	m_mousePositionBuffer = Point2(m_currentMousePosition);
	m_mouseButtonBuffer = m_currentPressedButtons;
	m_mouseWheelBuffer = m_mouseWheelBuffer;
	*/

	// capturing the mouse if it was specified so
	if (m_isVirtual)
	{
		m_outputMousePosition += getMouseMovement();
		setMousePosition(m_screenSize.x / 2, m_screenSize.y / 2, true, false, false);
		m_outputMousePosition.x = std::max(0, std::min(m_screenSize.x - 1, m_outputMousePosition.x));
		m_outputMousePosition.y = std::max(0, std::min(m_screenSize.y - 1, m_outputMousePosition.y));
	}
	else
	{
		m_outputMousePosition = m_currentMousePosition;
	}
}

void Input::updateKey(char key, bool state)
{
	// check whether the button is  clicked or released
	if (state)
	{
		// save the pressed key into the buffer
		m_keyBuffer.push_back(key);
	}
	else
	{
		// remove the key from the buffer
		m_keyBuffer.erase(std::remove(m_keyBuffer.begin(), m_keyBuffer.end(), key), m_keyBuffer.end());
	}

}

void Input::updateMousePosition(int x, int y)
{
	// save the mouseposition in the buffer
	m_mousePositionBuffer = glm::ivec2(x, y);
}

void Input::updateMouseButton(MouseButtons mouseButton, bool state)
{
	// check whether the button is released or clicked
	if (state)
	{
		// add the mousebutton to the buffer
		m_mouseButtonBuffer |= mouseButton;
	}
	else
	{
		// remove the mousebutton from the buffer
		m_mouseButtonBuffer &= ~mouseButton;
	}
}

void Input::updateMouseWheel(int dir)
{
	// add the direction to the mousewheel
	m_mouseWheelBuffer += dir;
}

std::vector<char> Input::getPressedKeys() const
{
	// return the currently pressed keys
	return m_currentPressedKeys;
}

bool Input::keyPressed(char key) const
{
	// check if the key is currently pressed
	return containsKey(m_currentPressedKeys, key);
}

bool Input::keyClicked(char key) const
{
	// check if the key is currently pressed and if the key was not pressed in the last frame
	return containsKey(m_currentPressedKeys, key) && !containsKey(m_lastPressesKeys, key);
}

bool Input::keyReleased(char key) const
{
	// check if the key is not currently pressed but in the last frame
	return !containsKey(m_currentPressedKeys, key) && containsKey(m_lastPressesKeys, key);
}

bool Input::mouseButtonPressed(MouseButtons buttons, bool allPressed) const
{
	// check if all buttons has to be pressed
	if (allPressed)
	{
		// check if there are all mousebuttons among the ones to check
		return (m_currentPressedButtons & buttons) == buttons;
	}
	else
	{
		// check if there is any mousebuttons among the ones to check
		return (m_currentPressedButtons & buttons) != MouseButtons::None;
	}
}

bool Input::mouseButtonClicked(MouseButtons buttons, bool allClicked) const
{
	// check if all buttons has to be clicked
	if (allClicked)
	{
		// check if there are all mousebuttons among the ones to check
		return ((m_currentPressedButtons & ~m_lastPressedButtons) & buttons) == buttons;
	}
	else
	{
		// check if there is any mousebuttons among the ones to check
		return ((m_currentPressedButtons &~m_lastPressedButtons) & buttons) != MouseButtons::None;
	}
}

bool Input::mouseButtonReleased(MouseButtons buttons, bool allReleased) const
{
	// check if all buttons has to be pressed
	if (allReleased)
	{
		// check if there are all mousebuttons among the ones to check
		return ((~m_currentPressedButtons & m_lastPressedButtons) & buttons) == buttons;
	}
	else
	{
		// check if there is any mousebuttons among the ones to check
		return ((~m_currentPressedButtons &m_lastPressedButtons) &buttons) != MouseButtons::None;
	}
}

bool Input::mouseMoved() const
{
	// check if the current position not equals the position of the last frame
	return m_isVirtual && m_currentMousePosition != m_screenSize / 2
		|| !m_isVirtual && m_currentMousePosition != m_lastMousePosition;
}

glm::ivec2 Input::getMousePosition() const
{
	// returns the current mouse position
	return m_outputMousePosition;
}

glm::vec2 Input::getMousePositionV2() const
{
	return glm::vec2(m_outputMousePosition);
}

glm::ivec2  Input::getMouseMovement() const
{
	if (m_isVirtual)
	{
		// returns the difference between the last mouseposition and the current mouse position
		return m_currentMousePosition - m_screenSize / 2;
	}
	else
	{
		return m_currentMousePosition - m_lastMousePosition;
	}
}

glm::vec2  Input::getMouseMovementV2() const
{
	// returns the difference between the last mouseposition and the current mouse position
	return glm::vec2(getMouseMovement());
}

MouseButtons Input::getPressedMouseButtons() const
{
	return static_cast<MouseButtons>(m_currentPressedButtons);
}

bool Input::mouseWheelMoved() const
{
	// check if the mousewheel value has changed
	return m_currentMouseWheelValue != m_lastMouseWheelValue;
}

int Input::getMouseWheelMovement() const
{
	// return difference of the current mousewheel value and the mousewheel value from the last frame
	return m_currentMouseWheelValue - m_lastMouseWheelValue;
}

bool Input::mouseWheelMovedUp() const
{
	// check if the mousemovement was bigger than 0
	return getMouseWheelMovement() > 0;
}

bool Input::mouseWheelMovedDown() const
{
	// check if the mousemovement was smaller than 0
	return getMouseWheelMovement() < 0;
}

int Input::getMouseWheelValue() const
{
	// return the current mousewheel value
	return m_currentMouseWheelValue;
}

bool Input::containsKey(std::vector<char> vect, char key) const
{
	// try to find the key and check if it is really inside
	return std::find(vect.begin(), vect.end(), key) != vect.end();
}

void Input::setMousePosition(int x, int y, bool resetMouseMovement, bool setVirtualMouse, bool setCurrentMousePosition)
{
	// set the mouse pointer
	glutWarpPointer(x, y);
	// reset the move movement
	if (resetMouseMovement)
	{
		m_lastMousePosition = glm::ivec2(x, y);
	}
	if (setVirtualMouse)
	{
		m_outputMousePosition = glm::ivec2(x,y);
	}
	// set the new mouse position
	if (setCurrentMousePosition)
	{
		m_currentMousePosition = glm::ivec2(x, y);
	}

}

NvGamepad::State Input::getControllerState(int controllerId)
{
	NvGamepad::State state;
	m_controller->getState(controllerId, state);
	return state;
}

bool Input::isControllerConnected(int controllerId)
{
	NvGamepad::State state;
	return m_controller->getState(controllerId, state);
}