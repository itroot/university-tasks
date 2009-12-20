/* задача нахождения максимального простого делителя */
/* алгоритм перебора "до квадратного корня" */

int maxpr( int n )
{
	int min = 1;
	do
	{
		n /= min;
		min = n;
		int i;
		for( i = n-1; i > 1; i-- )
		{
			if ( i * i <= n  && n % i == 0 )
				min = i;
		}
	} while ( min < n ) ;
	
	return n;
}