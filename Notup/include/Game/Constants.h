#pragma once

#include <glm/glm.hpp>

namespace Constants
{
	const unsigned int TILE_DIMENSION = 32;
	const float TILE_DIMENSION_F = static_cast<float>(TILE_DIMENSION);
	const glm::ivec2 TILE_SIZE_I = glm::ivec2(TILE_DIMENSION);
	const glm::vec2 TILE_SIZE = glm::vec2(TILE_DIMENSION_F);
	const float HEAR_RADIUS_ENEMY = 100.0f;
	const float HEAR_RADIUS_ENEMY_SQ = HEAR_RADIUS_ENEMY*HEAR_RADIUS_ENEMY;
	const float HEAR_RADIUS_PLAYER = 150.0f;
	const float HEAR_RADIUS_PLAYER_SQ = HEAR_RADIUS_PLAYER*HEAR_RADIUS_PLAYER;
	const float ENEMY_RANDOM_TIME = 2000.0f;
	const float ENEMY_CONST_TIME = 300.0f;
	const float ENEMY_SPEED = 100.0f;
	const float ENEMY_TARGET_COOLDOWN = 500.0f;
	const float ENEMY_TARGET_COOLDOWN_CONST = 500.0f;
	const float PLAYER_SPEED = 500.0f;
	const float PLAYER_FLASHLIGHT_MAX_TIME = 30000.0f;
	const float PLAYER_FLASHLIGHT_RATE = 1.0f;
	const glm::vec2 LIGHT_OFFSET = glm::vec2(0, 0);
	const float LIGHT_SPEED = 1000.0f;
	const float LIGHT_TIME = 300;
};