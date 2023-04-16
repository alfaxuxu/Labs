#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

//������ ������������� ��������� ������
void main()
{
	int *array = NULL;
	unsigned length, i;

	printf("Enter length of array: ");
	scanf("%d", &length);

	if (length > 0)
	{
		//��� ��������� ������ ������������ ���������.
		//���� ������ �� ���� ��������, �� ������������ NULL
		if ((array = (int*) malloc(length * sizeof(int))) != NULL)
		{
			for (i = 0; i < length; i++)
			{
				array[i] = i * i;
			}
		}
		else
		{
			printf("Error: can't allocate memory");
		}
	}

	//���� ���������� ���� ����������������, �� ������� �
	if (array != NULL)
	{
		free(array);
	}

	getch();

	return 0;
}