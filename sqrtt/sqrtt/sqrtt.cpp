#include <iostream>

// FINDING THE SQUAREROOT OF A NUMBER v1.1
// Approximations gets increasingly worse as number gets higher (Notably n @ 6-digits)
// Computation time becomes much longer as number gets higher (Notably n @ 6-digits)
// This works ONLY for positive integer numbers.

using std::cin;
using std::cout;
using std::endl;

//power
long double power(long double BASE, long double pow)
{
	/******************************************************************
	*This function computes:                                          *
	*																  *
	*                       pow                                       *
	*power(BASE,pow) =  BASE      or BASE^(pow)                       *
	*																  *
	*NOTES:                                                           *
	*1- This is essentially BASE multiplied by istelf "pow" times     *
	*	For example, 2^4 is exactly 2 * 2 * 2 * 2 * 1                 *
	*	i.e. 2 multiplied by itself "4" times                         *
	*2- The base case is when pow == 0 (implied)                      *
	*******************************************************************/

	if (pow > 0)
	{
		return ((BASE)* power(BASE, pow - 1));
	}
	else if (pow < 0)
	{
		return ((power(BASE, pow + 1) / BASE));
	}
	else
	{
		return (1);
	}
}

//fracfacto
long double fracfacto(long double n, long double iter)
{
	/**************************************************************************
	*This function computes:                                                  *
	*                                                                         *
	*Let:  r = iter                                                           *
	*                                                                         *
	*fracfacto(n,r) =  (n-(r-1)) * (n-(r-2)) * (n-(r-3)) * ...                *
	*					  ... until r = 0                                     *
	*																		  *
	*NOTES:																	  *
	*1- This is the computation of the facotiral of n if n is a +ve fraction  *
	*2- This is done r number of times                                        *
	***************************************************************************/

	if (n > 0)
	{
		if (iter > 0)
		{
			return((n - (iter - 1))*fracfacto(n, (iter - 1)));
		}
		else if (iter == 0)
		{
			return(1);
		}
	}

	else
	{
		cout << "ERROR: fracfacto(" << n << ", " << iter << ")" << endl;
		return(0);
	}
}

//factorial
long double factorial(long double n)
{
	/****************************************************************************
	*This function computes:                                                    *
	*                                                                           *
	*factorial(n) =  n * (n-1) * (n-2) * (n-3) * ... * (n-r) * ... * 3 * 2 * 1  *
	*                                                                           *
	*NOTES:                                                                     *
	*1- Exactly the same as n!                                                  *
	*****************************************************************************/

	if (n > 0)
	{
		return (n*factorial(n - 1));
	}
	else if (n < 0)
	{
		cout << "ERROR: factorial(" << n << ")" << endl;
		cout << "Cannt find " << n << "!" << endl;
		return(0);
	}
	else //i.e. 0! = 1
	{
		return (1);
	}
}

//nCr
long double nCr(long double n, long double r)
{
	/************************************************************************************************************
	*This function computes:                                                                                    *
	*1- nCr - The number of ways you can choose r-ojects from a total of n-objects, reguardless of order        *
	*																										    *
	*Recall:																								    *
	*nCr =       n!																							    *
	*	     ----------     , for all long double r <= n and long double n >= 0								    *
	*         r!(n-r)!																						    *
	*																										    *
	*Hence:																										*
	*nCr(n,r) =             factorial(n)																		*
	*		      ---------------------------------     , for all long double r <= n and long double n > 0		*
	*			   factorial(r) * factorial(n-r)																*
	*NOTES:																										*
	*1- The above is for when n is a positive whole number larger than 0										*
	*2- This is done r-number of times																			*
	*3- There exists another case within the binomial expansion theorem where the following is necessary.       *
	*																											*
	*For the Binomial expansion of a power, long double pow, and 0 < pow < 1:									*
	*The Combination coefficient becomes:																		*
	*																											*
	*nCr -->   (pow - (r-1))!																					*
	*         ----------------       , for all long double r <= n and long double 0 < pow < 1					*
	*                r!																							*
	*																											*
	*Hence: (where n --> pow)																					*
	*nCr(n,r) =      fracfactorial(n)																			*
	*		      -----------------------    , for all long double r <= n and long double 0 < n < 1				*
	*			       factorial(r)																				*
	*NOTES:																										*
	*1- According to this particular case of the Binomial expansion, 0 < n < 1									*
	*2- This is done r-number of times																			*
	*************************************************************************************************************/

	long double nCrr;

	if (n >= 1)
	{
		nCrr = ((factorial(n)) / ((factorial(r))*(factorial(n - r))));
	}
	else if ((n > 0) && (n < 1))
	{
		nCrr = ((fracfacto(n, r)) / (factorial(r)));
	}
	else
	{
		cout << "ERROR: nCr(" << n << ", " << r << ")" << endl;
	}

	return (nCrr);
}

