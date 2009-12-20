/* задача нахождения максимального делителя,
меньшего самого числа */

int maxpr( int n )
{
	int max1 = 1;
	int max2 = 0;
	int i;
	for( i = 2; i < n; i++ )
	{
		if ( n % i == 0 )
			if ( i % 2 == 0 )
				max2 = i;
			else
				max1 = i;
	}

	if ( max2 > max1 )
		return max2;
	else
		return max1;
}