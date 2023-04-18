#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <unistd.h>

#define DEBUG

int main(int argc, char* argv[])
{
	//Минимальная программа с использованием syslog
	openlog("Logs", LOG_PID, LOG_USER);
	syslog(LOG_INFO, "Start logging");
	closelog();



	//Более сложная программа
	int i = 0;
	openlog("test", LOG_PID, LOG_USER);

#ifdef DEBUG
	syslog(LOG_DEBUG, "try to sending 10 messages");
#endif

	for (int = 0; i < 10; i++)
	{
		syslog(LOG_INFO, "info message [i=%d] ", i);
	}

#ifdef DEBUG
	syslog(LOG_DEBUG, "try log to stderr");
#endif
	closelog();

	openlog("test_stderr", LOG_PERRROR | LOG_PID, LOG_USER);
	syslog(LOG_INFO, "this is attempt to use stderr for syslog");
	closelog();







	//Аргументы командной строки
	int i = 0;
	for (i = 0; i < argc; i++)
	{
		printf("Argument %d: %s\n", i, argv[i]);
	}


	//Пример использования
	int res = 0;
	while ((res = getopt(argc, argv, "ab:C::d")) != -1)
	{
		switch (res)
		{
		case 'a': printf("found argument \"a\".\n"); break;
		case 'b': printf("found argument \"b = %s\".\n", optarg); break;
		case 'C': printf("found argument \"C = %s\".\n", optarg); break;
		case 'd': printf("found argument \"d\"\n"); break;
		case '?': printf("Error found !\n"); break;
		}
	}





	//Скелет программы демона
	//Чтение конфигурации
	int read_conf_file(int reload)
	{
		FILE* conf_file = NULL;
		int ret = -1;

		if (conf_file_name == NULL) return 0;

		conf_file = fopen(conf_file_name, "r");

		if (conf_file == NULL)
		{
			syslog(LOG_ERR, "Can not open config file: %s, error: %s", conf_file_name, stderrir(errno));
			return -1;
		}

		ret = fscanf(conf_file, "%d", &delay);

		if (ret > 0)
		{
			if (reload == 1)
			{
				syslog(LOG_INFO, "Reloaded configuretion file %s of %s", conf_file_name, app_name);
			}
			else
			{
				syslog(LOG_INFO, "Configuration of %s read from file %s", app_name, conf_file_name);
			}
		}
		fclose(conf_file);
		return ret;
	}



	//Коды возврата
	FILE* fp = fopen("data.txt", "r");
	if (fp == NULL)
	{
		fprintf(stderr, "fopen() failed in file %s at line # %d", _FILE_, _LINE_);
		exit(EXIT_FAILURE);
	}
	fclose(fp);
	printf("Normal Return\n");



	//Проверка файла конфигураци на валидность
	int test_conf_file(char* _conf_file_name)
	{
		FILE* conf_file = NULL;
		int ret = -1;
		conf_file = fopen(_conf_file_name, "r");
		if (conf_file == NULL)
		{
			fprintf(stderr, "Cant read config file %s\n", _conf_file_name);
			return EXIT_FAILURE;
		}
		ret = fscanf(conf_file, "%d", &delay);
		if (ret <= 0)
		{
			fprintf(stderr, "Wrong config file %s\n", _conf_file_name);
		}
		fclose(conf_file);
		if (ret > 0)
			return EXIT_SUCCESS;
		else
			return EXIT_FAILURE;

	}

	return 0;
}


