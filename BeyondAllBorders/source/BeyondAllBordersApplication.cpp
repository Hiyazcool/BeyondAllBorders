#pragma once 
#include "Auxilium.h"

class BeyondAllBordersApplication : public Auxilium::Application
{

public:
	BeyondAllBordersApplication() {
		LOG_DEBUG("Creating Application");
	}
	~BeyondAllBordersApplication() {
	}
	void Run() override {
		//LOG_INFO("Running");
		std::cin.get();

	}

};
Auxilium::Application* Auxilium::CreateApplication() {
	return new BeyondAllBordersApplication();
}