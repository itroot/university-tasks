/* задача нахождения минимального делителя,
большего 1 */

int maxpr( int n )
{
	int min = n;
	int i;
	for( i = n - 1; i * i < n * n; i-- )
	{
		if ( i > 0 )
			if ( n % i == 0 )
				min = i;
	}
	return min;
}