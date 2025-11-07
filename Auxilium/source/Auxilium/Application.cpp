#include "axpch.h"
#include "Application.h"
#include <GLFW/glfw3.h>
namespace Auxilium {

	Application::Application() {
		window = std::unique_ptr<Window>(Window::Create());
		window->SetCallback(BIND_CALLER(Application::OnCall));
	}
	Application::~Application() {

	}
	void Application::Run() {
		while (isRunning) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			window->OnUpdate();
		}
	}
	bool Application::OnWindowsCloseCall(WindowCloseCaller& e) {
		isRunning = false;
		return true;
	}
	void Application::OnCall(Caller& call) {
		CallDispatcher dispatcher(call);
		dispatcher.Dispatch<WindowCloseCaller>(BIND_CALLER(Application::OnWindowsCloseCall));

		LOG_INFO("{0}", call.ToString());
	}
}
int main() {
	return 0;
}