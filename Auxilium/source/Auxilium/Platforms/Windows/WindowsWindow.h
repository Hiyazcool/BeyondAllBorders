#pragma once
#include "axpch.h"
#include "Define.h"
#include "Window.h"
#include <GLFW/glfw3.h>
namespace Auxilium {
	class WindowsWindow : Window {
	public:
		WindowsWindow(const WindowProps& props);
		virtual ~WindowsWindow();

		void OnUpdate() override;

		unsigned int GetWidth() const override { return data.Width; }
		unsigned int GetHeight() const override { return data.Height; }

		// Window attributes
		void SetCallback(const CallbackFn& callback) override { data.EventCallback = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		virtual void* GetNativeWindow() const { return window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void Shutdown();
	private:
		GLFWwindow* window;
		//Scope<GraphicsContext> context;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			CallbackFn EventCallback;
		};

		WindowData data;
	};
};
