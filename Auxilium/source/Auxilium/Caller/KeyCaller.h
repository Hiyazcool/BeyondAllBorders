#pragma once
#pragma once

#include "Auxilium/Caller/Caller.h"
#include "Auxilium/Core/Keycode.h"
namespace Auxilium {

	class KeyCaller : public Caller {
	protected:
		KeyCode keyCode;
		KeyCaller(const KeyCode keycode)
			: keyCode(keycode) {}
	public:
		KeyCode GetKeyCode() const { return keyCode; }
		CALLER_CLASS_CATEGORY(KeyboardCat | InputCat)
	};

	class KeyPressedCaller : public KeyCaller {
	public:
		KeyPressedCaller(const KeyCode keycode, bool isRepeat = false)
			: KeyCaller(keycode), isRepeat(isRepeat) {}

		bool IsRepeat() const { return isRepeat; }

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyPressedCaller: " << keyCode << " (repeat = " << isRepeat << ")";
			return ss.str();
		}
		CALLER_CLASS_TYPE(KeyPressed)
	private:
		bool isRepeat;
	};

	class KeyReleasedCaller : public KeyCaller {
	public:
		KeyReleasedCaller(const KeyCode keycode)
			: KeyCaller(keycode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyReleasedCaller: " << keyCode;
			return ss.str();
		}

		CALLER_CLASS_TYPE(KeyReleased)
	};

	class KeyTypedCaller : public KeyCaller {
	public:
		KeyTypedCaller(const KeyCode keycode)
			: KeyCaller(keycode) {}

		std::string ToString() const override {
			std::stringstream ss;
			ss << "KeyTypedCaller: " << keyCode;
			return ss.str();
		}

		CALLER_CLASS_TYPE(KeyTyped)
	};
}