#pragma once
#include <string>
#include "EventParams.h"
#include "List.h"
//#define EVENT_DEBUG
namespace Auxilium {
	class CATALYST_API Event {
	private:
		Catalyst::List<void(*)(const EventParams&)>* listeners;
	public:
		virtual void Invoke(EventParams& params);
		virtual void Subscribe(void(*listener)(const EventParams&));
		virtual void Unsubscribe(void(*listener)(const EventParams&));
		Event();
		Event(std::string);
		~Event();
#ifdef EVENT_DEBUG || Devolpment
		virtual const char* GetName() const = 0;
		virtual std::string ToString() const { return GetName(); };
#endif

	};

}