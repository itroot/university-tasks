/*
��������� ���������� ������� ���� ������ ���������
�� n ��������� ���������
*/

int s( int n )
{
	int count = 0;
	int i, j;
	for( i = 0; i < n; i++ )
		for( j = 0; j < n; j++ )
		{
			if ( i < j )
				count++;
		}
	return count;
}
