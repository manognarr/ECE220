#include "ImaginaryNumber.h"
#include "helper.h"

ImaginaryNumber::ImaginaryNumber()
{
   number_type=IMAGINARY;
   imaginary_component=0.0;
   magnitude=0.0;
   phase=0.0;
}

ImaginaryNumber::ImaginaryNumber(double rval)
{
    number_type=IMAGINARY;
    imaginary_component=rval;
    magnitude=(rval>=0)? rval: -rval;
    phase=calculate_phase(0.0, rval);
}

ImaginaryNumber::ImaginaryNumber( const ImaginaryNumber& other )
{
    number_type=IMAGINARY;
    imaginary_component=other.imaginary_component;
    magnitude=(imaginary_component>=0)? imaginary_component: -imaginary_component;
    phase=calculate_phase(0.0, imaginary_component);
}

void ImaginaryNumber::set_imaginary_component (double rval)
{
    imaginary_component=rval;
}

double ImaginaryNumber::get_imaginary_component() const
{
    /* Your code here */
    return imaginary_component;
}

//Getter function for magnitude
double ImaginaryNumber::get_magnitude() const{
    /* Your code here */
    return magnitude;
}

//Getter function for phase
double ImaginaryNumber::get_phase() const{
    /* Your code here */
    return phase;
}

//Operator Overload
ImaginaryNumber ImaginaryNumber::operator + (const ImaginaryNumber& arg)
{
    /* Your code here */
    return ImaginaryNumber(imaginary_component+arg.imaginary_component);
    
}

ImaginaryNumber ImaginaryNumber::operator - (const ImaginaryNumber& arg)
{
    /* Your code here */
    return ImaginaryNumber(imaginary_component-arg.imaginary_component);
}

RealNumber ImaginaryNumber::operator * (const ImaginaryNumber& arg)
{
    /* Your code here */
    return RealNumber((-1)*imaginary_component*arg.imaginary_component);
}

RealNumber ImaginaryNumber::operator / (const ImaginaryNumber& arg)
{
    /* Your code here */
    return RealNumber(imaginary_component/arg.imaginary_component);
}

ComplexNumber ImaginaryNumber::operator + (const RealNumber& arg)
{
    /* Your code here */
    return ComplexNumber(arg.get_real_component(), imaginary_component);
}

ComplexNumber ImaginaryNumber::operator - (const RealNumber& arg)
{
    /* Your code here */
    return ComplexNumber((-1)*arg.get_real_component(), imaginary_component);
}

ImaginaryNumber ImaginaryNumber::operator * (const RealNumber& arg)
{
    /* Your code here */
    return ImaginaryNumber(imaginary_component*arg.get_real_component());
}

ImaginaryNumber ImaginaryNumber::operator / (const RealNumber& arg)
{
    /* Your code here */
   return ImaginaryNumber(imaginary_component/arg.get_real_component());
}


ComplexNumber ImaginaryNumber::operator + (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(arg.get_real_component(), imaginary_component+arg.get_imaginary_component());
}

ComplexNumber ImaginaryNumber::operator - (const ComplexNumber& arg)
{
    /* Your code here */
       return ComplexNumber((-1)*arg.get_real_component(), imaginary_component-arg.get_imaginary_component());

}

ComplexNumber ImaginaryNumber::operator * (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber((-1)*imaginary_component*arg.get_imaginary_component(), imaginary_component*arg.get_real_component());
}

ComplexNumber ImaginaryNumber::operator / (const ComplexNumber& arg)
{
    /* Your code here */
    return ComplexNumber(
    (imaginary_component*arg.get_imaginary_component())/(arg.get_real_component()*arg.get_real_component()+
    (arg.get_imaginary_component()*arg.get_imaginary_component())), (imaginary_component*arg.get_real_component())/
    (arg.get_real_component()*arg.get_real_component()+
    (arg.get_imaginary_component()*arg.get_imaginary_component())));
}

string ImaginaryNumber::to_String(){
    /* Do not modify */
    stringstream my_output;
    my_output << std::setprecision(3) << imaginary_component << 'i';
    return my_output.str();
}

