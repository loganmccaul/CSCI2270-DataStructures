#include "MyClass.cxx"


// Pass by value
void fun1(MyClass a)
{
	a.setX(1);
}


// Pass by reference
void fun2(MyClass& a)
{
	a.setX(2);
}



// Pass by pointer
void fun3(MyClass* a)
{
	a->setX(3);
}


// Using double pointers! Coz why stop at single pointers? :)
void fun4(MyClass** a)
{
	(*a)->setX(4);
}



int main() 
{
	MyClass a;
	MyClass* b;
	MyClass** c;
	
	cout << endl << "----Calling fun1----" << endl;
	
	fun1(a); 
	a.printX(); // Explaining output (1 point)	
	//Creates a new variable x with the passed in value of 1 in myClass.cxx
	//Then prints out the value of x for the object a which is still 0, because 
	//it was passed in by value and not reference.


	cout << endl << "----Calling fun2----" << endl;	
	
	fun2(a); 
	a.printX(); // Explaining output (1 point)
	//Passes in by reference the value 2 into myClass.setX then sets X 
	//to that value two. Then prints X which equals 2.


	
	cout << endl << "----Calling fun3----" << endl;
	
	b = &a;     // Fixing compile error (1 point)
	fun3(b);   
	a.printX(); // Explaining output (1 point)
	//Variable b points to the address of a
	//passes the value of a into fun3, since fun3 is takes in the value 
	//of a pointer
	//setX then changes x for object a to 3 then prints x.


	cout << endl << "----Calling fun4----" << endl;

	c = &b;    // Fixing compile error (1 point)
	fun4(c);    
	a.printX(); // Explaining output (1 point)
	//Sets the double pointer of c to point at the address of b which
	//is pointing at the value of a. then passes in c to fun4 which looks
	//for a double pointer, and passes in the the value of the pointer which
	//the double pointer is pointing at, essentially *b.
	//Then it sets the value of x for object a to 4 and prints it out
	
	//Dereferencing using single pointer
	cout << "\n\nTwo ways of dereferencing, \n1. Using '.' operator\n2. Using '->' operator\n\n";
	

	(*b).printX();          // Fixing compile error (1 point)
	(b)->printX();      // Fixing compile error (1 point) 
	
	//line 84 didn't compile because it was trying to print out x using an object, when b was a pointer. B needs to be dereferenced
	//line 85 didn't compile because it was looking for a pointer of a pointer, since it already took the address b was pointing at
	

	cout << "\n\n----Understanding arrays as pointers----" << endl;
	MyClass arr[5];
	
	arr[0].setX(10);
	arr[1].setX(20);
	arr[2].setX(30);
	arr[3].setX(40);
	arr[4].setX(50);
	
	cout << "----Running for loop for array variable 'arr' with 5 slots----" << endl << endl;
	
	//Explaining for loop (2 points)
	for (unsigned int i=0; i<5; i++)
	{
		cout << "i = " << i << endl;//Prints out iteration
		cout << "memory location (arr + i) = " << arr+i << endl;//prints the address of the current iteration
		cout << "  (*(arr + i)).printX() prints ";
		(*(arr+i)).printX();//dereferencing the value of the address that we are currently on
		cout << "        arr[i].printX() prints ";
		arr[i].printX();//prints out the value of the array at iteration i
		cout << endl;
	}
	
	
	
	return 0;


}

