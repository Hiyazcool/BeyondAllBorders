#include <iostream>
#include "Format.h"
namespace HiyazUtils {
	namespace Format {
		string::string() :
			stringSize(0),
			stringArray(nullptr) {
		}
		inline string::~string() {
			std::cout << "Deleted " << stringArray << std::endl;
			delete[] stringArray;
		}
		inline void string::Clear() {
			stringSize = 0;
			delete[] stringArray;
		}
		inline char*& string::RetrieveData() {
			return stringArray;
		}
		inline char* string::RetrieveData() const {
			return stringArray;
		}
		inline void string::AddTo(char* _dstArray, const char*&& _srcArray) {
			memmove(_dstArray, _srcArray, strlen(_srcArray) + 1);
		}
		inline void string::AddTo(char* _dstArray, const char* _srcArray) {
			memcpy(_dstArray, _srcArray, strlen(_srcArray) + 1);
		}
		inline void string::AddTo(char* _dstArray, string&& _srcArray) {
			memmove(_dstArray, _srcArray, strlen(_srcArray) + 1);
		}
		inline void string::AddTo(char* _dstArray, string& _srcArray) {
			memcpy(_dstArray, _srcArray, strlen(_srcArray) + 1);
		}
		string::string(string& _array) :
			stringSize(strlen(_array)),
			stringArray(nullptr) {
			stringArray = new char[stringSize + 1];
			memcpy(stringArray, _array, stringSize + 1);
		}
		string::string(const char*&& _array) :
			stringSize(strlen(_array)),
			stringArray(nullptr) {
			stringArray = new char[stringSize + 1];
			memmove(stringArray, _array, stringSize + 1);
			_array = nullptr;
		}
		string::string(string&& _other) :
			stringSize(0),
			stringArray(nullptr) {
			stringArray = _other;
			stringSize = _other.Size();
			_other.RetrieveData() = nullptr;
			_other.Clear();
		}
		inline string&& string::operator<<(uint _shiftAmount) const {

		}
		inline string&& string::operator>>(uint _shiftAmount) const {

		}
		inline void string::operator>>=(uint _shiftAmount) {

		}
		inline void string::operator<<=(uint _shiftAmount) {

		}
		inline void string::operator~() {

		}
		inline void string::Scramble(uint _scambleAmount) {

		}
		inline void string::RandomizeString(uint _scambleAmount, const char* _allowedChars) {

		}
		inline string& string::operator++() {

		}
		inline string string::operator++(int) {

		}
		inline string& string::operator--() {

		}
		inline string string::operator--(int) {

		}
		inline string&& const string::operator+(string&& _other) const {
			size_t newStringSize = strlen(stringArray) + strlen(_other);
			char* newArray = new char[newStringSize + 1];
			AddTo(newArray, stringArray);
			size_t index = strlen(stringArray);
			AddTo(newArray + index, _other);
			newArray[newStringSize] = 0;
			string* newString = new string(std::move(newArray));
			string& returnString = *newString;
			newArray = nullptr;
			newString = nullptr;
			return std::move(returnString);
		}
		inline string&& const string::operator+(string& _other) const {
			size_t newStringSize = strlen(stringArray) + strlen(_other);
			char* newArray = new char[newStringSize + 1];
			AddTo(newArray, stringArray);
			size_t index = strlen(stringArray);
			AddTo(newArray + index, _other);
			newArray[newStringSize] = 0;
			string* newString = new string(std::move(newArray));
			string& returnString = *newString;
			newArray = nullptr;
			newString = nullptr;
			return std::move(returnString);
		}
		inline string&& const string::operator+(const char*&& _other) const {
			size_t newStringSize = strlen(stringArray) + strlen(_other);
			char* newArray = new char[newStringSize + 1];
			AddTo(newArray, stringArray);
			size_t index = strlen(stringArray);
			AddTo(newArray + index, _other);
			newArray[newStringSize] = 0;
			string* newString = new string(std::move(newArray));
			string& returnString = *newString;
			newArray = nullptr;
			newString = nullptr;
			return std::move(returnString);
		}
		inline void const string::operator+=(string&& _other) {
			*this = std::move(*this + std::move(_other));

		}
		inline void const string::operator+=(const char*&& _other) {
			*this = std::move(*this + std::move(_other));
		}
		inline void const string::operator+=(string& _other) {
			*this = std::move(*this + _other);
		}
		inline void const string::operator=(string&& _other) {
			if (*this == _other)
				return;
			if (stringArray != nullptr)
				delete[] stringArray;
			stringSize = strlen(_other);
			stringArray = new char[stringSize + 1];
			memmove(stringArray, std::move(_other), strlen(_other) + 1);
			_other.RetrieveData() = nullptr;
			_other.Clear();
		}
		inline void const string::operator=(const char*&& _other) {
			if (*this == _other)
				return;
			if (stringArray != nullptr)
				delete[] stringArray;
			stringSize = strlen(_other);
			stringArray = new char[stringSize + 1];
			memmove(stringArray, _other, strlen(_other) + 1);
			_other = nullptr;
		}
		inline void const string::operator=(string& _other) {
			if (*this == _other)
				return;
			if (stringArray != nullptr)
				delete[] stringArray;
			stringSize = strlen(_other);
			stringArray = new char[stringSize + 1];
			memcpy(stringArray, _other, strlen(_other) + 1);
		}
	}
}

