#pragma once
class IPrintable {  // Seperate Into Seperate File So Format and Print Can use it without conflicting with eachother
public:
	// Used to Display All Relevent Info for Debugging Purposes Default Overloaded to Print with Implicit Cast to Char*
	virtual const char* PrintDebugInfo() = 0;
	// Operator Overload Simple as that
	operator const char* () { return PrintDebugInfo(); }
	// Used to Display Critical Info, that Would Pertain to Testing
	virtual const char* const ToString() = 0;
};