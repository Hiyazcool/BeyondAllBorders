#pragma once
#include <string>
#include <iostream>
#include "Format.h"
namespace HiyazUtils {
	namespace Print { 
		template<typename ...Args>
		inline static void Print(Args& ..._args) {
			Print(FormatString(_args));
		}
		inline const static void Print(const char* _pointer);
		inline const static void Print(const std::string _pointer);
		inline const static void Print(const Format::string* _pointer);
		inline const static void Print(const IPrintable* _pointer);

		template<typename T, typename ...Args>
		inline const static void PrintL(bool _isSeperateLines, T _string, Args& ..._args) {
			if (_isSeperateLines)
				Print(FormatIntoStringList(true, _string, _args));
			else
				PrintL(FormatString(_string, _args));
		}
		inline const static void PrintL(const char* _pointer);
		inline const static void PrintL(const std::string _pointer);
		inline const static void PrintL(const Format::string* _pointer);
		inline const static void PrintL(const IPrintable* _pointer); 
	}
}
