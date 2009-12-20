/* задача нахождения минимального делителя,
большего 1 */

int maxpr( int n )
{
	int min1 = n;
	int min2 = n;
	int i;
	for( i = 1; i < n; i++ )
	{
		if ( n % i == 0 )
			if ( i % 2 == 0 )
			{
				if ( i < min2 )
					min2 = i;
			}
			else
				if ( i < min1 )
					min1 = i;
	}
	if ( min1 < min2 )
		return min1;
	else
		return min2;
}