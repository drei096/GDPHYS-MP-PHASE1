/*
* GDPHYS MP PHASE 1 - PARTICLE SYSTEM
* DEVELOPED BY:
* GAURANA, ALDREY
* TALLADOR, ERYN
*/

#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <vector>
#include <ctime>
#include "P6 components/PhysVector.h"
#include "P6 components/PhysParticle.h"
#include "Utils.h"
#include "P6 components/PhysicsWorld.h"

#define PI 3.14159

using namespace std;

/*
* DEFAULT VALUES:
* Max Particle Size is set to 25
* Force Value is between 16000 to 36000
* Direction Value is between 2.5 to 32.5
* Particle Position is set to (360, 400)
* Gravity is -20m/s2 (could be accessed in PhysicsWorld.h)
* Particle Destructor is set to either 0.5 second or 1 second 
    (could be accessed in PhysParticle.cpp under UpdateDestroyed() function)
* Damping Value is set to 0.8. (could be edited in PhysParticle.h) 
*/


int main() 
{
    srand(time(0));

    //Variable Initialization
    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
    Utils utils;
    PhysicsWorld pWorld = PhysicsWorld();
    vector<PhysParticle*> particleList;
    int particleCount = 0;

    //Window
    sf::RenderWindow window(sf::VideoMode(720, 500), "GDPHYS MP Phase 1");

    sf::Event event;

    //Ground Marker
    sf::RectangleShape groundLine;
    groundLine.setFillColor(sf::Color::White);
    groundLine.setSize(sf::Vector2f(720.0f, 10.0f));
    groundLine.setPosition(0, 400);

    //Clock
    sf::Clock clock;
    sf::Time timeSinceLast = sf::Time::Zero;

    while (1) {

        timeSinceLast += clock.restart();

        if (timeSinceLast > TimePerFrame) 
        {
            //Particle Size clamped to 25
            //For a larger particle size cap, simple modify the "25"
            if (pWorld.particles.size() < 25)
            {
                //Creates one particle
                for (int i = 0; i < 1; i++)
                {
                    //VALUE INITIALIZATION
                    //Change Force Value here
                    float forceVal = rand() % 20000 + 16000;

                    //Change Direction here
                    //NOTE: Only modify the added value as modifying the "30" would make it spread in a much larger cone
                    PhysVector direction(rand() % 30 + 2.5, rand() % 30 + 10);
                    float magnitude = direction.magnitude();
                    
                    direction.x = direction.x / magnitude;
                    direction.x = direction.x * (PI / 180);

                    direction.y = 1 / magnitude;
                    direction.y = direction.y * (PI / 180);

                    //PARTICLE CREATION
                    PhysParticle* particle = new PhysParticle();

                    //Value Assigning
                    particle->name = "firework " + i;
                    //EDIT MASS HERE
                    particle->mass = 1;

                    //addForce (direction and forceVal will reflect on this assignation)         
                    //rand inside is for a positive or negative x value
                    particle->addForce(PhysVector(cos(atan2(direction.x, direction.y)) * forceVal * (rand() % 2 == 1 ? 1 : -1), -1 * sin(atan2(direction.x, direction.y)) * forceVal));

                    //Particle Shape Creation
                    particle->particleShape.setRadius(5.0f);
                    particle->particleShape.setFillColor(sf::Color(rand() % 256 + 20, rand() % 256 + 20, rand() % 256 + 20));
                    particle->particleShape.setOrigin(particle->particleShape.getRadius(), particle->particleShape.getRadius());

                    //Position at Middle of the Window
                    particle->position = PhysVector(360, 400);
                    particle->initialPos = particle->position;
                    particle->particleShape.setPosition(particle->position.x, particle->position.y);

                    pWorld.addParticle(particle);
                    particleList.push_back(particle);
                    particleCount++;

                }
            }
            

            timeSinceLast -= TimePerFrame;

            pWorld.update(TimePerFrame.asMilliseconds() / 1000.0f);

            for (int i = 0; i < particleList.size(); i++)
            {
                particleList[i]->particleShape.setPosition(particleList[i]->position.x, particleList[i]->position.y);
            }


            window.pollEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();

            //DRAWING THE PARTICLES
            window.clear();

            for (list<PhysParticle*>::iterator i = pWorld.particles.begin(); i != pWorld.particles.end(); i++)
            {
                if ((*i)->getIsDestroyed() != true) {
                    window.draw((*i)->particleShape);
                }
            }

            window.draw(groundLine);
            window.display();
            //END OF PARTICLE DRAWING
                
            //Uncomment this if you want to see the particle count during simulation
            //cout << pWorld.particles.size() << endl;
        }
    }


    return 0;
}