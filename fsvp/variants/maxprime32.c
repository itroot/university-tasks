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
			int j;
			for( j = 2; j < i; j++ )
				if ( i % j == 0 )
					pc++;
			
			if ( pc == n % i )
				return i;
		}
	}
	return n - n + 2;
}
