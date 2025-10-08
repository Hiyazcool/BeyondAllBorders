This Shouldnt be called ReadMe in all Intents and Purposes, BUT I am having fun so f off
And the Point of My Util Library is nto to be better than the Standard Library or anyone else I am just Trying to learn how to do everything so I thought "Well I need to practice on something, soooooo why don't I Just make a better Standard library than than the Standard Library and everyone else!" ( I'm not self-absorbed, I'm Humorous, and-self absorbed!)
------------------------------ Todo : In order of Priority --------------------------------------

	Add Try/Catch Blocks to more Risky Code Sections
		Mainly when Pointers are involved
	Define some more Preproccessors  (Like uint)
		Event Wrapper?
		Lambdas?
*****		#Define DEBUG
*****			for #IFDEF DEBUG Blocks
	
	Do this -> https://learn.microsoft.com/en-us/cpp/build/reference/summary-visual-cpp?view=msvc-170
	
	Need to understand why the string is calling destructor
		is it using non ref types?
		is it because I am using a ref then a non ref????????????????
		is it because I am stupid (Probably)
			I believe it has to do with with the Template regard the args as non Ref or OOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
				IT ALWAYS HAPPENS AFTER THE SIMPLIFY RETURN VALUE GOES OUT OF SCOPE I THINK 
				Idk
	Learning Events / Setting up Events for Game Engine
	Unique/Smart Pointers
		Going to be Frustrating TBH
	Rebuild Log
		I need to figure out how to use preproccessors properly to really use this effectively
		Doesnt need to be a class, just a namespace
		LONGTERM:
			Output to File for ease of use????????
				Idk
			Can I setup a Non-member Func that I can Overload???????????
				So each different type can overload it (ToLog or something, Idk if ToString is taken in default c++)
				Or is this too complicated? (Probably, Will focus on another avenue like IToString interface or overloading <<) 
	Rebuild Print
		Should be Mostly if Not All inline just use Print as a easier way then cout because cout looks stupid IMO
		Doesnt need to be a class, just a namespace
	Expand on List/Array
		Maybe look into rewrite to optimise
	Thread Manager?
	Deprecated--Expand on String
		Rewrite String (Mostly)
			Implicit Conversion to Char*
			Need to make all operator overloads use char*s or strings idk yet, but I need to prevent ambiguity
				I beleive since there would be a Overload for each it will take the string overload before trying to convert
			Make Most of it Inline?
			Add IPrintable Pointer Overloads
	Build Format
		Needs to be Seperate from string BUT maybe look into Moving some String Functionality to Format Since I THINK I know the Header problem enough to solve
		Doesnt need to be a class, just a namespace
Event Abstract class????? 
	Need to figure out how to implent abstract wrapper for subscribers, I believe I need to go down the pointer route instead of a reference?
	+=/-= control listners (Supplemented by Subscribe/Unsubscribe Functions)
	Invoke/InvokeWithThreads
------------------------------ Already Did List (Major Points) -----------------------------------
Planned out: (To an Extent)
	Format
	Print
------------------------------ Spicy Ideas -------------------------------------------------------

Stupid Idea, use a function pointer to move a to b in string inside a forloop for each string just to spice things up
use bit shifting to just move the array data directly in chunks????

Also I REALLY WANT TO GET INTO THREADING, but I am hella not ready for it, I barely Understood how to use it effectively in C#! BUT I WANT TO, especially since I want to make a thread manager for it, because I hate myself and love the idea.

------------------------------ Notes For Me ------------------------------------------------------

Make strings implicitly convert to Rvalue References to reduce Overloads and Hopefully fix the Errors

https://stackoverflow.com/questions/4421706/what-are-the-basic-rules-and-idioms-for-operator-overloading

	IMPLICIT CONVERSION OPERATORS
		AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
	WHY DIDNT I THINK THAT IN REALITY IT WAS JUST A CONVERSION 
		IMMMMMM SOOOOO STUPIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIIDDDDDDD!!!!!!!!!!!!!!
	I am very happy now ^_^

https://learn.microsoft.com/en-us/cpp/cpp/reference-type-function-returns?view=msvc-170
https://learn.microsoft.com/en-us/cpp/cpp/rvalue-reference-declarator-amp-amp?view=msvc-170
https://learn.microsoft.com/en-us/cpp/cpp/temporary-objects?view=msvc-170
https://learn.microsoft.com/en-us/cpp/cpp/abstract-classes-cpp?view=msvc-170

Event Notes
https://en.cppreference.com/w/cpp/utility/functional/bind
https://en.cppreference.com/w/cpp/utility/functional/function
https://en.cppreference.com/w/cpp/utility/functional/invoke

CPP REFERENCE IS GREAT
constexpr
inline
friend

need to understand Volatile

Ptr string = new string() <-Stack allocated
Ptr* string = new string() <- Heap allocated

CrtIsValidHeapPointer 
			- https://stackoverflow.com/questions/64418624/why-do-i-get-crtisvalidheappointerblock-and-or-is-block-type-validheader-b
			- double delete or deleteing non heap mem
Heap corruption detected: after normal block 
			 - crt detected that the application wrote to memory after end of heap buffer. from deleting an array
			 - https://stackoverflow.com/questions/42390103/heap-corruption-detected-after-normal-block-crt-detected-that-the-applicatio
			 - Array[Out of bounds int] error throws at Delete

Public Templates -> _Overloads


