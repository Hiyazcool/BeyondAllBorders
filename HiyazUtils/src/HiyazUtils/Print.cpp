#include "Print.h"
namespace HiyazUtils {
	namespace Print {
		inline const static void Print(const char* _pointer) {
			std::cout << _pointer;
		}
		inline const static void Print(const std::string _pointer) {
			std::cout << _pointer;
		}
		inline const static void Print(const Format::string* _pointer) {
			//std::cout << *_pointer;
		}
		inline const static void Print(const IPrintable* _pointer) {
			std::cout << _pointer;
		}

		inline const static void PrintL(const char* _pointer) {
			std::cout << _pointer << std::endl;
		}
		inline const static void PrintL(const std::string _pointer) {
			std::cout << _pointer << std::endl;
		}
		inline const static void PrintL(const Format::string* _pointer) {
			std::cout << _pointer << std::endl;
		}
		inline const static void PrintL(const IPrintable* _pointer) {
			std::cout << _pointer << std::endl;
		}
	}
}