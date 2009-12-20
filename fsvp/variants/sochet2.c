/*
посчитать количество выборов трех элементов
(возможно с повторами) из n различных элементов
*/

int s( int n )
{
	int count = 0;
	int count2 = 0;
	int count3 = 0;
	int i, j ,k;
	for( i = 0; i < n; i++ )
		for( j = 0; j < n; j++ )
			for( k = 0; k < n; k++ )
			{
				if ( i < j  && j < k )
					count ++;
				else if ( i == j && j == k )
					count3 ++;
				else if ( i <= j && j <= k )
					count2 ++;
			}
	return count + count2 / 2 + count3 / 3;
}
