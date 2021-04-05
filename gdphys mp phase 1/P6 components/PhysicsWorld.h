#pragma once
#include<list>
#include"PhysParticle.h"

using namespace std;

class PhysicsWorld
{
public:
	list <PhysParticle*> particles;
	//Change Gravity Value here
	PhysVector gravity = PhysVector(0, 20);  // 20m/s2 down

public:
	void addParticle(PhysParticle* particle);
	void update(float time);
private:
	void updateParticleList();
};

