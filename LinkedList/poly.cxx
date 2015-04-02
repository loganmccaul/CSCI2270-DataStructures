//Logan McCaul Part 1
//polynode* head_ptr - The first node in the list. Has 0 as the coefficient and exponent
//polynode* tail_ptr - Always points to the last node in the list
//mutable polynode* recent_ptr - Changeable node that keeps track of the last pointer accessed
//unsigned int current_degree - Highest exponent in the list
#include "poly.h"
using namespace std;

namespace main_savitch_5
{
	//Constructor
	polynomial::polynomial(double c, unsigned int exponent)
	{
		EPSILON = std::numeric_limits<double>::epsilon();
		head_ptr = new polynode(c, 0);
		if (exponent == 0 || fabs(c) < EPSILON)
		{
			recent_ptr = head_ptr;
			tail_ptr = head_ptr;
			current_degree = 0;
		}
		else
		{
			head_ptr->set_coef(0);
			polynode* p = new polynode(c, exponent, nullptr, head_ptr);
			head_ptr->set_fore(p);
			tail_ptr = p;
			recent_ptr = p;
			current_degree = exponent;
		}
    }
	//Assignment operator
    polynomial& polynomial::operator=(const polynomial& source)
    {
		EPSILON = std::numeric_limits<double>::epsilon();
		if (this == &source)
			return *this;
		if (head_ptr != nullptr)
		{	
			clear();
			delete head_ptr;
		}
		tail_ptr = nullptr;
		head_ptr = nullptr;
		recent_ptr = nullptr;
	
		if (source.head_ptr != nullptr)
		{
			head_ptr = new polynode(source.head_ptr->coef(), source.head_ptr->exponent());
			tail_ptr = head_ptr;
			recent_ptr = head_ptr;
			current_degree = 0;
	
			for (unsigned int expo = source.next_term(0); expo != 0; expo = source.next_term(expo))
				assign_coef(source.coefficient(expo), expo);
		}
		return *this;
    }
	
	//copy constructor
    polynomial::polynomial(const polynomial& source)
    {
		EPSILON = std::numeric_limits<double>::epsilon();
		head_ptr = nullptr;
		*this = source;
    }
//Deletes the polynodes and calls clear to remove each node
    polynomial::~polynomial()
    {
		clear();
		delete head_ptr;
		head_ptr = nullptr;
		tail_ptr = nullptr;
		recent_ptr = nullptr;
		current_degree = 0;
    }

//Steps trhough each node in the list and removes it's values
    void polynomial::clear()
    {
		polynode* curr_node = head_ptr;
		while (head_ptr->fore() != nullptr)
		{
			curr_node = head_ptr->fore();
			delete head_ptr;
			head_ptr = curr_node;
		}
		head_ptr->set_coef(0);
		head_ptr->set_exponent(0);
		current_degree = 0;
		tail_ptr = head_ptr;
		recent_ptr = head_ptr;
    }
    
