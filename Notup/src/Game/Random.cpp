#include <Game/GameComponents/Random.h>
#include <random>
#include <ctime>

void Random::randomize()
{
	seed(static_cast<unsigned int>(time(0)));
}

void Random::seed(unsigned int seed)
{
	srand(seed);
}

float Random::nextFloat()
{
	return static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
}