#pragma once
#include <iostream>

#ifdef _DEBUG
	#define ASSERT(x) if(!!(x)) {} else __debugbreak()
	#define LOG(x) std::cout << (x) << std::endl; 

	#define GLCall(x) GLClearError();\
		x;\
		ASSERT(GLLogCall(#x, __FILE__, __LINE__))
#else
	#define ASSERT(x) x
	#define LOG(x) x
	#define GLCall(x) x
#endif

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);