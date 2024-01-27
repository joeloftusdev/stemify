#ifdef SPLEETERLIB_EXPORTS
#define SPLEETERLIB_API __declspec(dllexport)
#else
#define SPLEETERLIB_API __declspec(dllimport)
#endif

#include <iostream> 
#include <cstring>
#include <vector>

class SPLEETERLIB_API CSpleeterLib {
public:
	CSpleeterLib(void);
};

extern SPLEETERLIB_API int nSpleeterLib;
SPLEETERLIB_API int fnSpleeterLib(void);

extern "C"
{
	typedef void (*CallbackFunction)(const char* message);
	SPLEETERLIB_API int fnSpleeterLibGenerateStems(const char* sourceFile, const char* targetDir, const int numOfStems, CallbackFunction callbackFunction);
}

