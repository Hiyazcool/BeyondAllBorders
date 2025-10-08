#include "Events.h"
namespace HiyazUtils
{
	namespace Event {
		FuncWrapper::FuncWrapper(std::function<void(const EventArgs&)>& _callback) :
			Index(-1),
			Callback(_callback) {

		}
		std::function<void(const EventArgs&)>& FuncWrapper::SetCallback() {
			try {
				if (Index != -1)
					throw std::invalid_argument("This Wrapper is Currently Listening!");
				else
					return Callback;
			}
			catch (std::invalid_argument e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		Event::Event() {
		}
		Event::~Event() {
			Subscribers.Clear();
		}
		void Event::Subscribe(FuncWrapper* _other) {
			try {
				if (Subscribers == nullptr)
					throw std::invalid_argument("Event not Intialized!");
				if (Subscribers != _other)
					throw std::invalid_argument("Function Pointers Do Not Match!");
				else
					if (_other->Index <= -1)
						_other->Index = Subscribers.AddWithIndex(_other);
					else
						if (Subscribers[_other->Index] == _other)
							throw std::invalid_argument("Repeat Function Listener!");
						else
							_other->Index = Subscribers.AddWithIndex(_other);
			}
			catch (std::invalid_argument e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		void Event::UnSubscribe(FuncWrapper* _other) {
			try {
				if (Subscribers == nullptr)
					throw std::invalid_argument("Event not Intialized!");
				if (Subscribers != _other)
					throw std::invalid_argument("Function Pointers Do Not Match!");
				else
					if (_other->Index <= -1)
						throw std::invalid_argument("Out of Bounds Index!");
					else
						if (Subscribers[_other->Index] == _other) {
							Subscribers -= _other->Index;
							_other->Index = -1;
						}
						else
							if (Subscribers[_other->Index] != _other)
							throw std::invalid_argument("Function Listner Does Not Match!");
				else
					throw std::invalid_argument("Out of Bounds Index!");
			}
			catch (std::invalid_argument e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		void Event::operator+=(FuncWrapper* _other) {
			try {
				if (Subscribers == nullptr)
					throw std::invalid_argument("Event not Intialized!");
				if (Subscribers != _other)
					throw std::invalid_argument("Function Pointers Do Not Match!");
				else
					if (_other->Index < Subscribers.GetSize())
						if (_other->Index <= -1)
							_other->Index = Subscribers.AddWithIndex(_other);
						else
							if (Subscribers[_other->Index] == _other)
								throw std::invalid_argument("Repeat Function Listener!");
							else
								_other->Index = Subscribers.AddWithIndex(_other);
			}
			catch (std::invalid_argument e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		void Event::operator-=(FuncWrapper* _other) {
			try {
				if (Subscribers == nullptr)
					throw std::invalid_argument("Event not Intialized!");
				if (Subscribers != _other)
					throw std::invalid_argument("Function Pointers Do Not Match!");
				else
					if (_other->Index <= -1)
						throw std::invalid_argument("Out of Bounds Index!");
					else
						if (_other->Index < Subscribers.GetSize())
							if (Subscribers[_other->Index] == _other) {
								Subscribers -= _other->Index;
								_other->Index = -1;
							}
							else
								throw std::invalid_argument("Function Listner Does Not Match!");
						else
							throw std::invalid_argument("Out of Bounds Index!");
			}
			catch (std::invalid_argument e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		void Event::operator=(void(*_other)(const EventArgs _args)) {
			try {
			}
			catch (std::invalid_argument e)
			{
				std::cout << e.what() << std::endl;
			}
		}
		void Event::Invoke(const EventArgs& _args) {
			for (int i = 0; i < Subscribers.GetSize();i++)
			{
				Subscribers[i]->Callback(_args);
			}
		}
		void Event::InvokeThreaded(const EventArgs& _args) {

		}
	}
}
