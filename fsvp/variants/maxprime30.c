/* ������ ���������� ������������� �������� �������� */
/* �������� "�� �����������" */

int maxpr( int n )
{
	int i;
	for( i = n-1; i > 0 ; i-- )
	{
		if ( n % i == 0 )
		{
			int is_prime = 1;
			int j;
			for( j = i - 1; j > 1; j-- )
				if ( i % j == 0 )
					is_prime = 0;
			
			if ( is_prime )
				return i;
		}
	}
	return 1 - n;
}
