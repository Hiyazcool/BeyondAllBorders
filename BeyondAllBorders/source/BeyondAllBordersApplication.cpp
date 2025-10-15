#include <Auxilium.h>
#include <iostream>
#include <thread>
#include <chrono>
#include "Auxilium/Entry.h"

namespace BeyondAllBorders {
	
	class BeyondAllBordersApplication : public Auxilium::Application
	{

	public:
		BeyondAllBordersApplication() {
			LOG_DEBUG("Creating Application");
		}
		~BeyondAllBordersApplication() {
		}
		void Run() override {
			LOG_INFO("Running");
			std::cin.get();

		}

		Auxilium::Application* Auxilium::CreateApplication() {
			return new BeyondAllBorders::BeyondAllBordersApplication();
		}
	};
}