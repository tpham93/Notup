#pragma once

#include<vector>
#include<Framework/Game/GameTime.h>
#include<glm/glm.hpp>

#include<Game/GameComponents/Entities/Entity.h>
#include <map>
#include <set>
#include <Framework/Input/Input.h>
#include <Framework/Shader/ShaderProgram.h>

class World
{
public:
	World(std::shared_ptr<ShaderProgram> textureShader, glm::ivec2 m_windowSize);

	void loadMap(const std::string &backgroundPath, std::map<std::string, std::shared_ptr<Texture>> &tileTextures, std::map<std::string, bool> &tileCollidingInformation, std::shared_ptr<Input> input);

	void addPlayer(std::shared_ptr<Entity> e);

	void addEntity(std::shared_ptr<Entity> e);

	void addItem(std::shared_ptr<Entity> e);

	void addLight(std::shared_ptr<Entity> e);

	std::shared_ptr<Entity> getPlayer();

	void update(const GameTime& gameTime);

	void draw();

	glm::ivec2 worldToTile(glm::vec2 pos);

	glm::vec2 tileToWorld(glm::ivec2 pos);

	unsigned int tileToIndex(glm::ivec2 pos);

	void deleteDeadEntities();

	void deleteDeadEntities(std::vector<std::shared_ptr<Entity>> &entities);
private:
	std::shared_ptr<ShaderProgram> m_textureShader;
	std::shared_ptr<ShaderProgram> m_lightShader;
	std::shared_ptr<ShaderProgram> m_mergeLightShader;
	std::shared_ptr<Entity> m_player;
	std::vector<std::shared_ptr<Entity>> m_entities;
	std::vector<std::shared_ptr<Entity>> m_items;
	std::vector<std::shared_ptr<Entity>> m_updateableEntities;
	std::vector<std::shared_ptr<Entity>> m_light;
	std::vector<std::shared_ptr<Entity>> m_background;
	std::vector<bool> m_backgroundColliding;
	glm::ivec2 m_size;
	glm::ivec2 m_windowSize;

	static const unsigned int FRAMEBUFFER_NUM = 2;
	glm::ivec2 m_framebufferSize;
	GLuint m_framebufferId[FRAMEBUFFER_NUM];
	Sprite m_framebufferSprite[FRAMEBUFFER_NUM];
	std::shared_ptr<Texture> m_framebufferTexture[FRAMEBUFFER_NUM];

	Sprite m_playerSightField;
};