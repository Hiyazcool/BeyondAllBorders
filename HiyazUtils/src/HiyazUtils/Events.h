#pragma once
#include <stdexcept>
#include "List.h"
#include <functional>
#include "Print.h"
using namespace List;
/*
Static List of all events to be fired off to threads
	To be Implemented Later, Focusing on Single Thread ATM

Calling all Function Pointers through Invoke

Need to make Wrapper that holds the Objects Reference and the Member Function, using templates hooray!!!!! fml
Maybe use lambdas??????

	Todo:
		Validity Checks to Make sure Listner still exist!!!!!!!!!!!!!!!!
		Make it Easier to Add Listners ie Not 3-4 lines of code, Automate thru defines etc
   		
     		Base Event With Abstract Functions
			Allows Me to make a Generic Event with No Args As Well As Template Versions

		Look to make the Event Class Automatically Gather and Create the Wrapper Makeing it look like it doesnt need one

		https://www.ibm.com/docs/en/i/7.5?topic=only-pointers-members-c	
		https://isocpp.org/wiki/faq/pointers-to-members

		Look at Hashs instead of Wrappers to track Functions
		Seperate Implementation
		Look at Specializing EventArgs
		Add Quality of Life Things
			Resize that Reindexs everything
		Make Queue Class To use Threads
		Look at the Iterations to fix
		Organize/Rename/Comment

		Spicey Idea's 
			Integrate Timer/Ticks

https://en.wikipedia.org/wiki/Observer_pattern
*/	
#define List OldList
namespace HiyazUtils {
	namespace Event {
		class EventArgs {
			class Source;
		};
		struct FuncWrapper final {
		private:
			uint Index = -1; // Make Event Friend of this so it can be const and still be editable by Events
			friend class Event;
		public:
			FuncWrapper(std::function<void(const EventArgs&)>& _callback);
			std::function<void(const EventArgs&)>& Callback;
			std::function<void(const EventArgs&)>& SetCallback();
		};
		class Event final
		{
			struct EventThreadQueueObject {
				List<void(*)(const EventArgs _args)>& QueueList;
				EventArgs eventArgs;
			};
			static List<EventThreadQueueObject> ThreadQueue;
			List<FuncWrapper*> Subscribers;
		public:
			Event();
			~Event();
			void Subscribe(FuncWrapper*);
			void UnSubscribe(FuncWrapper*);
			void operator+=(FuncWrapper*);
			void operator-=(FuncWrapper*);
			void operator=(void(*_other)(const EventArgs _args));
			void Invoke(const EventArgs&);
			void InvokeThreaded(const EventArgs&);
		};

