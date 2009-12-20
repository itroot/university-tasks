/* задача нахождения максимального делителя, 
отличного от самого числа */

int maxpr( int n )
{
	int max = 1;
	int i;
	for( i = n - 1; i > 0; i-- )
	{
		if ( n % i == 0 )
			if ( i > max )
				max = i;
	}
	return max;
}