//coeff
long double coeff(long double n)
{
	/******************************************************************
	*This function computes:                                          *
	*                                                                 *
	*coeff(n) =    n(n-2)(n-4)(n-6)...(n-r)       , for all even r    *
	*	        --------------------------------                      *
	*             (n-1)(n-3)(n-5)...(n-(r-1))     , for all odd r     *
	*NOTES:                                                           *
	*1- r = n - 1                                                     *
	*2- The numerator uses only 0 and even values of r                *
	*3- The denominator uses only odd values of r                     *
	*4- The loop increments towards r                                 *
	*******************************************************************/

	long double ans = 1;
	int i = 0;
	while (i <= (n - 1))
	{
		if (i % 2 == 0)
		{
			ans = ans * (n - i);
		}

		else if (i % 2 == 1)
		{
			ans = (ans / (n - i));
		}
		i++;
	}
	return ans;
}

//binomial expansion (summation) - summation of (1-(1/n))^pow, 'iter' times
long double binexp(long double n, long double pow, long double iter)
{
	if (n > 1)
	{
		long double sumterms = 0;

		for (long double pow1 = pow; pow1 <= (iter + pow); pow1++)
		{
			sumterms = sumterms + ((nCr(pow, (pow1 - pow)))*(power((-(1 / n)), (pow1 - pow))));
		}

		return (sumterms);
	}
	else
	{
		return (1);
	}
}

//intermediate coefficient
long double interco(long double n, long double pow, long double iter)
{
	long double ans = 1;
	int i = (n - 1);
	while (i >= 0)
	{
		if (i % 2 == 0)
		{
			ans = ans * binexp((n - i), pow, iter); // on 1st: i = 2 if n = 3 so we need (1 - (1/(n-2)))^0.5
		}

		else if (i % 2 == 1)
		{
			ans = (ans / (binexp((n - i), pow, iter)));
		}
		i--;
	}
	return ans;
}

//sqruareroot 2
long double sqrtt(long double n)
{
	long double pow = 0.5; // sqare root
	long double iter = 14; // the degree of accuracy
	if (n > 1)
	{
		return ((coeff(n))*(interco(n, pow, iter)));
	}
	else if (n == 1 || n == 0)
	{
		return(n);
	}
	else
	{
		cout << "ERROR: sqrtt(" << n << ", " << pow << ", " << iter << ")" << endl;
		cout << "Cannot find the " << (1 / pow) << "-root of a negative number!" << endl;
		return (0);
	}
}


//sqruareroot 3
long double sqrttt(long double n, long double iter)
{
	long double pow = 0.5; // sqare root
	if (n > 1)
	{
		return ((coeff(n))*(interco(n, pow, iter)));
	}
	else if (n == 1 || n == 0)
	{
		return(n);
	}
	else
	{
		cout << "ERROR: sqrtt(" << n << ", " << pow << ", " << iter << ")" << endl;
		cout << "Cannot find the " << (1 / pow) << "-root of a negative number!" << endl;
		return (0);
	}

}


int main()
{
start:
	long double n;
	cout << "Enter x: ";
	cin >> n;
	cout << "sqrtt(" << n << ") = " << sqrtt(n) << endl;
	cout << "sqrt(" << n << ") = " << sqrt(n) << endl;
	for (long double iter = 0; iter <= 14; iter++)
	{
		cout << "n(" << n << ", " << iter + 1 << ") = " << sqrttt(n, iter) << endl;
	}
	goto start;
	return 0;
}