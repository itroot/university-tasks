/* задача нахождения минимального делителя,
большего 1 */

int maxpr( int n )
{
	int min1 = n;
	int min2 = n;
	int i;
	for( i = n - 1; i > 0; i-- )
	{
		if ( n % i == 0 )
			if ( i % 2 == 1 )
				min1 = i;
			else
				min2 = i % n;
	}
	if ( min1 < min2 )
		return min1;
	else
		return min2;
}