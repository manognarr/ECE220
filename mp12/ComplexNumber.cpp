#include "ComplexNumber.h"
#include "helper.h"
#include <cmath>

ComplexNumber::ComplexNumber()
{
    number_type=COMPLEX;
    real_component=0.0;
    imaginary_component = 0.0;
   magnitude=0.0;
   phase=0.0;
}

ComplexNumber::ComplexNumber(double rval_real_component, double rval_imaginary_component)
{
    number_type=COMPLEX;
    real_component=rval_real_component;
    imaginary_component=rval_imaginary_component;
    magnitude=(rval_real_component*rval_real_component)+(rval_imaginary_component*rval_imaginary_component);
    magnitude = sqrt(magnitude);
    phase=calculate_phase(rval_real_component, rval_imaginary_component);
}

ComplexNumber::ComplexNumber( const ComplexNumber& other )
{
    number_type=COMPLEX;
    real_component=other.real_component;
    imaginary_component=other.imaginary_component;
    magnitude=(real_component*real_component)+(imaginary_component*imaginary_component);
    magnitude = sqrt(magnitude);
    phase=calculate_phase(real_component,imaginary_component);
}

void ComplexNumber::set_real_component (double rval)
{
    real_component = rval;
}

double ComplexNumber::get_real_component() const
{
    return real_component;
}

void ComplexNumber::set_imaginary_component (double rval)
{
    imaginary_component = rval;
}

double ComplexNumber::get_imaginary_component() const
{
    return imaginary_component;
}

double ComplexNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

double ComplexNumber::get_phase() const{
    /* Your code here */
    return phase;
}

ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component+arg.get_real_component(), imaginary_component+arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(real_component-arg.get_real_component(), imaginary_component-arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
    /* Your code here */

        return ComplexNumber(real_component*arg.get_real_component()+(-1)*(imaginary_component*arg.get_imaginary_component()),
         imaginary_component*arg.get_real_component()+real_component*arg.get_imaginary_component());

}

ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
    /* Your code here */
        return ComplexNumber();

}

ComplexNumber ComplexNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber(arg.get_real_component()+real_component, imaginary_component);
}

ComplexNumber ComplexNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber(-arg.get_real_component()+real_component, imaginary_component);
}

ComplexNumber ComplexNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
		return ComplexNumber(arg.get_real_component()*real_component, imaginary_component*arg.get_real_component());

}

ComplexNumber ComplexNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
	return ComplexNumber();
}

ComplexNumber ComplexNumber::operator + (const ImaginaryNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component, imaginary_component+arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator - (const ImaginaryNumber& arg)
{
    /* Your code here */
	return ComplexNumber(real_component, imaginary_component-arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator * (const ImaginaryNumber& arg)
{
    /* Your code here */
		return ComplexNumber((-1)*imaginary_component*arg.get_imaginary_component(), real_component*arg.get_imaginary_component());
}

ComplexNumber ComplexNumber::operator / (const ImaginaryNumber& arg)
{
    /* Your code here */
	return ComplexNumber();
}

string ComplexNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    if (imaginary_component > 0)
        my_output << std::setprecision(3) << real_component << " + " << imaginary_component << 'i';
    else if (imaginary_component < 0)
        my_output << std::setprecision(3) << real_component << " - " << abs(imaginary_component) << 'i';
    else
        my_output << std::setprecision(3) << real_component;
    
    return my_output.str();
}