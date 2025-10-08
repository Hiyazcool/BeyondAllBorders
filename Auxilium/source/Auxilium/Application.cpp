#include "axpch.h"
#include "Application.h"
namespace Auxilium {

	Application::Application() {
		window = std::unique_ptr<Window>(Window::Create());
		window->SetCallback(BIND_CALLER(Application::OnCall));
	}
	Application::~Application() {

	}
	void Application::Run() {
		while (true);
	}
	void Application::OnCall(Caller& call) {
		LOG_INFO("{0}", call.GetName());
	}
}
int main() {
	return 0;
}