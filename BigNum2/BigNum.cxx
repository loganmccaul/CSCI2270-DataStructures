
// FILENAME: BigNum.cxx
// This is the implementation file of the BigNum class
//Logan McCaul


#ifndef HW3_BIGNUM_CXX
#define HW3_BIGNUM_CXX
#include <algorithm>   // Provides copy function
#include <cstdlib>
#include <iostream>
#include <string>
#include <cstring>
#include <cassert>
#include "BigNum.h"
using namespace std;

namespace HW3
{
	BigNum::BigNum()
	{
		capacity = DEFAULT_CAPACITY;
		digits = new unsigned int[capacity]; 
		digits[0] = 0;
		positive = true;      
		used = 1;
	}    

	BigNum::BigNum(int num)
	{
		digits = nullptr;

		if (num == 0) 
		{
			BigNum zero;
			*this = zero;
		}
    
		else 
		{
			if (num > 0) 
			{
				positive = true;
			}
			else 
			{
				positive = false;
				num = -num;
			}
      
			unsigned int i = 0, temp = num;
      
			// count the digits
			while (temp > 0) 
			{
				temp = temp/10; 
				i++;
			}

			capacity = i; 
		
			digits = new unsigned int[capacity];

			temp = num;
		
			for (used = 0; used < i; ++used) 
			{
				digits[used] = temp % 10;
				temp /= 10;
			}
		}
	}

	// Constructor that receives a string; leading 0's will be ignored
	BigNum::BigNum(const string& strin)
	{
		digits = nullptr;
		
		int len = strin.length();
		
		if (len == 0)
		{
			BigNum zero;
			*this = zero;
			return;
		}

		used = len;
		positive = true;
		
		int i = 0;

		if(strin[i] == '-')  
		{
			positive = false;
			i = 1;
			used--;
		}
		else if(strin[i] == '+')  
		{
			i = 1;
			used--;
		}
		
		capacity = used;
	
		digits = new unsigned int[capacity];

		for(unsigned int k = 0; k < used; ++k) 
		{
			digits[used - k - 1] = strin[i++] - '0';
		}
		
		if (used == 1 && digits[0] == 0)
			positive = true;
			
		trim();
	}
 
    BigNum::BigNum(const BigNum& anotherBigNum)
    {
		digits = nullptr;
		
		// makes operator = do the work; use that function if you use this
		*this = anotherBigNum;
    }

    BigNum::~BigNum()
    {
		delete [] digits;
    }
        
    // assume doubling is done before passing in n
	void BigNum::resize(unsigned int n)
	{
		unsigned int *largerArray;

		if (n < used) return; // Can't allocate less than we are using

		capacity = n;
		largerArray = new unsigned int[capacity];
		
		copy(digits, digits + used, largerArray);
		
		delete [] digits;
		digits = largerArray;
	}

	BigNum& BigNum::operator=(const BigNum& anotherBigNum)
	{
		if (this == &anotherBigNum)  return *this;
		
		if (digits != nullptr)
			delete [] digits;
			
		capacity = anotherBigNum.capacity;
		digits = new unsigned int[capacity];
		
		positive = anotherBigNum.positive;
		used = anotherBigNum.used;
		copy(anotherBigNum.digits, anotherBigNum.digits + used, digits);
  
		return *this;
	}

