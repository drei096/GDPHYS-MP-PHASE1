#pragma once
#include<iostream>
#include<iomanip>
#include"P6 Components/PhysVector.h"
#include"P6 Components/PhysParticle.h"
#include <vector>
using namespace std;
class Utils
{
public:
	void displayStats(vector<PhysParticle> orderedFinish, int totalUpdateCalls);
	void displayDistanceTravelled(PhysParticle p);
};