    //sets recent polynode
    double polynomial::coefficient(unsigned int exponent) const
    {
		set_recent(exponent);
		if (recent_ptr->exponent() == exponent)
			return recent_ptr->coef();
		return 0;
    }

//add on to the coefficient of a specific polynode
    void polynomial::add_to_coef(double amount, unsigned int exponent)
    {
			set_recent(exponent);
		if (fabs(amount) < EPSILON)
			return;
		else
		{
			if (recent_ptr->exponent() < exponent)
			{
				polynode* new_node = new polynode(amount, exponent, recent_ptr->fore(), recent_ptr);
				if (recent_ptr->fore() != nullptr)
					recent_ptr->fore()->set_back(new_node);
				else
					tail_ptr = new_node;
				recent_ptr->set_fore(new_node);
				if (exponent > current_degree && fabs(amount) >= EPSILON)
					current_degree = exponent;
			}
			else
			{
				if (exponent == 0)
					recent_ptr->set_coef(recent_ptr->coef() + amount);
				else
				{
					if (exponent == current_degree)
					{	
						if (fabs(amount + recent_ptr->coef()) < EPSILON)
						{
							tail_ptr = recent_ptr->back();
							delete recent_ptr;
							recent_ptr = tail_ptr;
							tail_ptr->set_fore(nullptr);
							current_degree = tail_ptr->exponent();
						}
						else
							recent_ptr->set_coef(recent_ptr->coef() + amount);
					}
					else
					{
						if (fabs(amount + recent_ptr->coef()) < EPSILON)
						{
							recent_ptr->back()->set_fore(recent_ptr->fore());
							recent_ptr->fore()->set_back(recent_ptr->back());
							delete recent_ptr;
							recent_ptr = recent_ptr->back();
						}
						else
							recent_ptr->set_coef(recent_ptr->coef() + amount);
					}
				}
			}
		}
	}

//change the coefficient of a specific polynode
    void polynomial::assign_coef(double coefficient, unsigned int exponent)
    {
		set_recent(exponent);
		if (fabs(coefficient) < EPSILON && exponent > current_degree)
			return;
		else
			if (recent_ptr->exponent() < exponent)
			{
				polynode* new_node = new polynode(coefficient, exponent, recent_ptr->fore(), recent_ptr);
				if (recent_ptr->fore() != nullptr)
				{
					recent_ptr->fore()->set_back(new_node);
				}
				else
				{
					tail_ptr = new_node;
				}
				recent_ptr->set_fore(new_node);
				if (exponent > current_degree)
					current_degree = exponent;
				recent_ptr = new_node;
			}
			else
				if (fabs(coefficient) > EPSILON || exponent == 0)
				{
					recent_ptr->set_coef(coefficient);
					if (exponent > current_degree)
						current_degree = exponent;
				}
				else
					if (exponent == current_degree)
					{
						tail_ptr = recent_ptr->back();
						delete recent_ptr;
						recent_ptr = tail_ptr;
						tail_ptr->set_fore(nullptr);
						current_degree = tail_ptr->exponent();
					}
					else
					{
						recent_ptr->back()->set_fore(recent_ptr->fore());
						recent_ptr->fore()->set_back(recent_ptr->back());
						polynode* to_delete = recent_ptr;
						recent_ptr = recent_ptr->back();
						delete to_delete;
					}
    }
//Points recent to the next term in the list
    unsigned int polynomial::next_term(unsigned int exponent) const
    {
		if (exponent >= current_degree) 
		{
			return 0;
		}
		set_recent(exponent);   
		if (recent_ptr->fore() == nullptr) 
		{
			return 0;
		}
		return recent_ptr->fore()->exponent();
    }

//points to the previous term in the list
	unsigned int polynomial::previous_term(unsigned int exponent) const
    {
		if (exponent <= 0) return UINT_MAX;
		set_recent(exponent - 1);
		if (recent_ptr == nullptr) return UINT_MAX;
		if (recent_ptr->exponent() == 0 && fabs(recent_ptr->coef()) < EPSILON)
			return UINT_MAX;
		else
		{
			return recent_ptr->exponent();
		}
		return UINT_MAX;
    }
    
    //set what the recent_ptr is looking at
    void polynomial::set_recent(unsigned int exponent) const
    {
		if (exponent == 0)
		{
			recent_ptr = head_ptr;
		}
		else if (exponent >= current_degree)
			{
				recent_ptr = tail_ptr;
			}
			else
				if (exponent < recent_ptr->exponent())
				{
					while (recent_ptr->back() != nullptr && recent_ptr->exponent() > exponent)
					recent_ptr = recent_ptr->back();
				}
				else
				{	
					while (recent_ptr->fore() != nullptr && recent_ptr->exponent() < exponent)
						recent_ptr = recent_ptr->fore();
					if (recent_ptr->exponent() > exponent)
						recent_ptr = recent_ptr->back();
				}
	}
    
