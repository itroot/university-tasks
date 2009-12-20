/* задача нахождения максимального простого делителя */
/* алгоритм перебора "до квадратного корня" */

int maxpr( int n )
{
	int min;
	do
	{
		min = n;
		int i;
		for( i = 2; i*i <= n; i++ )
		{
			if ( n % i == 0 && i < min )
				min = i;
		}
		n /= min;
	} while ( n > 1 ) ;
	
	return min;
}