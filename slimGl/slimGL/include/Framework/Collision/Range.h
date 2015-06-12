#pragma once

/**********************************************************************************************
* 											include
**********************************************************************************************/
#include <limits>
/**********************************************************************************************
* 										class declaration
**********************************************************************************************/
class Range
{
public:

	/*
	*	\brief		constructor
	*	\param min	the starting min value
	*	\param max	the starting max value
	*/
	Range(float min = std::numeric_limits<float>::infinity(), float max = -std::numeric_limits<float>::infinity());

	/*
	*	\brief		including a number to the range, if the num is not inside of th range, it will be extnded
	*	\param num	the number which should be included
	*/
	void add(float num);

	/*
	*	\brief	check if this range intersects with another range
	*/
	float intersection(Range &range);
private:
	//! the minimum of the range
	float m_min;
	//! the maximum of the range
	float m_max;
};