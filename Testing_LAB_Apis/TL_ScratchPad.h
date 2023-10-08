#define PHNT_VERSION PHNT_WIN10_21H2 //! to match sdk with windows version

#include "phnt.h" //! Instead of windows.h

//! Imports for ntdll
#pragma comment (lib,"ntdll.lib") //! 



struct CriticalSectionLocker
{
	CRITICAL_SECTION& m_cs;

	CriticalSectionLocker( CRITICAL_SECTION& cs ) :m_cs( cs )
	{
		::EnterCriticalSection( &cs );
	}
	~CriticalSectionLocker()
	{
		::LeaveCriticalSection( &m_cs );
	}	
};

//! SetUnhandledExceptionFilter callback typedef prototype
typedef LONG( WINAPI* PTOP_LEVEL_EXCEPTION_FILTER )(
	_In_ struct _EXCEPTION_POINTERS* ExceptionInfo);


//! Calling SetUnhandledExceptionFilter replaces the current unhandled exception filter function with new one.
//! SetUnHandledExceptionFilter returns previous top-level-exception-filter which was replaced by argument of SetUndledFilterException function

LPTOP_LEVEL_EXCEPTION_FILTER
SetUnhandledExceptionFilter(
	_In_opt_ LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter );

LONG UnHandledExceptionFilter( PEXCEPTION_POINTERS );

//! Creation of user thread is always enclosed in __try / __except block
void RtlUserThreadStart( PTHREAD_START_ROUTINE StartAddress, PVOID Argument,... )
{
	__try
	{
		RtlExitUserThread( StartAddress( Argument ) );
	}
	__except (UnHandledExceptionFilter( GetExceptionInformation() ))
	{
		NtTerminateProcess( NtCurrentProcess(), // Exitproces
							GetExceptionCode() );
	}


}

//! normally searching for handlers is performed up the callstack of offending thread
//! VEH allows being notified of exceptions from any thread by registering a callback function
// Add a VEH
typedef LONG( WINAPI* PVECTORED_EXCEPTION_HANDLER )(
	PEXCEPTION_POINTERS ep
	);

PVOID AddVectoredEcxeptionHandler(
	_In_ ULONG First,
	_In_ PVECTORED_EXCEPTION_HANDLER Handler );
