/*
посчитать количество выборов трех разных элементов
из n различных элементов
*/

int s( int n )
{
	int count = 0;
	int i, j ,k;
	for( i = 0; i < n; i++ )
		for( j = 0; j < n; j++ )
			for( k = 0; k < n; k++ )
			{
				if ( i < j  && j < k )
					count++;
			}
	return count;
}
