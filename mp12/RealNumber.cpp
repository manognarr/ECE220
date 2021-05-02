#include "RealNumber.h"
#include "helper.h"

RealNumber::RealNumber()
{
    number_type=REAL;
    real_component=0.0;
   magnitude=0.0;
   phase=0.0;
}

RealNumber::RealNumber(double rval)
{
    number_type=REAL;
    real_component=rval;
    magnitude=(rval>=0)? rval: -rval;
    phase=calculate_phase(rval, 0.0);
}

RealNumber::RealNumber( const RealNumber& other )
{
    number_type=REAL;
    real_component=other.real_component;
    magnitude=(real_component>=0)? real_component: -real_component;
    phase=calculate_phase(real_component, 0.0);
}

void RealNumber::set_real_component (double rval)
{
   real_component = rval;
}

double RealNumber::get_real_component() const
{
    return real_component;
}

double RealNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

double RealNumber::get_phase() const{
    /* Your code here */
    return phase;
}

RealNumber RealNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
    return RealNumber(real_component+arg.real_component);
}

RealNumber RealNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
     return RealNumber(real_component-arg.real_component);;
}

RealNumber RealNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
        return RealNumber(real_component*arg.real_component);

}

RealNumber RealNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
       return RealNumber(real_component/arg.real_component);

}

ComplexNumber RealNumber::operator + (const ImaginaryNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component, arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator - (const ImaginaryNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component, arg.get_imaginary_component());
}

ImaginaryNumber RealNumber::operator * (const ImaginaryNumber& arg){
    /* Your code here */
	return ImaginaryNumber(real_component*arg.get_imaginary_component());
}

ImaginaryNumber RealNumber::operator / (const ImaginaryNumber& arg){
    /* Your code here */
	return ImaginaryNumber((-1)*real_component/arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator + (const ComplexNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component+arg.get_real_component(), arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator - (const ComplexNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component-arg.get_real_component(), arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator * (const ComplexNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component*arg.get_real_component(), real_component*arg.get_imaginary_component());
}

ComplexNumber RealNumber::operator / (const ComplexNumber& arg){
    /* Your code here */
	return ComplexNumber(real_component*arg.get_real_component()/(
        arg.get_real_component()*arg.get_real_component()+(arg.get_imaginary_component()*arg.get_imaginary_component())), 
        real_component*(arg.get_imaginary_component())/(arg.get_real_component()*arg.get_real_component()+(arg.get_imaginary_component()*arg.get_imaginary_component())));
    
}

string RealNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << real_component;
    return my_output.str();
}