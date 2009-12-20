/*
посчитать количество выборов двух разных элементов
из n различных элементов
*/

int s( int n )
{
	int count = 0;
	int all = 0;
	int i, j;
	for( i = 0; i < n; i++ )
		for( j = 0; j < n; j++ )
		{
			if ( i > j )
				count++;
			all++;
		}
	int k = n * n;
	return all - count - k - k;
}
