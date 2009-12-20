/* задача нахождения минимального делителя,
большего 1 */

int maxpr( int n )
{
	int min = n * n + n;
	int i;
	for( i = 1; i < n * n; i++ )
	{
		if ( i!= n && n % i == 0 )
			if ( i < min )
				min = i;
	}
	return min;
}