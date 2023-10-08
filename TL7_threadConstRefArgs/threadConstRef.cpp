#include<iostream>
#include<vector>
#include<thread>

//! NOTE:  take input from vector as const refererence; place the result in *res
void f( const std::vector<double>& v, double* result )
{

}

class F
{
private:
	double* m_result {};
	const std::vector<double>& m_v;

public:
	F( const std::vector<double>& vv, double* ptr )
		:m_v { vv }, m_result { ptr }
	{

	}

	void operator()()
	{

	}

};

//? use return value a global for now
double g( const std::vector<double>& retVec )
{
	return retVec.at( 0 );
}

void user( std::vector<double>& vec1,
		   std::vector<double> vec2,
		   std::vector<double> vec3 )
{
	double res1 {};
	double res2 {};
	double res3 {};

	// f(vec1, &res1) execotes in a separate thread
	std::thread t1 { f,cref( vec1 ),&res1 };

	//F{vec2,&res2}() executes in a separate thread
	std::thread t2 { F{vec2,&res2} };

	//capture local variables by reference using lambda
	// captures res3 and vec3 by reference capture variable
	std::thread t3 { [&]()
    {
     res3 = g( vec3 ); //? is g a function or callback
    } };

	// join before using the results

	t1.join();
	t2.join();
	t3.join();

	std::cout << res1 << ' ' << res2 << ' ' << res3 << '\n';

}

int main()
{
	std::vector<double> v1 { 1.1,2.2,3.3 };
	std::vector<double> v2 { 4.4,5.5,6.6 };
	std::vector<double> v3 { 7.7,8.8,9.9 };

	// check the output of user function having multithreaded thread task
	user(v1,v2,v3);

	return 0;

}