  //calls the plus operator
	BigNum& BigNum::operator+=(const BigNum& addend)  
	{
		*this = *this + addend;
		return *this;
	}
//calls the - operator
	BigNum& BigNum::operator-=(const BigNum& subtractand)
	{
		*this = *this - subtractand;
		return *this;
	}
//calls the * operator
	BigNum& BigNum::operator*=(const BigNum& multiplicand)
	{
		*this = *this * multiplicand;
		cout << *this << endl;
		return *this;
	}
//calls the division operator for bignum
	BigNum& BigNum::operator/=(const BigNum& divisor)
	{
		*this = *this / divisor;
		return *this;
	}
//calls the remainder operator for bignum
	BigNum& BigNum::operator%=(const BigNum& divisor)
	{
		*this = *this % divisor;
		return *this;
	}

//adds 1 to bignum
	BigNum& BigNum::operator++()
	{
		BigNum temp = 1;
		*this += temp;
		return *this;
	}
//subtracts one from a bignum
	BigNum& BigNum::operator--()
	{
		BigNum temp = 1;
		*this -= temp;
		return *this;
	}

//subtract each variable of the smaller bignum from the larger while carrying over the remainder.
//pull down the remaining variables from the larger with the carrier added.
	BigNum& BigNum::diff(const BigNum& a, const BigNum& b)
	{
		resize(a.used);
		used = 0;
		unsigned int diff = 0;
		unsigned int carrier = 0;
		
		for(unsigned int i = 0; i < a.used; i++){
			if(i < b.used){
				if(a.digits[i] >= b.digits[i] + carrier){
					diff = a.digits[i] - carrier - b.digits[i];
					carrier = 0;
				}
				else{
					diff = a.digits[i] - carrier + 10 - b.digits[i];
					carrier = 1;
				}
		}else{
			if(a.digits[i] >= carrier){
				diff = a.digits[i] - carrier;
				carrier = 0;
			}
			else{
				diff = a.digits[i] + 10 - carrier;
				carrier = 1;
		}
		}
	used++;
	digits[i] = diff % 10;
	}
			trim();
			return *this;
  }

//Iterates through each bignum when they aren't aligned adding 0
//then when they are alligned multiplies the two values together and iterates used by the size of the number of 0's plus the step you are in within digits
//if the carrier still has a value it then adds it on the end of digits and iterates digits
//passes product into a new bignum
	BigNum& BigNum::mult(const BigNum& a, const BigNum& b)
	{
		resize(a.used + b.used);
		unsigned int prod = 0;
		unsigned int carrier = 0;
		unsigned int j,k;
		for(unsigned int i = 0; i < a.used; i++){
			BigNum product;
			if (a.digits[i] > 0){
				product.resize(a.used + b.used);
				product.used = 0;
				for(j = 0; j < i; j++){
					product.digits[j] = 0;
				}
				carrier = 0;
				for(k = 0; k < b.used; k++){
					prod = a.digits[i] * b.digits[k];
					prod += carrier;
					product.digits[j+k] = prod % 10;
					product.used = j+k+1;
					carrier = prod / 10;
				}
				while(carrier > 0){
					product.digits[j+k] = carrier % 10;
					product.used++;
					carrier = carrier / 10;
					++j;
				}
				product.trim();
			}
			*this += product;
		}
		trim();
		return *this;
	}
	
	BigNum& BigNum::sum(const BigNum& a, const BigNum& b) 
	{
		resize(a.used + 1);
		used = 0;
		unsigned int carrier = 0;
		unsigned int sum = 0;
		
		for(unsigned int i = 0; i < a.used; i++){
			sum = a.digits[i];
			if(i < b.used)
				sum += b.digits[i];
			sum += carrier;
			digits[i] = sum %10;
			carrier = sum/10;
			used++;
		}
		if (carrier > 0){
			digits[used] = carrier;
			used++;
			}
		return *this;
	}

//Check to see if either is 0, and if not call sum or diff depending on the size of the abs value and positive to negative relations
	BigNum operator+(const BigNum& a, const BigNum& b)
	{
		BigNum result = 0;
		BigNum number1 = a;
		BigNum number2 = b;
		number1.positive = true;
		number2.positive = true;
		
		if (number1 == 0)
			return b;
		if (number2 == 0)
			return a;
		
		if(a.positive == b.positive){
			result.positive = a.positive;
			if(number1 > number2)
				result.sum(number1, number2);
			else
				result.sum(number2, number1);
		}
		else{
			if(number1 > number2){
				result.diff(number1, number2);
				result.positive = a.positive;
			}
			else if(number1 == number2){
				return result;
			}
			else{
				result.diff(number2, number1);
				result.positive = b.positive;
			}
		}
		return result;
	}

//almost the exact opposite of +
	BigNum operator-(const BigNum& a, const BigNum& b)
	{
		BigNum result = 0;
		BigNum number1 = a;
		BigNum number2 = b;
		number1.positive = true;
		number2.positive = true;

		if(a.positive != b.positive){
			if(number1 > number2)
				result.sum(number1, number2);
			else if(number2 >= number1)
				result.sum(number2,number1);
			result.positive = a.positive;
		}
		else{
			if(number1 > number2){
				result.diff(number1, number2);
				result.positive = a.positive;
			}
			else{
				result.diff(number2, number1);
				result.positive = !a.positive;
			}
		}
		BigNum temp = 0;
		temp.positive = false;
		if(result == temp){
			result.positive = true;
		}
		return result;
	}
      
//check to see if either number is 1 or 2 to do the simple multiplcation, if not call the mult function and check to see if positive or negative
	BigNum operator*(const BigNum& a, const BigNum& b)
	{
		BigNum result = 0;
		BigNum uno = 1;
		if(a == result || b == result)
			return result;
		else if(a == uno)
			return b;
		else if(b == uno)
			return a;
		else{
			result.mult(a,b);
			if(a.positive == b.positive)
				result.positive = true;
			else
				result.positive = false;
		}
		return result;
	}

//Calls the multiply function with an iterator until the number is greater than what your dividing by
//If the number is greater tha  remove the last iteration to find how many times it divides into
	BigNum operator / (const BigNum& a, const BigNum& b)
	{
		BigNum result = 1;
		result.resize(a.used);
		
		if (a.positive == b.positive && a.positive == true){
			for(result = 1; result * b < a; ++result){}
			if(result * b > a)
				--result;
		}
		if (a.positive == b.positive && b.positive == false){
			for(result = 1; result * a > b; ++result){}
			if(result * b < a)
				--result;
		}
		else if(a.positive != b.positive && a.positive == true){
			for(result = 1; result* b < a; --result){}
			if(result * b > a)
				++result;
			result.positive = false;
		}
		else if(a.positive != b.positive && a.positive == false){
			for(result = 1; result * b > a; --result){}
			if(result * b > a)
				++result;
			result.positive = false;
		}
		return result;
	}

