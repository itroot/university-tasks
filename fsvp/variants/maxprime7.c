/* задача нахождения максимального делителя,
меньшего самого числа */

int maxpr( int n )
{
	int max = -1;
	int i;
	for( i = 1; i < n; i++ )
	{
		if ( n % i == 0 )
			max = i;
	}
	return max;
}