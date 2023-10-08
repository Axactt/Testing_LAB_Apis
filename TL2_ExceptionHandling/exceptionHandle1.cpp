#include<Windows.h>
#include<cstdio>
#include"exceptionHandle1.h"
int sample1( int x )
{
	int y {};
	__try
	{
		++x;
		y = 10 / x;
		printf( "y = %d\n", y );

	}
	__except (EXCEPTION_EXECUTE_HANDLER) //! this wil cause code in except block to execute; very generic exception-handling and swallowing
	{
		printf( "Handling exception 0x%X\n", GetExceptionCode() ); //!GetExceptionCode compiler instrinsics translated to machine code for generating exception code value stated in winnt.h
	}

	return y;

}