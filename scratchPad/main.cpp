 #include<thread>
#include<iostream>
#include<vector>

// Passing arguments multithread tasks

// function: do something with v
void f( std::vector<double>& v ) // pass argument by non-const reference 
{
	for (auto& d : v)
	{
		std::cout << d << ' ';
	}

}

// function object: do something with v

struct F
{
	std::vector <double>& m_v; //! pass argument by non const rreference 

	//! // pass argument by non const rreference 
	//! Expect task to modify the value of data referred to
	F( std::vector<double>& vv ) // constructor::
		:m_v { vv }
	{

	}
	void operator()() // application operator
	{
		for (auto& d : m_v)
		{
			std::cout << d << ' ';
		}
	}
};

int main()
{
	std::vector<double> some_vec { 1,2,3,4,5,6,7,8,9 };
	std::vector<double> vec2 { 10,11,12,13,14,15 };

	//! Threads in a process share an address space they can communicate through shared objects
	//! Communication controlled by locks or other mechanisms to prevent data races whichh is uncontrollled concurrent access to variable


	//! This example again causes a data race as UBCONTROLLED CONCURREBT ACCESS to ostream object cout
	//f(some_vec) executes in a separate thread
	std::jthread t1 { f,ref( some_vec ) }; // std::ref a refernce wrapper to tell t1 thread varaidic template that argumnet vector is passed by reference

	// F(vec2)() executes in a separate thread
	std::jthread t2 { F{vec2} };

}