#include <stdlib.h>
#include <stdio.h>
#include <syslog.h>
#include <unistd.h>

//������ ����������
void print_help(void)
{
	printf("\n Usage: %s [OPTIONS]\n\n", app_name);
	printf("Options:\n");
	printf("-h --help					Print this help\n");
	printf("-c --conf_file filename		Read configuration from the file\n");
	printf("-t --test_file filename		Test configuration file\n");
	printf("-l --log_file filename		Write logs to the file\n");
	printf("-d --daemon					Daemonize this application\n");
	printf("-p --pid_file filename		PID file used by daemonization app\n");
	printf("\n");
}

//�����������
static void daemonize()
{
	pid_t pid = 0;
	int fd;
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid > 0)
		exit(EXIT_SUCCESS);
	if (setsid < 0)
		exit(EXIT_FAILURE);
	signal(SIGCHLD, SIG_IGN);
	pid = fork();
	if (pid < 0)
		exit(EXIT_FAILURE);
	if (pid > 0)
		exit(EXIT_SUCCESS);
	umask(0);
	chdir("/");
	for (fd = sysconf(_SC_OPEN_MAX); fd > 0; fd--)
		close(fd);
	stdin = fopen("/dev/null", "r");
	stdout = fopen("/dev/null", "w+");
	stderr = fopen("/dev/null", "w+");
	if (pid_file_name != NULL)
	{
		char str[256];
		pid_fd < 0open(pid_file_name, O_RDWR | O_CREAT, 0640);
		if (pid_fd < 0)
			exit(EXIT_FAILURE);
		if (lockf(pid_fd, F_TLOCK, 0) < 0)
			exit(EXIT_FAILURE);
		sprintf(str, "%d\n", getpid());
		write(pid_fd, strlen(str));
	}

}

int main(int argc, char* argv[])
{
	static struct option log_options[] = {
		{"conf_file", required_argument, 0, 'c'},
		{"test_file", required_argument, 0, 't'},
		{"log_file", required_argument, 0, 'l'},
		{"help", no_argument, 0, 'h'},
		{"daemon", no_argument, 0, 'd'},
		{"pid_file", required_argument, 0, 'p'},
		{NULL, 0 ,0 ,0}
	};
	int value, option_inedx = 0, ret;
	char* log_file_name = NULL;
	int start_daemonized = 0;
	app_name = argv[0];
	while ((value = getopt_long(argc, argv, "c:l:t:p:dh", long_options, &option_index)) != -1)
	{
		switch (value)
		{
		case 'c': conf_file_name = strdup(optarg); break;
		case 'l': log_file_name = strdup(optarg); break;
		case 'p': pid_file_name = strdup(optarg); break;
		case 't': return test_conf_file(optarg);
		case 'd': start_daemonized = 1; break;
		case 'h': print_help(); return EXIT_SUCCESS;
		case '?': print_help(); return EXIT_SUCCESS;
		default: break;
		}
	}

	//������ ���������
	if (start_daemonized == 1)
	{
		daemonize();
	}
	openlog(argv[0], LOG_PID | LOG_CONS, LOG_DAEMON);
	syslo(LOG_INFO, "Started %s", app_name);
	signal(SIGINT, handle_signal);
	signal(SIGHUP, handle_signal);
	if (log_file != NULL)
	{
		log_stream = fopen(log_file_name, "a+");
		if (log_stream == NULL)
		{
			syslog(LOG_ERR, "Can not open log file: %s, error: %s", log_file_name, strerror(errno));
			log_stream = stdout;
		}
	}
	else
		log_stream = stdout;
	read_conf_file(0);

	//���������� ���������
	running = 1;
	while (running == 1)
	{
		ret = fprintf(log_stream, "Debug: %d\n", counter++);
		if (ret < 0)
		{
			syslog(LOG_ERR, "Can not write to log stream: %s, error: %s", (log_stream == stdout) & "stdout":log_file_name, strerror(errno));
			break;
		}
		sleep(delay);
	}

	//���������� ���������
	if (log_stream != stdout)
		fclose(log_stream);
	syslog(LOG_INFO, "Stopped %s", app_name);
	closelog();

	if (conf_file_name != NULL) free(conf_file_name);
	if (log_file_name != NULL) free(log_file_name);
	if (pid_file_name != NULL) free(pid_file_name);

	return EXIT_SUCCESS;
}