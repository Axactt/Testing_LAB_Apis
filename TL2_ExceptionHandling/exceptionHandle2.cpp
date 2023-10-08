#include<Windows.h>
#include<cstdio>
#include"exceptionHandle2.h"


int sample2( int x )
{
	int y {};
	__try
	{
		++x;
		y = 10 / x;
		printf( "y = %d\n", y );

	}
	//! GetExceptionCode() can only be in invoked in except expression or its block
	//! Handling/swallowing only a particular kind of expression in except block
	__except (GetExceptionCode()==EXCEPTION_INT_DIVIDE_BY_ZERO
			   ? EXCEPTION_EXECUTE_HANDLER
			   : EXCEPTION_CONTINUE_SEARCH) 
	{
		printf( "Handling exception 0x%X\n", GetExceptionCode() ); //!GetExceptionCode compiler instrinsics translated to machine code for generating exception code value stated in winnt.h
	}

	return y;

}