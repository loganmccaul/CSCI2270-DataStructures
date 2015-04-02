// FILENAME: BigNum.cxx
// This is the implementation file of the BigNum class
// Logan McCaul


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
		//Creates a new empty BigNum
		capacity = DEFAULT_CAPACITY;
		positive = true;
		used = 1;
		digits = new unsigned int[capacity];
		digits[0] = 0;
	}    

	BigNum::BigNum(int num)
	{
		//if int is 0 creats empty bignum
		if(num == 0){
			capacity = DEFAULT_CAPACITY;
			positive = true;
			used = 1;
			digits = new unsigned int[capacity];
			digits[0] = 0;
			return;
		}
		//if negative set positive
			if (num < 0){
				positive = false;
				num = -num;
			}else{
				positive = true;
			}
		//gets length of the integer
		int len = floor(log10(num))+1;
		capacity = len*2;
		used = 0;
		digits = new unsigned int[capacity];
		//adds int into a bignum
		for(int i = 0; i < len; i++){
			digits[i] = num%10;
			num = num / 10;
			used++;
		}
}

	// Constructor that receives a string; leading 0's will be ignored
	BigNum::BigNum(const string& strin)
	{
		//sets digits to blank
		digits = NULL;
		//length of string
		unsigned int len = strin.length();
		//if the string is empty or a 0 then blank bignum
		if((len == 0 || strin == "0")){
			capacity = DEFAULT_CAPACITY;
			positive = true;
			used = 1;
			digits = new unsigned int[capacity];
			digits[0] = 0;
			return;
		}
		//finds if positive or negative then sets positive
		if(strin[0] == '+'){
			positive = true;
			capacity = len;
			used = len-1;
			digits = new unsigned int[capacity];
			for(unsigned int k = 1; k < len; k++){
				digits[--used] = strin[k] - 48;
			}
			used = len-1;
		}
		else if(strin[0] == '-'){
			positive = false;
			capacity = len;
			used = len-1;
			digits = new unsigned int[capacity];
			for(unsigned int i = 1; i < len; i++){
				digits[--used] = strin[i] - 48;
			}
			used = len-1;
		}
		//if neither then positive
		else{
			positive = true;
			capacity = len;
			used = len;
			digits = new unsigned int[capacity];
			//adds chars into bignum and converts to ints
			for(unsigned int j = 0; j < len; j++){
				digits[--used] = strin[j] - 48;
			}
			used = len;
	}
	//removes leading zeroes
	trim();
		
}		
 
    BigNum::BigNum(const BigNum& anotherBigNum)
    {
		//copy constructor
		capacity = anotherBigNum.capacity;
		used = anotherBigNum.used;
		positive = anotherBigNum.positive;
		digits = new unsigned int[capacity];
		for(unsigned int i = 0; i < used; i++){
			digits[i] = anotherBigNum.digits[i];
		}
    }

    BigNum::~BigNum()
    {
		//deletes heap memory on close
		delete[] digits;
    }
    
    void BigNum::resize(unsigned int n)
	{
		//Make sure the bigNum is getting bigger and the resize is necessary
	if(n > capacity){
		//create temp bigNum to store in the process of transferring over
		unsigned int* tempBigNum = new unsigned int[n];
		
	for(unsigned int i=0; i < used; i++){
		tempBigNum[i] = digits[i];
	}
	//removes old num and renames tempBigNum
		delete[] digits;
		digits = tempBigNum;
		capacity = n;
	}
}
	BigNum& BigNum::operator=(const BigNum& anotherBigNum)
	{
		//copies over anotherbignum to bignum if they are set equal to eachother
		if(this != &anotherBigNum){
			delete[] digits;
			used = anotherBigNum.used;
			capacity = anotherBigNum.capacity;
			positive = anotherBigNum.positive;
			digits = new unsigned int[capacity];
			for(unsigned int i = 0; i < used; i++){
				digits[i] = anotherBigNum.digits[i];
			}
		}
		return *this;
	}

  
	BigNum& BigNum::operator+=(const BigNum& addend)  
	{

		return *this;
	}

	BigNum& BigNum::operator-=(const BigNum& subtractand)
	{
		return *this;
	}

	BigNum& BigNum::operator*=(const BigNum& multiplicand)
	{
		return *this;
	}

	BigNum& BigNum::operator/=(const BigNum& divisor)
	{
		return *this;
	}

	BigNum& BigNum::operator%=(const BigNum& divisor)
	{
		return *this;
	}

	BigNum& BigNum::operator++()
	{
		return *this;
	}

	BigNum& BigNum::operator--()
	{
		return *this;
	}

	BigNum& BigNum::diff(const BigNum& a, const BigNum& b)
	{
		return *this;
	}
  

	BigNum& BigNum::mult(const BigNum& a, const BigNum& b)
	{
		return *this;
	}
	
	BigNum& BigNum::sum(const BigNum& a, const BigNum& b) 
	{
		return *this;
	}

	BigNum operator+(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}

	BigNum operator-(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}
      
	BigNum operator*(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}

	BigNum operator / (const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}


	BigNum operator%(const BigNum& a, const BigNum& b)
	{
		BigNum result;
		return result;
	}

	bool operator>(const BigNum& a, const BigNum& b)
	{
		//find the largest depending on the positive of both bignums
		int count = 0;
		if (a.positive == true && b.positive == false)
			return true;
		else if(a.positive == false && b.positive == true)
			return false;
		//if both false find the largest by incrementing through both
		else if(a.positive == false && b. positive == false){
			if(a.used > b.used)
				return false;
			else if(b.used > a.used)
				return true;
			else{
			count = a.used - 1;
			while(a.digits[count] == b.digits[count]){
				count--;
			}
			if(a.digits[count] > b.digits[count])
				return false;
			else
				return true;
			}
		}
		//if both true find the largest by incrementing through both
		else if(a.positive == true && b. positive == true){
			if(a.used > b.used)
				return true;
			else if(b.used > a.used)
				return false;
			else{ 
			count = a.used - 1;
			while(a.digits[count] == b.digits[count]){
				count--;
			}
			if(a.digits[count] > b.digits[count])
				return true;
			else
				return false;
		}
	}
	return false;
}

	bool operator>=(const BigNum& a, const BigNum& b)
	{
		return((a > b) || (a == b));
	}

	bool operator<(const BigNum& a, const BigNum& b)
	{
			return (!(a>b));
	}


	bool operator<=(const BigNum& a, const BigNum& b)
	{
			return (!(a>b) || (a ==b));
	}


	bool operator==(const BigNum& a, const BigNum& b)
	{
		//runs a forloop to make sure that every value of to bignums are the same
		if(a.positive == true && b.positive == true){
			if(a.used == b.used){
				for(unsigned int i = 0; i < a.capacity; i++){
					if(a.digits[i] !=b.digits[i])
						return false;
				} 
				return true;
			}
		}
		return false;
	}


	bool operator!=(const BigNum& a, const BigNum& b)
	{
			return (!(a==b));
	}

	void BigNum::trim()
	{
		while(digits[used-1] == 0){
			used--;
		}
	}
	
	
	std::ostream& operator<<(std::ostream &os, const BigNum& bignum)
	{
		//prints out each part of a bignum by using a for loop
		if(bignum.positive == false)
			cout << "-";
		for(int i = bignum.used-1; i >= 0; i--){
			cout << bignum.digits[i];
		}
			cout << endl;
		return os;
	}	 

	std::istream& operator>>(std::istream &is, BigNum& bignum)
	{
		//passes the string inputted into a bignum
		string a;
		is >> a;
		BigNum temp = BigNum(a);
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



