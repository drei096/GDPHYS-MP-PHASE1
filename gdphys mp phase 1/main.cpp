#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <cstdlib>
#include <vector>
#include <ctime>
#include <Windows.h>
#include "P6 components/PhysVector.h"
#include "P6 components/PhysParticle.h"
#include "Utils.h"
#include "P6 components/PhysicsWorld.h"

#define PI 3.14159

using namespace std;

/*
* CHANGES SINCE 4/3/2021 8:41 PM:
* Particle Destroyer added inside PhysParticle (updater)
* Particle Creation inside while loop
* Changed Force Values Randomizer
* Changed X Direction added value
* Particle Destroyer Updated to destroy in a range in if statement
* Added an additional if inside timeSinceLast if statement
* Added a particleCounter at the end of the while loop
* Increased forceVal range (16k-20k)
* Pakicheck nalang if may simultaneous fire sa simulang simula ng simu
*/



int main() 
{
    srand(time(0));

    const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);
    Utils utils;
    PhysicsWorld pWorld = PhysicsWorld();
    vector<PhysParticle*> particleList;
    int particleCount = 0;

    sf::RenderWindow window(sf::VideoMode(720, 500), "P6 Test");

    sf::Event event;

    //ground marker
    sf::RectangleShape groundLine;
    groundLine.setFillColor(sf::Color::White);
    groundLine.setSize(sf::Vector2f(720.0f, 10.0f));
    groundLine.setPosition(0, 400);

    /*
    //Bullet 1 particle
    PhysParticle bullet;
    bullet.name = "Bullet 1";
    bullet.mass = 20;
    bullet.addForce(PhysVector(cos(atan2(0.6, 0.3)) * 16000, -1 * sin(atan2(0.6, 0.3)) * 16000));
    bullet.particleShape.setRadius(10.0f);
    bullet.particleShape.setFillColor(sf::Color::White);
    bullet.particleShape.setOrigin(bullet.particleShape.getRadius(), bullet.particleShape.getRadius());
    bullet.position = PhysVector(0, window.getSize().y - bullet.particleShape.getRadius());
    bullet.initialPos = bullet.position;
    bullet.particleShape.setPosition(bullet.position.x, bullet.position.y);

    pWorld.addParticle(&bullet);
    */

    /*
    //Bullet 1 shape
    sf::CircleShape bullet1(10.0f);
    bullet1.setFillColor(sf::Color::White);
    bullet1.setOrigin(bullet1.getRadius(), bullet1.getRadius());

    //Bullet 1 setPos
    bullet.position = PhysVector(0, window.getSize().y - bullet1.getRadius());
    bullet.initialPos = bullet.position;
    bullet1.setPosition(bullet.position.x, bullet.position.y);
    */

    sf::Clock clock;
    sf::Time timeSinceLast = sf::Time::Zero;

    while (1) {

        timeSinceLast += clock.restart();

        if (timeSinceLast > TimePerFrame) 
        {
            if (pWorld.particles.size() < 25)
            {
                for (int i = 0; i < 1; i++)
                {
                    float forceVal = rand() % 20000 + 16000;
                    PhysVector direction(rand() % 30 + 2.5, rand() % 30 + 10);
                    float magnitude = direction.magnitude();

                    direction.x = direction.x / magnitude;
                    direction.x = direction.x * (PI / 180);

                    direction.y = 1 / magnitude;
                    direction.y = direction.y * (PI / 180);
                    //direction.y = direction.y / magnitude;

                    PhysParticle* particle = new PhysParticle();

                    particle->name = "firework " + i;
                    particle->mass = 1;

                    particle->addForce(PhysVector(cos(atan2(direction.x, direction.y)) * forceVal * (rand() % 2 == 1 ? 1 : -1), -1 * sin(atan2(direction.x, direction.y)) * forceVal));

                    particle->particleShape.setRadius(5.0f);
                    particle->particleShape.setFillColor(sf::Color(rand() % 256 + 20, rand() % 256 + 20, rand() % 256 + 20));
                    particle->particleShape.setOrigin(particle->particleShape.getRadius(), particle->particleShape.getRadius());
                    particle->position = PhysVector(360, 400);
                    particle->initialPos = particle->position;
                    particle->particleShape.setPosition(particle->position.x, particle->position.y);

                    pWorld.addParticle(particle);
                    particleList.push_back(particle);
                    particleCount++;

                    //delay(1);
                }
            }
            

            timeSinceLast -= TimePerFrame;

            pWorld.update(TimePerFrame.asMilliseconds() / 1000.0f);

            for (int i = 0; i < particleList.size(); i++)
            {
                particleList[i]->particleShape.setPosition(particleList[i]->position.x, particleList[i]->position.y);
            }


            //bullet.particleShape.setPosition(bullet.position.x, bullet.position.y);


            window.pollEvent(event);
            if (event.type == sf::Event::Closed)
                window.close();

            window.clear();

            for (list<PhysParticle*>::iterator i = pWorld.particles.begin(); i != pWorld.particles.end(); i++)
            {
                if ((*i)->getIsDestroyed() != true) {
                    window.draw((*i)->particleShape);
                }
            }


            //if (pWorld.particles.begin.getIsDestroyed() != true)
                //window.draw(bullet.particleShape);

            window.draw(groundLine);
            window.display();

            //cout << particleCount << endl;
     
                
            
        }
    }

    //utils.displayDistanceTravelled(bullet);


    return 0;
}