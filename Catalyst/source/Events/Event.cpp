#include "Event.h"
using namespace Auxilium;
void  Event::Invoke(EventParams& params) {
	for (int i = 0; i < listeners->GetSize(); i++) {
		listeners->Get(i)(params);
	}
}
void Event::Subscribe(void(*listener)(const EventParams&)) {
	listeners->AddToList(listener);
}void Event::Unsubscribe(void(*listener)(const EventParams&)) {
	listeners->RemoveSearch(listener);
}
Event::Event() {
	Event::listeners = new Catalyst::List<void(*)(const EventParams&)>();
}
Event::~Event() {
	delete listeners;
}