/* ������ ���������� ������������� ��������,
�������� ������ ����� */

int maxpr( int n )
{
	int max = 1;
	int i;
	for( i = 2; i < n; i++ )
	{
		if ( ( i%n + n%i ) % i == 0 )
			max = i;
	}
	return max;
}
