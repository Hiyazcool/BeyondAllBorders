#pragma once
#include<iostream>
#include"Define.h"
namespace HiyazUtils {
	namespace Format {
		/*
Todo: 
		String Class:
				Fix Comparison operators when comparing Char* (includes termination char)
				Fill out More Functionality
				Do a more versatile test

			Interesting Ideas ( * Are Planned )
			*	<<,<<= and >>,>>= Shift Characters around ( Hello ->  << -> elloH -> << -> lloHe )
					Might just do Shift Functions
			*	~ Siwtches Capitalization ( Hello -> ~ -> hELLO )
			*	++ and -- Increase / Decrease Char Values ( Hello -> ++ -> Ifmmp -> ++ -> Jgnnq )
			*	[ ] Obvious What they Do
				- and -= Remove Right Operand from Left ( "Hello" -> -'o' -> "Hell" -> -"el" -> "Hl")
						Needs More Revision
			*	Scramble Function ( Hello -> Scramble() -> ULgw0 )
					Optional Unsigned Int for Num of times to scramble
					Optional to Scramble with certain characters?
						Like a Matrix thing???
				Encode Function Because Why Not
				Convert to Int Adds all Char Values and returns
				& Compares between two strings returning chars that both share
				| Compares between two strings returning all chars they have
				/ Find how many instances supplied char/string Occur with in string
				% Find how many characters are not Supplied char/string
		Randomize String Function
		Char Const Arrays



		*/

