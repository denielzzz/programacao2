#include <stdio.h>

int main()
{
	int m, n;

	scanf("%d %d", &m, &n);
	getchar();

	char map[m][n];

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			map[i][j] = getchar();
		getchar();
	}

	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			printf("%c", map[i][j]);
		printf("\n");
	}

	return 0;
}