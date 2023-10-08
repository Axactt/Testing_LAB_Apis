#include<thread>
#include<iostream>

//? A task is a function of function object
//! data race problem on concurent tasks accessing  same cout ostream object in a multithreaded application


void f()// function can be used as a task
{
	std::cout << "Hello Xatat.\n";
}
struct F      // function object
{
	void operator ()()// F's call operator
	{
		std::cout << "Parallel World.\n";

	}
};

void user()
{
	std::thread t1 { f }; //! f() executes in a separate thread an example of task

	std::thread t2 { F{} }; //! F{}() functor object executes in a separate thread an example of task

	t1.join();  // wait for t1
	t2.join();  // wait for t2 means to become signalled or terminate



}

void user1()
{
	// easier to forget to join so jthread
	// joining in reverse order of construtor as done by destructors
	std::jthread t1 { f }; // jthread is a RAII compliant joining thread having its destrutor join()

	std::jthread t2 { F{} };

}

int main()
{

	user1();
	return 0;

}