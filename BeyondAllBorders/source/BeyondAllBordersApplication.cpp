#pragma once 
#include "Auxilium.h"
#include "EntityComponentSystem.h"
using namespace ecs;
class BeyondAllBordersApplication : public Auxilium::Application
{

	// Example components
	struct Position { float x, y, z; };
	struct Velocity { float vx, vy, vz; };
	struct Mesh { int meshId; };

public:
	BeyondAllBordersApplication() {
	}
	~BeyondAllBordersApplication() {
	}
	void Run() override {
		std::cin.get();
	}

};
Auxilium::Application* Auxilium::CreateApplication() {
	return new BeyondAllBordersApplication();
}