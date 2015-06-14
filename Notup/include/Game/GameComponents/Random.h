#pragma once

class Random
{
public:
	static void randomize();

	static void seed(unsigned int seed);

	static float nextFloat();
};