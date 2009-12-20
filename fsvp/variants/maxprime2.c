/* задача нахождения максимального делителя, 
отличного от самого числа */

int maxpr( int n )
{
	int i;
	for( i = n - 1; i > 0; i-- )
	{
		if ( n % i == 0 )
			return i;
	}
	return 1;
}