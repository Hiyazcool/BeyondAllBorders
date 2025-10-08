#pragma once
#include "Core.h"
#include <tuple>
#include "Print.h"
#include "Format.h"
/*
Make Thread Safe

*/
namespace HiyazUtils {
#define DebugLog(n) Logger::Log(LogPriority::Debug,##n)
	namespace Log {
		enum LogPriority
		{
			Debug = 0,
			Info = 1,
			Warn = 2,
			Error = 3,
			Critical = 4,
		};
		class HIYAZUTILS_API Logger {
		private:
			static LogPriority CurrentPriority;
			template<typename...Args>
			void static Log(Args&... args) {
				printf(args...);
				printf("\n");
			}
		public:
			Logger();
			void static SetPriority(LogPriority _priority);
			template<typename...Args>
			void static Log(LogPriority _priority = LogPriority::Info, Args& ...args) {
				if (_priority < CurrentPriority)
					return;
				switch (_priority)
				{
				case Info:
					printf("[Info] : ");
					Log(args...);
					break;
				case Warn:
					printf("[Warn] : ");
					Log(args...);
					break;
				case Error:
					printf("[Warn] : ");
					Log(args...);
					break;
				case Critical:
					printf("[CRITICAL] : ");
					Log(args...);
					break;
				case Debug:
					printf("[Debug] : ");
					Log(args...);
					break;
				default:
					printf("[CRITICAL] : Unknown Log Switch Value");
					break;
				}
			}
		};
	}
}