	//Calls the division operator, the -= operator, and * operator to get the remaining value.
	BigNum operator%(const BigNum& a, const BigNum& b)
	{
		BigNum result = a;
		result -= (a/b * b);
		return result;
	}

	bool operator>(const BigNum& a, const BigNum& b)
	{
		if (a.positive == true && b.positive == false) return true;
		
		else if (a.positive == false && b.positive == true) return false;
		
		else 
		{
			if (a.used > b.used) 
			{
				if (a.positive == true) return true;
				else return false;
			}
			
			else if (a.used < b.used) 
			{
				if (a.positive == true) return false;
				else return true;
			}
	
			else 
			{
				for (unsigned int i = 0; i < a.used; ++i) 
				{
					if (a.digits[a.used - 1 - i] < b.digits[b.used - 1 - i])  
					{
						if(a.positive == true) return false;
						else return true;
					}
					if (a.digits[a.used - 1 - i] > b.digits[b.used - 1 - i])  
					{
						if(a.positive == true) return true;
						else return false;
					}
				}
			}          
		}
		return false;
	}


	bool operator>=(const BigNum& a, const BigNum& b)
	{
		return ((a > b) || (a == b));
	}


	bool operator<(const BigNum& a, const BigNum& b)
	{
		return !(a >= b);
	}


	bool operator<=(const BigNum& a, const BigNum& b)
	{
		return !(a > b);
	}


	bool operator==(const BigNum& a, const BigNum& b)
	{
		if ((a.positive != b.positive) || (a.used != b.used))
			return false;

		for (unsigned int i = 0; i < a.used; i++) 
		{
			if (a.digits[a.used - 1 - i] != b.digits[b.used - 1 - i]) 
				return false;
		}

		return true;
	}


	bool operator!=(const BigNum& a, const BigNum& b)
	{
		return !(a == b);
	}

	// trim leading zeros
	void BigNum::trim()
	{
		while (used > 1 && digits[used-1] == 0)
			used--;
	}
	
	std::ostream& operator<<(std::ostream &os, const BigNum& bignum)
	{
		unsigned int i = 0;
		unsigned int j = 0;

		if (bignum.positive == false)  os << '-';

		for (i=0; i<bignum.used; ++i) 
		{
			os << bignum.digits[bignum.used - i - 1];
			if (j < 60) ++j; 
			else 
			{
				os << endl;
				j = 0;
			}
		}
    
		return os;
	}	 

	std::istream& operator>>(std::istream &is, BigNum& bignum)
	{
		string str;
		is >> str;

		BigNum temp = str;
		bignum = temp;
		return is;
	}
	
	BigNum factorial(const BigNum& a)
	{
		BigNum result;
		return result;
    }
  }


#endif



