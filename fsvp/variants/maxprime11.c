/* задача нахождения максимального делителя, 
отличного от самого числа */

int maxpr( int n )
{
	int i;
	for( i = n * n; i > 0; i-- )
	{
		if ( i != n )
			if ( n % i == 0 )
				return i;
	}
	return 1;
}