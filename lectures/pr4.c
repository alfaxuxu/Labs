#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

//Скелет прораммы работы с потоками
//реализация потоковой функции
void* thread_func(void* vptr_args) {
	for (unsigned int i = 0; i < 20; i++) {
		fputs("b\n", stderr);
		wait_thread();
	}
	return NULL;
}

int main(int argc, char* argv[], char* envp[]) {
	pthread_t thread; //дескриптор потока
	//создание нового потока и вызова потоковой функции
	if (pthread_create(&thread, NULL, thread_func, NULL)) return EXIT_FAILURE;
	for (unsigned int i = 0; i < 20; i++) {
		puts("a");
	}
	//ожидание завершения потока
	if (pthread_join(thread, NULL)) return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
