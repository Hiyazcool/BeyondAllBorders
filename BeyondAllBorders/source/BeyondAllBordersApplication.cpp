#pragma once 
#include "Auxilium.h"
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

};
Auxilium::Application* Auxilium::CreateApplication() {
	return new BeyondAllBordersApplication();
}