    double polynomial::eval(double x) const
    {
		double total = 0;
		unsigned int exp = next_term(0);
		while (exp != 0){
			//adds the power of x to exp multiplied by the coefficiet to the total
				total += pow(x, exp) * coefficient(exp);
				//move to the next node
				exp = next_term(exp);
		}
		return total;
    }

    polynomial polynomial::derivative() const
    {
		polynomial p_prime;
		double coeff;
		unsigned int exp = 0;
		//set the coefficient to be the exponent multiplied by the coefficient
		coeff = exp * coefficient(exp);
		//assigns the coefficient to be to be coeff and the exponent 1 less
		p_prime.assign_coef(coeff, exp-1);
		//move to the next node
		exp = next_term(exp);
		//Do it for the rest
		while(exp !=0){
			coeff = exp * coefficient(exp);
			p_prime.assign_coef(coeff, exp-1);
			exp = next_term(exp);
		}
		return p_prime;
    }
    
    polynomial operator+(const polynomial& p1, const polynomial& p2)
    {
		polynomial p = p1;
		unsigned int exp = 0;
		//adds the coefficent of p2 to p
		p.add_to_coef(p2.coefficient(exp), exp);
		//moves to next polnode
		exp = p2.next_term(exp);
		//runs it for the rest after 00
		while(exp!=0){
			p.add_to_coef(p2.coefficient(exp), exp);
			exp = p2.next_term(exp);
		}
		
		return p;
    }
    
    polynomial operator-(const polynomial& p1, const polynomial& p2)
    {
		//Creates a new polynomial with the contents of p1
		polynomial p = p1;
		unsigned int exp = 0;
		//adds the negative of the coefficient to the first coefficent
		p.add_to_coef(-1*p2.coefficient(exp), exp);
		//moves to the next node
		exp = p2.next_term(exp);
		
		//do it for every node in the second polynomial
		while(exp != 0){
			p.add_to_coef(-1*p2.coefficient(exp), exp);
			exp = p2.next_term(exp);
		}
		return p;
    }
    
    polynomial operator*(const polynomial& p1, const polynomial& p2)
    {		
		polynomial p;
		unsigned int exp1 = 0;
		unsigned int exp2 = 0;
		//get the 0*0 exponent
		p.add_to_coef(p1.coefficient(exp1) * p2.coefficient(exp2), exp1 + exp2);
		//gets the 0 * the exponents of polynode 2
		for(exp2 = p2.next_term(exp2); exp2 != 0; exp2 = p2.next_term(exp2)){
			p.add_to_coef(p1.coefficient(exp1) * p2.coefficient(exp2), exp1 + exp2);
		}
		//Does the rest of the multiply outs functions
		for(exp1 = p1.next_term(0); exp1 != 0; exp1 = p1.next_term(exp1)){
			exp2 = 0;
			p.add_to_coef(p1.coefficient(exp1) * p2.coefficient(exp2), exp1 + exp2);
			exp2 = p2.next_term(exp2);
			while(exp2 != 0){
				p.add_to_coef(p1.coefficient(exp1) * p2.coefficient(exp2), exp1 + exp2);
				exp2 = p2.next_term(exp2);
			}
		}
		
		return p;
    }

    ostream& operator << (ostream& out, const polynomial& p)
    {
		unsigned int expo = 0;
		//Run through once
		//prints the coefficent and the exponent on the sides of a x
		out << p.coefficient(expo) << "*x^" << expo;
		//moves to next exponent
		expo = p.next_term(expo);
		//print next node
		if (expo != 0) out << " + ";
		
		//do the rest
		while(expo != 0){
			out << p.coefficient(expo) << "*x^" << expo;
			expo = p.next_term(expo);
			if (expo != 0) out << " + ";
		}
		return out;
    }
    
    void polynomial::find_root(
	double& answer,
	bool& success,
	unsigned int& iterations,
	double guess,
	unsigned int maximum_iterations,
	double epsilon) const
    {
	}
}
