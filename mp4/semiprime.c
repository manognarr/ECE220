#include <stdlib.h>
#include <stdio.h>


/*
Partners: smruthi2, manogna3
Intro Paragraph: In this program, the first error that we found was in the function 
is_prime, where the value being returned was incorrect. It should return 0, if number
does have a factor, thus the value is not prime. If number is prime, then it should return 1.
The second error that we found was that k was always zero and it should be instead the other 
factor that you need to multiply with j to get i. The third error that we found that
the code was checking multiple combinations of the same factors, so the semiprime value being printed
was being repeated. Instead, we added a break to break out of the loop to prevent the semiprime value 
from being repeated.

 * is_prime: determines whether the provided number is prime or not
 * Input    : a number
 * Return   : 0 if the number is not prime, else 1
 */
int is_prime(int number)
{
    int i;
    if (number == 1) {return 0;}
    for (i = 2; i < number; i++) { //for each number smaller than it
        if (number % i == 0) { //check if the remainder is 0
            return 0; //if not prime, then return 0
        }
    }
    
    return 1; //if prime, then return 1
}


/*
 * print_semiprimes: prints all semiprimes in [a,b] (including a, b).
 * Input   : a, b (a should be smaller than or equal to b)
 * Return  : 0 if there is no semiprime in [a,b], else 1
 */
int print_semiprimes(int a, int b)
{
    int i, j, k;
    int ret = 0;
    for (i = a; i <=b; i++) { //for each item in interval
        //check if semiprime
        for (j = 2; j <= i; j++) {
            if (i%j == 0) {
                if (is_prime(j)) {
                    k = i/j; //divide i and j to get the other factor and check if it is prime
                   if (is_prime(k)) {
                        printf("%d ", i);
                        break; //break out of loop if already found the prime factors
                    
                   }
                }
            }
        }

    }
    printf("\n");
    return ret;

}

