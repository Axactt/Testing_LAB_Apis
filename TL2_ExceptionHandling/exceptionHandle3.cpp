#include<Windows.h>
#include<cstdio>
#include "exceptionHandle3.h"

//! more complex handling decisioon of exception is coneverted to filter expression function which return one of the three constatnts 1,0 or -1
int CanHandle( DWORD code ) 
{
	//! More better elaborated code
	if (code == EXCEPTION_INT_DIVIDE_BY_ZERO
		 || code == EXCEPTION_FLT_DIVIDE_BY_ZERO)
		return EXCEPTION_EXECUTE_HANDLER;
	return EXCEPTION_CONTINUE_SEARCH;

}


int sample3( int x )
{
	int y = 0;
	__try
	{
		++x;
		y = 10 / x;
		printf( "10 / %d=%d\n", x, y );

	}
	//? Illegal to call GetExceptionCode() in arbitrary function other than filter expression or __except block body
	__except (CanHandle( GetExceptionCode() ))
	{
		printf( "Handling divide by zero exception only\n" );

	}
	//! If exception is handled by __except handler block the execution will continueafter the block

    return y;
}
