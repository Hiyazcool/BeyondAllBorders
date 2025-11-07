#pragma once
#ifdef AXLM_WINDOWS_PLATFORM

	extern Auxilium::Application* Auxilium::CreateApplication();

	int main(int argc, char** argv) {
		Auxilium::Logger::Initialize();
		LOG_INFO("Creating Application");
		auto application = Auxilium::CreateApplication();
		LOG_INFO("Running Application");		
		application->Run();
		delete application;
	}

#endif 
