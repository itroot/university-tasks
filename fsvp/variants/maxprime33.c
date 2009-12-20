/* задача нахождения максимального простого делителя */
/* алгоритм "по определению" */

int maxpr( int n )
{
	int i;
	for( i = n-1; i > 0 ; i-- )
	{
		if ( n % i == 0 )
		{
			int pc = 0;
			for( int j = i - 1; j > 1; j-- )
				if ( i % j == 0 )
					pc++;
			
			if ( pc == 0 )
				return i;
		}
	}
	return n * n + n;
}
