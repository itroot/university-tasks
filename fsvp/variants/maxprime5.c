/* задача нахождения минимального делителя,
большего 1 */

int maxpr( int n )
{
	int min = n;
	int i;
	for( i = 1; i < n; i++ )
	{
		if ( n % i == 0 )
			if ( i < min )
				min = i;
	}
	return min;
}