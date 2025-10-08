#pragma once

#include "Auxilium/Caller/Caller.h"
#include "Auxilium/Core/MouseCode.h"

namespace Auxilium {

	class MouseMovedCaller : public Caller
	{
		float mouseX, mouseY;
	public:
		MouseMovedCaller(const float x, const float y)
			: mouseX(x), mouseY(y) {}

		float GetX() const { return mouseX; }
		float GetY() const { return mouseY; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseMovedCaller: " << mouseX << ", " << mouseY;
			return ss.str();
		}

		CALLER_CLASS_TYPE(MouseMoved)
		CALLER_CLASS_CATEGORY(MouseCat | InputCat)
	};

	class MouseScrolledCaller : public Caller
	{
	public:
		MouseScrolledCaller(const float xOffset, const float yOffset)
			: xOffset(xOffset), yOffset(yOffset) {}

		float GetXOffset() const { return xOffset; }
		float GetYOffset() const { return yOffset; }

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseScrolledCaller: " << GetXOffset() << ", " << GetYOffset();
			return ss.str();
		}

		CALLER_CLASS_TYPE(MouseScrolled)
		CALLER_CLASS_CATEGORY(MouseCat | InputCat)
	private:
		float xOffset, yOffset;
	};

	class MouseButtonCaller : public Caller
	{
	public:
		MouseCode GetMouseButton() const { return button; }

		CALLER_CLASS_CATEGORY(MouseCat | InputCat | MouseButtonCat)
	protected:
		MouseButtonCaller(const MouseCode button)
			: button(button) {}

		MouseCode button;
	};

	class MouseButtonPressedCaller : public MouseButtonCaller
	{
	public:
		MouseButtonPressedCaller(const MouseCode button)
			: MouseButtonCaller(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonPressedCaller: " << button;
			return ss.str();
		}

		CALLER_CLASS_TYPE(MousePressed)
	};

	class MouseButtonReleasedCaller : public MouseButtonCaller
	{
	public:
		MouseButtonReleasedCaller(const MouseCode button)
			: MouseButtonCaller(button) {}

		std::string ToString() const override
		{
			std::stringstream ss;
			ss << "MouseButtonReleasedCaller: " << button;
			return ss.str();
		}

		CALLER_CLASS_TYPE(MouseReleased)
	};

}