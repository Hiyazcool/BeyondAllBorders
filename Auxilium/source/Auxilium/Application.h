#pragma once
#include "axpch.h"
#include "Define.h"
#include "Caller/Caller.h"
#include "Caller/ApplicationCaller.h"
#include "Window.h"
namespace Auxilium {
	class AXLM_API Application
	{
	public:
		Application();
		virtual ~Application();
		virtual void Run();
		void OnCall(Caller& call);


	private:
		bool OnWindowsCloseCall(WindowCloseCaller& e);

		std::unique_ptr<Window> window;
		bool isRunning = true;
	};
	Application* CreateApplication();
}

