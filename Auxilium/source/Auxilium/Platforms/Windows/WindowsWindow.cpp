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

		Logger::Initialize();
		LOG_INFO("Creating window {0} ({1}, {2})", data.Title, data.Width, data.Height);

		if (GLFWWindowCount == 0) {
			int success = glfwInit();

			glfwSetErrorCallback(GLFWErrorCallback);
			GLFWWindowCount++;
		}
		window = glfwCreateWindow((int)props.Width, (int)props.Height, data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(window);
		glfwSetWindowUserPointer(window, &data);
		SetVSync(true);

		// Set GLFW Callbacks
		glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			data.Width = width;
			data.Height = height;

			WindowResizeCaller call(width, height);
			data.Callback(call);
			});
		glfwSetWindowCloseCallback(window, [](GLFWwindow* window) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			WindowCloseCaller call;
			data.Callback(call);
			});
		glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
			WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
			switch (action) {
			case GLFW_PRESS:
			{
				KeyPressedCaller call(key, 0);
				data.Callback(call);
				break;
			}
			case GLFW_RELEASE:
			{
				KeyReleasedCaller call(key);
				data.Callback(call);
				break;
			}
			case GLFW_REPEAT:
			{
				KeyPressedCaller call(key, 1);
				data.Callback(call);
				break;
			}
			}});
			glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action) {
				case GLFW_PRESS:
				{
					MouseButtonPressedCaller call(button);
					data.Callback(call);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedCaller call(button);
					data.Callback(call);
					break;
				}
				}});
				glfwSetScrollCallback(window, [](GLFWwindow* window, double xOffset, double yOffset) {
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
					MouseScrolledCaller call((float)(xOffset), (float)yOffset);
					data.Callback(call);
					});
				glfwSetCursorPosCallback(window, [](GLFWwindow* window, double xPos, double yPos) {
					WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
					MouseMovedCaller call((float)xPos, (float)yPos);
					data.Callback(call);
					});
	}
	void WindowsWindow::Shutdown() {


		glfwDestroyWindow(window);
		--GLFWWindowCount;

		if (GLFWWindowCount == 0) {
			glfwTerminate();
		}
	}

	void WindowsWindow::OnUpdate() {
		glfwPollEvents();
		glfwSwapBuffers(window);
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