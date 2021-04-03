#pragma once
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include"PhysVector.h"

using namespace std;
class PhysParticle
{
public:
	string name;
	float mass;
	sf::Clock timer;
	PhysVector position = PhysVector(0, 0);
	PhysVector velocity = PhysVector(0, 0);
	PhysVector acceleration = PhysVector(0, 0);
	PhysVector totalVelocity = PhysVector(0, 0);
	PhysVector initialPos = PhysVector(0, 0);
	sf::CircleShape particleShape;

	bool isFinished = false;
	float damping = 0.8f;

public:
	void update(float time);
	float measureTime();
	bool getIsDestroyed();
	void setIsDestroyed();
	void addForce(PhysVector f);
	void resetForce();
	PhysParticle();


private:
	void updatePos(float time);
	void updateVelocity(float time);
	void updateDestroyed();

private:
	bool isDestroyed = false;
	PhysVector accumulatedForce = PhysVector(0, 0);

};

