//======================================================================
//File: ContactResolver.cpp
//Author: Matt Struble
//======================================================================
#include "ContactResolver.h"
//======================================================================
ContactResolver::ContactResolver(unsigned int iterations)
	:m_Iterations(iterations)
{

}

//--------------------------------------------------------------------------------
void ContactResolver::ResolveContacts(Contact *contactArray, unsigned int numContacts, float dt)
{
	unsigned int i;

	m_IterationsUsed = 0;

	while (m_IterationsUsed < m_Iterations)
	{
		float max = std::numeric_limits<float>::max();

		unsigned int maxIndex = numContacts;

		for (i = 0; i < numContacts; i++)
		{
			float sepVel = contactArray[i].CalculateSeparatingVelocity();

			if (sepVel < max && (sepVel < 0 || contactArray[i].Penetration > 0))
			{
				max = sepVel;
				maxIndex = i;
			}
		}

		if (maxIndex == numContacts) break;

		contactArray[maxIndex].Resolve(dt);

		m_IterationsUsed++;
	}
}