		template<typename CallbackParameters = EventArgs, typename ReturnType = void>
		class WrapperEvent {
		public:
			struct FunctionWrapper final {
			private:
				uint Index = -1;
				friend class WrapperEvent;
			public:
				uint GetIndex();
				FunctionWrapper(std::function<ReturnType(const CallbackParameters&)>&);
				~FunctionWrapper();
				std::function<ReturnType(const CallbackParameters&)>& Callback;
				std::function<ReturnType(const CallbackParameters&)>& SetCallback();
			};
		private:
			struct EventThreadQueueObject {
				List<ReturnType(*)(const CallbackParameters& _args)>& QueueList;
				EventArgs eventArgs;
			};
			static List<EventThreadQueueObject> ThreadQueue;
			List<FunctionWrapper*> Subscribers;
		public:
			WrapperEvent();
			~WrapperEvent();
			void Subscribe(FunctionWrapper*);
			void UnSubscribe(FunctionWrapper*);
			void operator+=(FunctionWrapper*);
			void operator-=(FunctionWrapper*);
			void Invoke(const CallbackParameters&);
			void InvokeThreaded(const CallbackParameters&);
		};
#pragma region Template Implementation
		template<typename CallbackParameters, typename ReturnType>
		WrapperEvent<CallbackParameters,ReturnType>::FunctionWrapper::FunctionWrapper(std::function<ReturnType(const CallbackParameters&)>& _callback) :
			Index(-1),
			Callback(_callback) {
#ifdef DEBUG
			DebugLog("Created Function Wrapper");
#endif // DEBUG
		}
		template<typename CallbackParameters, typename ReturnType>
		WrapperEvent<CallbackParameters, ReturnType>::FunctionWrapper::~FunctionWrapper() {
#ifdef DEBUG
			DebugLog("Deleted Function Wrapper");
#endif // DEBUG
		}
		template<typename CallbackParameters, typename ReturnType>
		uint WrapperEvent<CallbackParameters, ReturnType>::FunctionWrapper::GetIndex() {
			return Index;
		}
		template<typename CallbackParameters, typename ReturnType>
		std::function<ReturnType(const CallbackParameters&)>& WrapperEvent<CallbackParameters, ReturnType>::FunctionWrapper::SetCallback() {
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
		template<typename CallbackParameters, typename ReturnType>
		WrapperEvent<CallbackParameters, ReturnType>::WrapperEvent(){
#ifdef DEBUG
			DebugLog("Created Wrapper Event");
#endif // DEBUG
		}
		template<typename CallbackParameters, typename ReturnType>
		WrapperEvent<CallbackParameters, ReturnType>::~WrapperEvent() {
			Subscribers.Clear();
#ifdef DEBUG
			DebugLog("Deleted Wrapper Event");
#endif // DEBUG
		}
		template<typename CallbackParameters, typename ReturnType>
		void WrapperEvent<CallbackParameters, ReturnType>::Subscribe(FunctionWrapper* _other) {
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
#ifdef DEBUG
			DebugLog("Added Wrapper to Event");
#endif // DEBUG
		}
		template<typename CallbackParameters, typename ReturnType>
		void WrapperEvent<CallbackParameters, ReturnType>::UnSubscribe(FunctionWrapper* _other) {
			try {
				if (Subscribers == nullptr)
					throw std::invalid_argument("Event not Intialized!");
				if (Subscribers != _other)
					throw std::invalid_argument("Function Pointers Do Not Match!");
				else
					if (_other->Index < 0)
						throw std::invalid_argument("Out of Bounds Index!");
					else
						if (Subscribers[_other->Index] == _other) {
							Subscribers -= _other->Index;
							_other->Index = -1;
						}
						else 
							if(Subscribers[_other->Index] == _other)
								throw std::invalid_argument("Function Listner Does Not Match!");
						else
							throw std::invalid_argument("Out of Bounds Index!");
			}
			catch (std::invalid_argument e)
			{
				std::cout << e.what() << std::endl;
			}
#ifdef DEBUG
			DebugLog("Removed Wrapper from Event");
#endif // DEBUG
		}
		template<typename CallbackParameters, typename ReturnType>
		inline void WrapperEvent<CallbackParameters, ReturnType>::operator+=(FunctionWrapper* _other) {
			Subscribe(_other);
		}
		template<typename CallbackParameters, typename ReturnType>
		inline void WrapperEvent<CallbackParameters, ReturnType>::operator-=(FunctionWrapper* _other) {
			UnSubscribe(_other);
		}
		template<typename CallbackParameters, typename ReturnType>
		void WrapperEvent<CallbackParameters, ReturnType>::Invoke(const CallbackParameters& _args) {
			for (int i = 0; i < Subscribers.GetSize();i++)
			{
				Subscribers[i]->Callback(_args);
			}
#ifdef DEBUG
			DebugLog("Invoked Event");
#endif // DEBUG
		}
		template<typename CallbackParameters, typename ReturnType>
		void WrapperEvent<CallbackParameters, ReturnType>::InvokeThreaded(const CallbackParameters& _args) {
#ifdef DEBUG
			DebugLog("Invoked Multi-Thread Event");
#endif // DEBUG
		}
#pragma endregion
	}
}
