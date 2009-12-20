/* задача нахождения максимального делителя,
меньшего самого числа */

int maxpr( int n )
{
	int max = 1;
	int i;
	for( i = 2; i < n; i++ )
	{
		if ( ( n + i ) % i == 0 )
			max = i;
	}
	return max;
}