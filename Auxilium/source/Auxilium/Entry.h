#pragma once
#include "Auxilium.h"
#include "axpch.h"
#include "Application.h"
#ifdef AXLM_WINDOWS_PLATFORM
namespace Auxilium {

	extern Auxilium::Application* Auxilium::CreateApplication();

	int main(int argc, char** argv) {
		Auxilium::Logger::Initialize();

		auto application = Auxilium::CreateApplication();
		application->Run();
		delete application;
	}
}

#endif 
