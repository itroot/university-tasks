/*@ predicate isDivisor(int m, int n) { (n % m == 0) } */

/*@ predicate isPrime(int n) { (n >= 1) && \forall int i;  ((i >= 2) && (i < n)) => !isDivisor(i, n) } */

/*@ requires (n >= 2)
  @ ensures (\result < n) && isDivisor(\result, n) && isPrime(\result) && (\forall int i; ((i > \result) && (i < n)) => (!isPrime(i) || !isDivisor(i, n)))
  @*/
int maxpr( int n )
{
	int i;
	/*@
	  @ invariant (i < n) && (i >= 0) && (\forall int k; ((k > i) && (k < n)) => (!isPrime(k) || !isDivisor(k, n)))
	  @ variant i
	  @*/
	for( i = n-1; i > 0 ; i-- )
	{
		if ( n % i == 0 )
		{
			int is_prime = 1;
			int j;
			/*@
			  @ invariant (j >= 1) && ((i >= 2) => (j <= i-1)) && (((i == 1) || (i==2)) => (is_prime != 0)) &&
			  @           ((is_prime != 0) <=> (\forall int k; (k >= 2) && (k < j) => (!isDivisor(k, i))))
			  @ variant (i - j)
			  @*/
			for( j = i - 1; j > 1; j-- )
				if ( i % j == 0 )
				{
					is_prime = 0;
					break;
				}
			
			if ( is_prime )
				return i;
		}
	}
	return 1;
}
