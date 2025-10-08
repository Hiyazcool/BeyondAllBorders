#pragma once
#include "Auxilium.h"
#include "axpch.h"
#ifdef AXLM_WINDOWS_PLATFORM

extern "C++" Auxilium::Application* Auxilium::CreateApplication();

int main(int argc, char** argv) {
	Auxilium::Logger::Initialize();
	std::cout << "\033[31mThis text is red.\033[0m" << std::endl;
	
	auto application = Auxilium::CreateApplication();
	application->Run();
	delete application;
}
#endif // AXLM_WINDOWS_PLATFORM
