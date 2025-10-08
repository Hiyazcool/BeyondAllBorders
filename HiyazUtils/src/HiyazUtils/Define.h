#pragma once
/*
	Define These for special platforms
		https://stackoverflow.com/questions/32198368/unsigned-long-long-conflict-with-uint64-t
*/
// int with range of 	0 to 4,294,967,295
#define uint unsigned
// int with range of 0 to 18,446,744,073,709,551,615
#define uint64 unsigned long long
// int with range of -9,223,372,036,854,775,808 to 9,223,372,036,854,775,807
#define int64 long long
// int with range of 0 to 65,535
#define ushort unsigned short
#define DEBUG
#define CATCHBLOCK catch (std::invalid_argument e) { #ifdef DEBUG DebugLog(e.what); #endif }