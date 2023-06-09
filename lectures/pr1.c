#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

#include<fcntl.h>
#include<errno.h> 

#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h> 

extern int errno;

void main()
{
	//������ ������������� ��������� ������
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
			//printf("Error: can't allocate memory");
			if (errno == ENOMEM)
			{
				perror("Malloc error");
				exit(2);
			}
			else
			{
				exit(3);
			}
		}
	}
	//���� ���������� ���� ����������������, �� ������� �
	if (array != NULL)
	{
		free(array);
	}
	getch();




	//������ � �������
	//������ ��������� ������ ������

	int sz; //���������� ����������� ����
	//������������ ������ �������� 100 ����
	char* c = (char*)calloc(100, sizeof(char));
	// ��������� ���� ��� ������ � ��� ������������� ��������
	int fd = open("foo.txt", O_RDONLY | O_CREAT);
	// ������� �� ����� �������� ����������� �����
	printf("fd = %d/n", fd);
	// ������� �� ����� �������� ����������� �����
	if (fd == -1)
	{
		// ������� ��� ������ ���������� ���������� ������
		printf("Error Number % d\n", errno);

		// ������� �� ����� ��������� �������� ������
		perror("open file error:");
	}
	//������ �� ����� 10 ����
	//� sz �������� ���������� ����, ������� ������� ��������� �� �����
	sz = read(fd, c, 10);
	printf("called read(% d, c, 10). returned that"
		" %d bytes were read.\n", fd, sz);
	//���������� � ����� ������� ������ ����� ������
	c[sz] = '\0';
	//��������� ����
	if (close(fd) < 0) {
		perror("close file error:");
		exit(1);
	}
	printf("closed the fd.\n");





	//�������� ��������
	//��������� ����� fork()
	int pid = fork();
	switch (pid) {
	case -1:
		perror("fork");
		return -1;
	case 0: // Child
		printf("my pid = %i, returned pid = %i\n", getpid(), pid);
		break;
	default: // Parent
		printf("my pid = %i, returned pid = %i\n", getpid(), pid); break;



	//������ ������������� ������ exec()
	char* args[] = { "/bin/cat", "--help", NULL };
	execve("/bin/cat", args, environ);

	return 0;
}