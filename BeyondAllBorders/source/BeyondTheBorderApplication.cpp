#include <Auxilium.h>
#include <iostream>
#include <thread>
#include <chrono>

namespace BeyondTheBorder {
void Thread(long long* boop) {
	long long& value = (*boop);
	while (true) {
		for (int i = 0; i < 5; i++)
			boop[i]++;
		//std::cout << "w";
		
		//(*boop)++;
	}
}
	class BeyondTheBorderApplication : public Auxilium::Application
		{

		public:	

			//value++;
			//Thread(value);
		
			BeyondTheBorderApplication() {
				LOG_DEBUG("Creating Application");
			}
			~BeyondTheBorderApplication() {
			}
			void Run() override {
				LOG_INFO("Running");
				 long long* doop = new long long[5];
				 long long* doop2 = new long long[5];
				 
				 for (int i = 0; i < 5; i++){
					 doop[i]= 0;
					 doop2[i]= 0;
				 }
				
				using namespace std::chrono_literals;
				std::thread myThread(Thread,doop);
				
				std::thread myThread2(Thread,doop2);
				std::this_thread::sleep_for(1000ms);
				for (int i = 0; i < 5; i++) {
					std::cout << doop[i]<< "," << doop[i] <<"\n";
				}
				std::this_thread::sleep_for(1000ms);
				for (int i = 0; i < 5; i++) {
					std::cout << doop[i]<< "," << doop[i] <<"\n";
				}
				
				
				LOG_INFO("Running");
				myThread.join();
				std::cin.get();

			}
	};
}

Auxilium::Application* Application::CreateApplication() {
	return new BeyondTheBorder::BeyondTheBorderApplication();
}