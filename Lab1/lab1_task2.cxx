
#include <iostream>  // Provides cout, cin
#include <cstdlib>   // Provides EXIT_SUCCESS
using namespace std;

double underflow_double( );

float underflow_float( );

int main( )
{
    cout << underflow_float() << endl;
    cout << underflow_double() << endl;
    return EXIT_SUCCESS;
}

double underflow_double( )
{
	double temp;
	double eps2 = 1;
    double n1 = 1;
    while (eps2 > 0){
		temp = eps2;
		eps2 = eps2/2;
	}
	cout << temp << endl;
	return n1;	// more is needed here
}

float underflow_float( )
{
	float temp;
    float n1 = 1;
    float eps1 = 1;
    while (eps1 > 0){
		temp = eps1;
		eps1 = eps1/2;
	}
	cout << temp << endl;
	return n1;	// more is needed here
}

