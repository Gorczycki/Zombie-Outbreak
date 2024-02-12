#include <iostream>
#include <boost/numeric/odeint.hpp>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;
using namespace boost::numeric::odeint;

typedef double StateType;

void rhs (const StateType &s, const StateType &i, const StateType &d, StateType &dsdt, StateType &didt, StateType &dddt, const double t)
{
    // x = e^rt
    double x = exp(1.64*t);
    double alpha = 0.3;
    double mu = 0.7;
    double epsilon = 0.2;
    double delta = exp(0.009*t);

    dsdt = x * s - (alpha*s) + (s*i*(mu - alpha));
    didt = (s*i)*(alpha - mu - epsilon);
    dddt = (delta*s) + (epsilon*s*i);

    // x = birth rate
    //alpha*S*I zombies bite humans
    //delta*S Humans dying
    //mu*S*I Cured Zombies
    //Epsilon*S*I humans killing zombies
    //s is susceptible

    //partial(S)/partial(T) = X*S - alpha*s + S*I(mu - alpha)
    //partial(I)/partial(T) = S*I(alpha - mu - epsilon)
    //partial(D)/partial(T) = delta*S + epsilon*S*I

}

void write_cout(const double &s, const double &i, const double &d, const double t)
{
    cout<<s<<", "<<t<<endl;
    cout<<i<<", "<<t<<endl;
    cout<<d<<", "<<t<<endl;
    cout<<endl;
}

typedef runge_kutta_dopri5<StateType> stepper_type;

int main()
{
    StateType s = 0.0;
    StateType i = 0.0;
    StateType d = 0.0;
    integrate_adaptive(make_controlled( 1E-12 , 1E-12 , stepper_type() ) , rhs , s , 1.0 , 10.0 , 0.1 , write_cout);
    integrate_adaptive(make_controlled( 1E-12 , 1E-12 , stepper_type() ) , rhs , i , 1.0 , 10.0 , 0.1 , write_cout);
    integrate_adaptive(make_controlled( 1E-12 , 1E-12 , stepper_type() ) , rhs , d , 1.0 , 10.0 , 0.1 , write_cout);


    return 0;
}