#include "PhysicsWorld.h"

void PhysicsWorld::addParticle(PhysParticle* particle)
{
	particles.push_back(particle);
}

void PhysicsWorld::update(float time)
{
	updateParticleList();


	for (list<PhysParticle*>::iterator i = particles.begin(); i != particles.end(); i++)
	{
		(*i)->acceleration = gravity;
		(*i)->update(time);
	}
}

void PhysicsWorld::updateParticleList()
{
	particles.remove_if(
		[](PhysParticle* p)
		{
			return p->getIsDestroyed();
		}
	);
}

