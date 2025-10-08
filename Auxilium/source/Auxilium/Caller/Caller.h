
#include "axpch.h"
#pragma once
#include "Log.h"


#include "Define.h"


// Heavily Based on TheCherno's (Youtube) Game Engine "Hazel" 
// Will Redo when I understand what the heck is happening in this code

namespace Auxilium {
	enum class CallType {
		None = 0,
		WinClose,
		WinResize,
		WinFocus,
		WinLostFocus,
		WinMoved,
		AppTick,
		AppUpdate,
		AppRender,
		KeyPressed,
		KeyReleased,
		KeyTyped,
		MousePressed,
		MouseReleased,
		MouseMoved,
		MouseScrolled
	};
	enum CallCategory {
		None = 0,
		ApplicationCat = BIT(0),
		InputCat = BIT(1),
		KeyboardCat = BIT(2),
		MouseCat = BIT(3),
		MouseButtonCat = BIT(4)
	};
#define CALLER_CLASS_TYPE(type)  static CallType GetStaticType() { return CallType::##type; }\
								virtual CallType GetCallType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define CALLER_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override {return category; }

	class AXLM_API Caller {
		friend class CallDispatcher;
	public:
		virtual CallType GetCallType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsCategory(CallCategory category) {
			return GetCategoryFlags() & category;
		}
		bool IsHandled() {
			return isHandled;
		}
	protected:
		bool isHandled = false;
	};
	class CallDispatcher {
		template<typename T>
		using CallerFn = std::function<bool(T&)>;
	public:
		CallDispatcher(Caller& caller) :
			caller(caller) {

		}

		template<typename T>
		bool Dispatch(CallerFn<T> func) {
			if (caller.GetCallType() == T::GetStaticType()) {
				caller.isHandled = func(*(T*)&caller);
				return true;
			}
			return false;
		}

	private:
		Caller& caller;
	};
	inline std::ostream& operator << (std::ostream& os, const Caller& c) {
		return os << c.ToString();
	}
#define BIND_CALLER(var) std::bind(&var, this, std::placeholders::_1)
}