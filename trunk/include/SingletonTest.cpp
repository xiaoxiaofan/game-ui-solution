#include "singleton.hpp"
#include <iostream>
#include <memory>

//	Test for on the stack singleton
class A : public Dot::Singleton<A, Dot::NoCreation<A>, Dot::NoDestruction>  {
public : 
	inline virtual void Test() { std::cout << "A::Test" << std::endl; }
};	//	end of class A

inline void TestA() {
	A::Instance().Test();
}



//	Test for on the singleton created via new
class B {
public : 
	inline virtual void Test() { std::cout << "B::Test" << std::endl; }
};	//	end of class B
class C : public B {
public : 
	inline virtual void Test() { std::cout << "C::Test" << std::endl; }
};	//	end of class C

typedef Dot::Singleton<B> SingletonB;

inline void TestB() {
	SingletonB::Instance().Test();
}

void DestroyB(B* p) {
	delete p;
}



int main() {

	//	Test for on the stack singleton
	A a;
	TestA();
	
	//	Test for dynamic creation
	SingletonB::Instance().Test();

	//	allow polymorphism
	std::auto_ptr<C> c(new C);			//	keep here first in case Reset throws
	SingletonB::Reset(c.get(), DestroyB);
	//	safe to release c now, in fact must, since c also does its own cleanup
	c.release();
	SingletonB::Instance().Test();


	return 0;
}