#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define MAX 2000
#define BUFFER_LENGTH 100
#define DATA_MAX 20000

typedef struct WEB {
	char *ip;
	char *time;
	char *url;
	char *status;
}web;

web data[DATA_MAX];
int print_data=0;
void process_command();
void sort();
void load();
void sort_T();
void sort_IP();
void print();
int compare_IP(const void *a, const void *b);
int compare_T(const void *a, const void*b);
int month_judge(char *tmp1,char *tmp2);
int n = 0;
int main(void) {
	process_command();
	return 0;
}

void process_command() {

	char command[BUFFER_LENGTH];
	while (1) {

		printf("$ ");
		scanf("%s", command);
		if (strcmp(command, "read") == 0) {
			load();
		}
		else if (strcmp(command, "sort") == 0) {
			sort();
		}
		else if (strcmp(command, "print") == 0) {
			print();
		}
		else if (strcmp(command, "exit") == 0)
			break;

	}

}

void sort() {
	char tmp[BUFFER_LENGTH];
	scanf("%s", tmp);

	if (strcmp(tmp, "-t") == 0) {
		sort_T(); print_data = 1;
	}
	else if (strcmp(tmp, "-ip") == 0) {
		sort_IP(); print_data = 2;
	}
	else return;
}
void sort_T() {
	qsort(data, n-1, sizeof(web), compare_T);
}
void sort_IP() {
	qsort(data, n-1, sizeof(web), compare_IP);
}

void load() {
	char buffer[MAX];
	char *token[4];
	char *time[6];
	char file_name[BUFFER_LENGTH];
	scanf("%s", file_name);
	FILE*in_fp = fopen(file_name, "r");
	fgets(buffer, MAX, in_fp);
	while (!feof(in_fp)) {
		fgets(buffer, MAX, in_fp);
		token[0] = strtok(buffer, ",");
		for (int i = 1; i <= 3; i++)
			token[i] = strtok(NULL, ",");
		
		data[n].ip = strdup(token[0]);
		data[n].time = strdup(token[1]);
		data[n].url = strdup(token[2]);
		data[n].status = strdup(token[3]); n++;
	}
	fclose(in_fp);
}

int compare_T(const void *a, const void*b) {
	char timeA[BUFFER_LENGTH], timeB[BUFFER_LENGTH];
	char *A[6], *B[6];
	strcpy(timeA, ((web*)a)->time);
	strcpy(timeB, ((web*)b)->time);

	A[0] = strtok(timeA, "/");
	A[1] = strtok(NULL, "/");
	A[2] = strtok(NULL, ":");
	A[3] = strtok(NULL, "\0");

	B[0] = strtok(timeB, "/");
	B[1] = strtok(NULL, "/");
	B[2] = strtok(NULL, ":");
	B[3] = strtok(NULL, "\0");

	if (strcmp(A[2], B[2]) != 0)
		return (strcmp(A[2], B[2]));
		
	if (month_judge(A[1], B[1])!= 0) {
		return month_judge(A[1], B[1]);
	}
	strcmp(A[0], B[0]);
	if (strcmp(A[0], B[0]) != 0) {
		return (strcmp(A[0], B[0]));
	}

	return (strcmp(A[3], B[3]));
}
int compare_IP(const void *a, const void *b) {
	int result = strcmp(((web *)a)->ip, ((web *)b)->ip);
	if (result != 0)
		return result;
	return compare_T(a, b);
}
void print() {
	if (print_data == 1) {
		for (int i = 0; i < n-1; i++) {
			printf("%s\n", data[i].time);
			printf("\tIP: %s\n", data[i].ip);
			printf("\tURL: %s\n", data[i].url);
			printf("\tStatus: %s", data[i].status);
		}
	}
	else if (print_data == 2) {
		for (int i = 0; i < n-1; i++) {
			printf("%s\n", data[i].ip);
			printf("\tIP: %s\n", data[i].time);
			printf("\tURL: %s\n", data[i].url);
			printf("\tStatus: %s", data[i].status);
		}
	}
	else
		printf("Error!\n");
}
int month_judge(char *tmp1,char *tmp2) {
	char *Month[12] = { "Jan","Feb","Mer","Apr","May","Jun","Jul","Aug","Sep","Oct","Nov","Dec" };
	int A=0, B=0;
	for (int i = 0; i < 12; i++) {
		if (strcmp(tmp1, Month[i]) == 0)
			A = i;
		if (strcmp(tmp2, Month[i]) == 0)
			B = i;
	}
	return A - B;
}