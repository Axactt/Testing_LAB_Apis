#define BUILD_WINDOWS
#include<Windows.h>
#include <iostream>
//! C++-> Advanced->IgnoreSpecificWarnings->4996

#pragma  comment(lib,"ntdll.lib")

extern "C"
void WINAPI RtlGetVersion( OSVERSIONINFO* ); // Implemented in ntdll.dll to get real windows version


int main()
{

	OSVERSIONINFO osi = { sizeof( osi ) }; // Initializing a kernel strcuture with size of structure
    RtlGetVersion( &osi );
	//GetVersionEx(&osi); // will not give real version
	printf( "%d.%d.%d\n", osi.dwMajorVersion, osi.dwMinorVersion, osi.dwBuildNumber );
	return 0;
}
