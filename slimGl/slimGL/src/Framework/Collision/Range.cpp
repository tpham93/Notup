#include <Framework/Collision/Range.h>

#include <algorithm>

Range::Range(float min, float max)
	:m_min(min),
	m_max(max)
{

}

void Range::add(float num)
{
	m_min = std::min(m_min, num);
	m_max = std::max(m_max, num);
}

float Range::intersection(Range &range)
{

	if (m_min < range.m_min)
	{
		return m_max - range.m_min;
	}
	else
	{
		return range.m_max - m_min;
	}


	//return std::max(range.m_max - m_min, m_max - range.m_min);
	//return m_min <= range.m_max && m_max > range.m_min || range.m_min <= m_max && range.m_max > m_min;
}