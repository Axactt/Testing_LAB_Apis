#include<windows.h>
#include<cstdio>
//! EXCEPTION_CONTINUE_EXECUTION example for divide by zero exception
int x {};
int y {};
int FixException()
{
	y = 1;
	return EXCEPTION_CONTINUE_EXECUTION;//? MAY CAUSE INFINITE LOOP AS THIS IS A MACHINE INSTRUCTION
}

void DoWork()
{
	__try
	{
		int z = x / y;
		printf( "z = %d\n", z );
	}
	
	//! exception will continue execution in original exception generating place : Generally discouraged 
	__except(GetExceptionCode()==EXCEPTION_INT_DIVIDE_BY_ZERO
			  ? FixException(): EXCEPTION_CONTINUE_SEARCH)
	{

	}
}