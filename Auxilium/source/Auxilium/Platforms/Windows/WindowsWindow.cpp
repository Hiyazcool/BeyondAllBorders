#include "axpch.h"
#include "Define.h"
#include "WindowsWindow.h"


#include "Caller/ApplicationCaller.h"
#include "Caller/MouseCaller.h"
#include "Caller/KeyCaller.h"


namespace Auxilium {

	static uint8_t GLFWWindowCount = 0;

	Window* Window::Create(const WindowProps& props) {
		return new WindowsWindow(props);
	}

	static void GLFWErrorCallback(int error, const char* description) {
		LOG_ERROR("GLFW Error ({0}): {1}", error, description);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props) {

		Init(props);
	}

	WindowsWindow::~WindowsWindow() {
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props) {
		data.Title = props.Title;
		data.Width = props.Width;
		data.Height = props.Height;
		LOG_CRIT("Creating window {0} ({1}, {2})", data.Title, data.Width, data.Height);

		if (GLFWWindowCount == 0) {
			int success = glfwInit();
			
			glfwSetErrorCallback(GLFWErrorCallback);
			GLFWWindowCount++;
		}
		window = glfwCreateWindow((int)props.Width, (int)props.Height, data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
		SetVSync(true);
	}
	void WindowsWindow::Shutdown() {
		

		glfwDestroyWindow(window);
		--GLFWWindowCount;

		if (GLFWWindowCount == 0) {
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate() {

	}

	void WindowsWindow::SetVSync(bool enabled) {

		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const {
		return data.VSync;
	}

}