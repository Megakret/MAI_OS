#include <pthread.h>
#include <stdio.h>
#include<string.h>
#include<stdbool.h>
const int kBuffer = 1000;
const int kThreadCount = 5;
typedef struct{
	char* field;
	char* sample;
	int start_pos;
	int end_pos;
	int sample_len;
	int field_len;
} ThreadArg;
void *StartThread(void *void_arg) {
	ThreadArg* args = (ThreadArg*)void_arg;
	for(int i = args->start_pos; i < args->end_pos; ++i){
		bool has_found = true;	
		for(int j = i; j < args->field_len && j - i < args->sample_len; ++j){
			if(args->field[j] != args->sample[j - i]){
				has_found = false;
				break;
			}
		}
		if(has_found){
			//Success
			printf("Found sample at %d\n", i);
		}
	}
	return NULL;
}
int main() {
	char field[kBuffer];
	for(int i = 0; i < kBuffer; ++i){
		field[i] = '\0';
	}
	char* _field = fgets(field, kBuffer, stdin);
	if(_field == NULL){
		return -1;
	}
	int field_len = strlen(field);
	char sample[kBuffer];
	for(int i = 0; i < kBuffer; ++i){
		sample[i] = '\0';
	}
	char* _sample = fgets(sample, kBuffer, stdin);
	if(_sample == NULL){
		return -1;
	}
	int sample_len = strlen(sample) - 1; //-1 because of \n
  pthread_t thread_ids[kThreadCount];
	ThreadArg args[kThreadCount];
	for(int i = 0; i < kThreadCount; ++i){
		ThreadArg arg = {field, sample, field_len/kThreadCount*i, field_len/kThreadCount*(i+1), sample_len, field_len};
		args[i] = arg;
	}
  for (int i = 0; i < kThreadCount; ++i){
    int err = pthread_create(&thread_ids[i], NULL, &StartThread, &args[i]);
  }
	for(int i = 0; i < kThreadCount; ++i){
		pthread_join(thread_ids[i], NULL);
	}
}
