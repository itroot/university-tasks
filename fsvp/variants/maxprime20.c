/* задача нахождения максимального делителя, 
отличного от самого числа */

int maxpr( int n )
{
	int max1 = 1;
	int max2 = 1;
	int i;
	for( i = n - 1; i > 0; i-- )
	{
		if ( n % i == 0 )
			if ( i % 2 == 1 )
			{
				if ( i > max2 )
					max2 = i;
			}
			else
			{
				if ( i > max1 )
					max1 = i;
			}
	}
	if ( max1 < max2 )
		return max2;
	else
		return max1;
}