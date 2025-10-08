#pragma once

#include "Caller.h"

namespace Auxilium {
	class WindowResizeCaller : public Caller
	{
	public:
		WindowResizeCaller(unsigned int width, unsigned int height)
			: width(width), height(height) {}

		unsigned int GetWidth() const { return width; }
		unsigned int GetHeight() const { return height; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "WindowResizeCaller: " << width << ", " << height;
			return ss.str();
		}

		CALLER_CLASS_TYPE(WinResize)
		CALLER_CLASS_CATEGORY(ApplicationCat)
	private:
		unsigned int width, height;
	};

	class WindowCloseCaller : public Caller
	{
	public:
		WindowCloseCaller() = default;

		CALLER_CLASS_TYPE(WinClose)
		CALLER_CLASS_CATEGORY(ApplicationCat)
	};

	class AppTickCaller : public Caller
	{
	public:
		AppTickCaller() = default;

		CALLER_CLASS_TYPE(AppTick)
		CALLER_CLASS_CATEGORY(ApplicationCat)
	};

	class AppUpdateCaller : public Caller
	{
	public:
		AppUpdateCaller() = default;

		CALLER_CLASS_TYPE(AppUpdate)
		CALLER_CLASS_CATEGORY(ApplicationCat)
	};

	class AppRenderCaller : public Caller
	{
	public:
		AppRenderCaller() = default;

		CALLER_CLASS_TYPE(AppRender)
		CALLER_CLASS_CATEGORY(ApplicationCat)
	};
}