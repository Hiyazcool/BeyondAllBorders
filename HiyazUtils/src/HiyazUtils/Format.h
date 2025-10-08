#pragma once
#include "String.h"
#include "IPrintable.h"
using namespace HiyazUtils;
namespace HiyazUtils { 
namespace Format {
	namespace StringConstants {
		const constexpr char* Colon = ": ";
		const constexpr char* Comma = ", ";
		const constexpr char* NewLine = "\n";
	}
	template<typename ...Args>
	static string& FormatIntoString(Args& ..._args);
	template<typename ...Args>
	static void FormatString(string* _destination, Args& ..._args);
	template<typename ...Args>
	static void FormatIntoStringList(string* _destination, Args& ..._args);
	static void FillCharArray(char* _destination, char* _source);
	static void FillCharArray(char* _destination, char*&& _source); // rValue
	static void FillCharArray(char* _destination, string* _source);
	static void FillCharArray(char* _destination, IPrintable* _source);
	template<typename ...Args>
	static size_t CalculatestringLength(char* _string, Args& ..._args);
	template<typename ...Args>
	static size_t CalculatestringLength(string* _string, Args& ..._args);
	template<typename ...Args>
	static size_t CalculatestringLength(IPrintable* _string, Args& ..._args);
	static size_t CalculatestringLength(char* _string);
	static size_t CalculatestringLength(string* _string);
	static size_t CalculatestringLength(IPrintable* _string);
}}
