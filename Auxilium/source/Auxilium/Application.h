#include "axpch.h"
#pragma once
#include "Define.h"
#include "Caller/Caller.h"
#include "Window.h"
namespace Auxilium {
	class Application
	{
	public:
		Application();
		virtual ~Application();
		virtual void Run();
		void OnCall(Caller& call);

		Application* CreateApplication();
	private:
		std::unique_ptr<Window> window;
		bool isRunning = true;
	};
}

