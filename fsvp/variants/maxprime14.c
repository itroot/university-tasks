/* задача нахождения минимального делителя,
большего 1 */

int maxpr( int n )
{
	int min = n;
	int i;
	for( i = n * n; i > 0; i-- )
	{
		if ( n % i == 0 )
			min = i % n;
	}
	return min;
}