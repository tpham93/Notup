#pragma once

#include <Game/Gamestates/Gamestate.h>
#include <Framework/Shader/ShaderProgram.h>
#include <Framework/Drawable/Sprite.h>
#include <Framework/Drawable/Text.h>
#include <Game/GameComponents/World.h>
#include <Game/GameComponents/Entities/Player.h>

class ActualGame : public Gamestate
{
public:
	ActualGame(std::shared_ptr<Input>input, const GameTime &gameTime, glm::ivec2 &windowSize, std::shared_ptr<ShaderProgram> textureShader);
	~ActualGame();
	virtual bool initialize();
	virtual bool loadContent();
	virtual GamestateType update();
	virtual void draw();
	virtual GamestateType getGamestateType() const;

private:
	std::shared_ptr<Entity> m_player;
	std::shared_ptr<ShaderProgram> m_textureShader;
	std::map<std::string, std::shared_ptr<Texture>> tileTextures;
	std::map<std::string, bool> tileCollidingInformation;
	World m_world;
};