#include <Game/GameComponents/Entities/Entity.h>

class LightParticle : public Entity
{
public:
	LightParticle(World &world, glm::vec2 position, glm::vec2 size, std::shared_ptr<Texture> texture, unsigned int lifetime, glm::vec2 direction, float speed);

	virtual ~LightParticle();

	virtual void update(const GameTime& gameTime);

	virtual void collision(std::shared_ptr<Entity> e);

	virtual bool drawNormal();
private:

	float m_time;
	glm::vec2 m_direction;
	float m_speed;
	bool m_hadCollision;
};