#include<Windows.h>
#include<cstdio>
#include"exceptionHandle3.h"

//! Filter expression coneverted to filter function for more elaborate decision making

int main()
{
	printf( " press enter to continue and hit a breakpoint.\n" );
	getchar();
	DebugBreak();
	printf( "Result: %d\n", sample3( 1 ) );
	printf( "Result: %d\n", sample3( -6 ) );
	printf( "Result: %d\n", sample3( -1 ) );
	return 0;

}