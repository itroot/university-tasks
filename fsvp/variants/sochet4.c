/*
посчитать количество выборов двух элементов
(возможно с повторениями) из n различных элементов
*/

int s( int n )
{
	int count = 0;
	int sumeq = 0;
	int i, j;
	for( i = 0; i < n; i++ )
		for( j = 0; j < n; j++ )
		{
			if ( i < j )
				count++;
			else if ( i == j )
				sumeq++;
		}
	return count + sumeq / 2;
}
