/* задача нахождения максимального делителя,
меньшего самого числа */

int maxpr( int n )
{
	int max = 1;
	int i;
	for( i = -n; i < n; i++ )
	{
		if ( i > 1 )
			if ( n % i == 0 )
				max = i;
	}
	return max;
}