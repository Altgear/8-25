#include <cstdlib>
#include <iostream>
#include <sstream>
using namespace std;

class complex_t
{
public:
    
    static unsigned int count ;
    complex_t(){
        real = 0.0f;// обозначен. типа float
        imag = 0.0f;
        ++count;
    }
    complex_t add( complex_t other) const// comple_t const * const
    {
        complex_t result;
        result.imag = this->imag + other.imag;
        result.real = this->real + other.real;
        return result;
    }
    complex_t sub( complex_t other) const
{
	complex_t result;
        result.imag = this->real - other.real;
	result.real = this->imag - other.imag;
        return result;
}
    complex_t mult( complex_t other) const
{
	complex_t result;
	result.real = this->real *other.real - this->imag*other.imag;
	result.imag = this->imag *other.real + this->real*other.imag;
	return result;
}
    complex_t div( complex_t &other) const
{
	complex_t result;
	result.real = (this->real *other.real + this->imag*other.imag) 
                / (other.real * other.real + other.imag * other.imag);
	result.imag = (this->imag *other.real - this->real*other.imag) 
                / (other.real * other.real + other.imag * other.imag);
	return  result;
}

    std::ostream & write( std::ostream & stream ) const// complex_t const 
    {
        return stream << '(' << real << ", " << imag << ')';
    }
    std::istream & read( std::istream & stream ) //     const
    {
        char symbol;
        float real;
        float imag;

        if ( stream >> symbol && symbol == '(' &&
            stream >> real &&
            stream >> symbol && symbol == ',' &&
            stream >> imag &&
            stream >> symbol && symbol == ')')
        {

            this->real = real;
            this->imag = imag;

        } else
        {
            stream.setstate(std::ios::failbit);
        }

        return stream;
    }
    
    
    
    ~complex_t(){
        
    }
    void set_real(float value){
        if( value > 0.0f){
            real = value;
        }
    }
    void set_image(float value){
        if( value > 0.0f){
            imag = value;
        }
    }
private:
    float real;
    float imag;
};

unsigned int complex_t::count=0;

 int main()
{
	string input;
	getline(cin, input);
	istringstream stream(input);
        complex_t complex1;
        complex_t complex2;	
	char op;
        
	if( complex1.read( stream ) && 
	    stream >> op && (op == '+' || op == '-' || op == '*' || op == '/') &&
	    complex2.read( stream )) 
	{
		switch (op)
		{
			case '+': {
				auto result = complex1.add( complex2);  
				result.write(cout); 
				break; 
			}
			case '-': {
				auto result = complex1.sub( complex2);  
				result.write(cout); 
				break; 
			}
			case '*': {
				auto result = complex1.mult( complex2);  
				result.write(cout); 
				break; 
			}
			case '/': {
				auto result = complex1.div(complex2); 
				result.write(cout);  
				break; 
			}
		}
	}
	else
	{
		cout << "An error has occured while reading input data";
		return 1;
	}

	
	return 0;
}