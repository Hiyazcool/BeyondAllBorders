#include "axpch.h"
#include "Define.h"
#include "Caller/Caller.h"
#pragma once
namespace Auxilium {
	struct WindowProps {
		std::string Title;
		uint Width;
		uint Height;
		WindowProps(const std::string& title = "Auxilium Engine", uint width = 1920, uint height = 720) :
			Title(title),
			Width(width),
			Height(height) {

		}
	};
	class AXLM_API Window {
	public:
		using CallbackFn = std::function<void(Caller&)>;
		virtual ~Window() {}

		virtual void OnUpdate() = 0;
		virtual uint GetWidth() const = 0;
		virtual uint GetHeight() const = 0;

		virtual void SetCallback(const CallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool IsVSync() const = 0;

		static Window* Create(const WindowProps& props = WindowProps());
	};
}