		// All Letters of the English Alphabet both Uppercase and Lowercase
		constexpr char FullAlphabet[53] = {
			"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
		};
		// All Uppercase Letters of the English Alphabet
		constexpr char UppercaseAlphabet[27] = {
			"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		};
		// All Lowercase Letters of the English Alphabet
		constexpr char LowercaseAlphabet[27] = {
			"abcdefghijklmnopqrstuvwxyz"
		};
		// All Numerical Digits
		constexpr char FullDigits[11] = {
			"0123456789"
		};
		// All Letters of the English Alphabet both Uppercase and Lowercase and Numerical Digits
		constexpr char FullAlphabetAndDigits[63] = {
			"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
		};
		// All Symbols on a Standard QWERTY Keyboard
		constexpr char Symbols[33] = {
			"!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~"
		};
		// All Symbols Commonly Used to Censor Swears
		constexpr char SwearSymbols[8] = {
			"!@#$%&?"
		};
		// All Characters on a Standard QWERTY Keyboard
		constexpr char FullKeyboard[95] = {
			"!\"#$%&\'()*+,-./:;<=>?@[\\]^_`{|}~0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
		};
		// Both Binary Characters
		constexpr char Binary[3] = {
			'1','0'
		};
		// All Hexadecimal Characters
		constexpr char Hexadecimal[17] = {
			"0123456789ABCDEF"
		};
		
		// A Array of Characters Used to Display Text to the Console with Various Functions and Quality of Life Features
		class string {
			char* stringArray;
			size_t stringSize;
			static void AddTo(char*, const char*&&);
			static void AddTo(char*, const char*);
			static void AddTo(char*, string&&);
			static void AddTo(char*, string&);
		public:

			// Default Constructer, String of Size "0" and a Value of "nullptr"
			string();
			// Constructor for a lValue Reference
			string(string&);
			// Constructor for a rValue Reference, Resulting in Taking Ownership of the Orignal Values, Instead of Copying
			string(const char*&&);
			// Constructor for a rValue Reference, Resulting in Taking Ownership of the Orignal Values, Instead of Copying
			string(string&&);
			// Deconstructor
			~string();
#pragma region Miscellaneous Functions
		public:
			// Clears Data, Setting Size to 0 and Deleting the Array and Setting it to nullptr
			void Clear();
			// Returns Char Array
			char*& RetrieveData(); // Make it private so only this string and other strings can modify
			// Returns Char Array
			char* RetrieveData() const;
			// Returns String Size in size_t
			inline size_t Size() const {
				return stringSize;
			}
			// Implicit Char Array Conversion
			inline operator char* () {
				return stringArray;
			}
			// Implicit Size Conversion
			inline operator size_t () {
				return stringSize;
			}
			// Allows Access to Char Array, with Bound Checking
			inline char& operator[](uint _index) {
				if (_index < stringSize)
					return stringArray[_index];
			}
			// Allows Access to Char Array, with Bound Checking
			inline char& operator[](uint _index) const {
				if (_index < stringSize)
					return stringArray[_index];
			}
			// Shifts the String to the Left a Number of Times, Then Returns the new String as an rValue Reference
			inline string&& operator<<(uint) const;
			// Shifts the String to the Right a Number of Times, Then Returns the new String as an rValue Reference
			inline string&& operator>>(uint) const;
			// Shifts the String to the Left a Number of Times, Then Reassigns the Original String to the New String
			inline void operator<<=(uint);
			// Shifts the String to the Right a Number of Times, Then Reassigns the Original String to the New String
			inline void operator>>=(uint);
			// Reverses Capitalization of Characters, No Effect on Non-Letter Characters
			inline void operator~();
			// Randomizes the String Array a Number of Times [Default = "1"]
			inline void RandomizeString(uint = 1, const char* = FullDigits);
			// Scramble the String Array a Number of Times [Default = "1"]
			inline void Scramble(uint = 1);
			// Adds One to the Value of All Characters in the String
			inline string& operator++();
			// Adds One to the Value of All Characters in the String, returning a copy of the orignal string to be used for the rest of the expression
			inline string operator++(int);
			// Subtracts One to the Value of All Characters in the String
			inline string& operator--();
			// Subtracts One to the Value of All Characters in the String, returning a copy of the orignal string to be used for the rest of the expression
			inline string operator--(int);
#pragma endregion
#pragma region Addition and Assignment Operators
		public:
			// Adds Two Strings/Char Arrays Together Returning a rValue String Reference
			inline string&& const operator+(string&&) const;
			// Adds Two Strings/Char Arrays Together Returning a rValue String Reference
			inline string&& const operator+(string&) const;
			// Adds Two Strings/Char Arrays Together Returning a rValue String Reference
			inline string&& const operator+(const char*&&) const;
			// Adds Two Strings/Char Arrays Together Returning a rValue String Reference
			inline friend string&& const operator+(const char*&& _stringOne, string&& _stringTwo) {
				size_t newStringSize = strlen(_stringOne) + strlen(_stringTwo);
				char* newArray = new char[newStringSize + 1];
				AddTo(newArray, _stringOne);
				size_t index = strlen(_stringOne);
				AddTo(newArray + index, _stringTwo);
				newArray[newStringSize] = 0;
				string* newString = new string(std::move(newArray));
				string& returnString = *newString;
				newArray = nullptr;
				newString = nullptr;
				return std::move(returnString);
			}
			// Adds Two Strings/Char Arrays Together Returning a rValue String Reference
			inline friend string&& const operator+(const char*&& _stringOne, string& _stringTwo) {
				size_t newStringSize = strlen(_stringOne) + strlen(_stringTwo);
				char* newArray = new char[newStringSize + 1];
				AddTo(newArray, _stringOne);
				size_t index = strlen(_stringOne);
				AddTo(newArray + index, _stringTwo);
				newArray[newStringSize] = 0;
				string* newString = new string(std::move(newArray));
				string& returnString = *newString;
				newArray = nullptr;
				newString = nullptr;
				return std::move(returnString);
			}
			// Adds Two Strings/Char Arrays Together Assigning the Result to the first Operand
			inline void const operator+=(string&&);
			// Adds Two Strings/Char Arrays Together Assigning the Result to the first Operand
			inline void const operator+=(const char*&&);
			// Adds Two Strings/Char Arrays Together Assigning the Result to the first Operand
			inline void const operator+=(string&);
			// Sets the Left Operand String to the Value of the Right String/Char Array
			inline void const operator=(string&&);
			// Sets the Left Operand String to the Value of the Right String/Char Array
			inline void const operator=(const char*&&);
			// Sets the Left Operand String to the Value of the Right String/Char Array
			inline void const operator=(string&);
#pragma endregion


#pragma region Comparison Templates
			// Compares the String Length to the Right Operands Value [ In Terms of String Length for Strings and Char Arrays]
			template<typename T>
			inline bool const operator==(T& _other) const {
				return (unsigned int)stringSize == (unsigned int)_other;
			}
			// Compares the String Length to the Right Operands Value [ In Terms of String Length for Strings and Char Arrays]
			template<typename T>
			inline bool const operator!=(T& _other) const {
				return (unsigned int)stringSize != (unsigned int)_other;
			}
			// Compares the String Length to the Right Operands Value [ In Terms of String Length for Strings and Char Arrays]
			template<typename T>
			inline bool const operator<=(T& _other) const {
				return (unsigned int)stringSize <= (unsigned int)_other;
			}
			// Compares the String Length to the Right Operands Value [ In Terms of String Length for Strings and Char Arrays]
			template<typename T>
			inline bool const operator>=(T& _other) const {
				return (unsigned int)stringSize >= (unsigned int)_other;
			}
			// Compares the String Length to the Right Operands Value [ In Terms of String Length for Strings and Char Arrays]
			template<typename T>
			inline bool const operator<(T& _other) const {
				return (unsigned int)stringSize < (unsigned int)_other;
			}
			// Compares the String Length to the Right Operands Value [ In Terms of String Length for Strings and Char Arrays]
			template<typename T>
			inline bool const operator>(T& _other) const {
				return (unsigned int)stringSize > (unsigned int)_other;
			}
#pragma endregion
		};
		// Checks Whether the String is Empty, If Not it Returns the Char Array to the Output Stream
		inline std::ostream& operator<<(std::ostream& stream, const string& string) {
			if (string.RetrieveData() == nullptr)
				stream << "[String is Empty]";
			else
				stream << string.RetrieveData();
			return stream;
		}
	}
}