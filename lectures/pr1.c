#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

void main()
{
	//Пример динамического выделения памяти

	int *array = NULL;
	unsigned length, i;

	printf("Enter length of array: ");
	scanf("%d", &length);

	if (length > 0)
	{
		//При выделении памяти возвращается указатель.
		//Если память не была выделена, то возвращается NULL
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

	//Если переменная была инициализирована, то очищаем её
	if (array != NULL)
	{
		free(array);
	}

	getch();





	//Пример программы чтения данных

	int sz; //количество прочитанных байт
	//динамический массив размером 100 байт
	char* c = (char*)calloc(100, sizeof(char));
	// открываем файл для чтения и при необходимости создания
	int fd = open("foo.txt", O_RDONLY | O_CREAT);
	// выводим на экран значение дескриптора файла
	printf("fd = %d/n", fd);
	// выводим на экран значение дескриптора файла
	if (fd == -1)
	{
		// выводим код ошибки последнего системного вызова
		printf("Error Number % d\n", errno);

		// выводим на экран текстовое описание ошибки
		perror("open file error:");
	}
	//читаем из файла 10 байт
	//в sz хранится количество байт, которое удалось прочитать из файла
	sz = read(fd, c, 10);
	printf("called read(% d, c, 10). returned that"
		" %d bytes were read.\n", fd, sz);
	//записываем в конец массива символ конца строки
	c[sz] = '\0';
	//закрываем файл
	if (close(fd) < 0) {
		perror("close file error:");
		exit(1);
	}
	printf("closed the fd.\n");



	return 0;
}