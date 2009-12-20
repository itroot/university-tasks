/* задача нахождения минимального делителя,
большего 1 */

int maxpr( int n )
{
	int min = n * n * n;
	int i;
	for( i = n - 1; i > 0; i-- )
	{
		if ( (n + i%n) % i == 0 )
			min = i;
	}
	return min;
}
