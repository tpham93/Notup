#pragma once

#include <Game/Gamestates/Gamestate.h>
#include <Framework/Shader/ShaderProgram.h>
#include <Framework/Drawable/Sprite.h>
#include <Framework/Drawable/Text.h>

class Menu : public Gamestate
{
public:
	Menu(std::shared_ptr<Input>input, const GameTime &gameTime, glm::ivec2 &windowSize, std::shared_ptr<ShaderProgram> textureShader);
	virtual bool initialize();
	virtual bool loadContent();
	virtual GamestateType update();
	virtual void draw();
	virtual GamestateType getGamestateType() const;

private:
	std::shared_ptr<ShaderProgram> m_textureShader;
	Text m_textMainMenu;
	Text m_textKey;
	Sprite m_arrow;
	glm::vec2 m_arrowStartPosition;
};