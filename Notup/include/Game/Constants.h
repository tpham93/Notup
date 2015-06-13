#pragma once

#include <glm/glm.hpp>

namespace Constants
{
	const unsigned int TILE_DIMENSION = 32;
	const float TILE_DIMENSION_F = static_cast<float>(TILE_DIMENSION);
	const glm::ivec2 TILE_SIZE_I = glm::ivec2(TILE_DIMENSION);
	const glm::vec2 TILE_SIZE = glm::vec2(TILE_DIMENSION_F);
};