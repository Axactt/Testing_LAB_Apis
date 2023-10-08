#include<Windows.h>
#include<cstdio>
//! Creating anonymous pipe to read write half duplex by inheritng handle
//! sharing one end of anon pipe read/write handle to another process so one side writes other reads
//! ReadFile and writefile api used to read and write to one of the end of PIpe

int Error( const char* message )
{
	printf( "%s(error=%u)\n", message, GetLastError() );
	return 1;
}

int main()
{
	HANDLE hRead {};
	HANDLE hWrite {};

	if (!::CreatePipe( &hRead, &hWrite, nullptr, 0 ))
		return Error( "Failed to create anon pipe" );
  //! write-handle to be inheritable to be used by newly craeted process
	::SetHandleInformation( hWrite, HANDLE_FLAG_INHERIT, HANDLE_FLAG_INHERIT );


	//! CREATE cmd.exe while inheriting the handle as standard output handle
	PROCESS_INFORMATION pi;
	STARTUPINFO si = { sizeof( si ) };
	si.hStdOutput = hWrite;
	si.dwFlags = STARTF_USESTDHANDLES; //! to use differnt input/output device handles frm default(keyboard and monitor)
	WCHAR name[] = L"cmd.exe";
	if (!::CreateProcess( nullptr, name, nullptr, nullptr, TRUE, CREATE_NEW_CONSOLE, nullptr, nullptr, &si, &pi ))
		return Error( "Failed to create cmd process" );
	CloseHandle( pi.hThread ); // thread handle not needed
	CloseHandle( hWrite ); //! write handle duplicated/inherited in cmd.exe and write pipe handle not needed.
	
	
	// Read data from REad end of pipe and do something with it and print it into the SimplePipe console
	char text[512];
	ULONG read ;
	//If dwMilliseconds is zero, the function does not enter a wait state if the object is not signaled; it always returns immediately. If dwMilliseconds is INFINITE, the function will return only when the object is signaled.
	while (::WaitForSingleObject( pi.hProcess, 0 ) == WAIT_TIMEOUT)
	{
		if (!::ReadFile( hRead, text, sizeof(text)-1, &read, nullptr));
		break;
		//null-terminate the string
		text[read] = 0;
		printf( "%s", text );

	}
	::CloseHandle( hRead );
	::CloseHandle( pi.hProcess );
	return 0;
}