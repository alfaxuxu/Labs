#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

//������ �������� ������ � ��������
//���������� ��������� �������
void* thread_func(void* vptr_args) {
	for (unsigned int i = 0; i < 20; i++) {
		fputs("b\n", stderr);
		wait_thread();
	}
	return NULL;
}

int main(int argc, char* argv[], char* envp[]) {
	pthread_t thread; //���������� ������
	//�������� ������ ������ � ������ ��������� �������
	if (pthread_create(&thread, NULL, thread_func, NULL)) return EXIT_FAILURE;
	for (unsigned int i = 0; i < 20; i++) {
		puts("a");
	}
	//�������� ���������� ������
	if (pthread_join(thread, NULL)) return EXIT_FAILURE;
	return EXIT_SUCCESS;
}
