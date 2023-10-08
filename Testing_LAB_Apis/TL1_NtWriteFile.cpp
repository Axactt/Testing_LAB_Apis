#define PHNT_VERSION PHNT_WIN10_21H2 //! to match sdk with windows version
#include"phnt.h"  //! Used instead of windows.h
//! Imports for ntdll.dll
#pragma comment(lib, "ntdll.lib")

static char message[] = "Hello, phnt!\r\n";

int main(  )
{
	IO_STATUS_BLOCK IoStatusBlock = { 0.0 };
	NtWriteFile(
		NtCurrentPeb()->ProcessParameters->StandardOutput,
		NULL,
		NULL,
		NULL,
		&IoStatusBlock,
		message,
		strlen( message )-1 ,
		NULL,
		NULL
	);
	
	return 0;
}