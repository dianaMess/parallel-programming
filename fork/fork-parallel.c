#define _GNU_SOURCE 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include<sys/wait.h>
#include <sched.h>
int new_array[100];
int * bubblesort(int *array, int size) {
    for(int k = 0; k < size; k++) {
        for(int i = 0; i + 1 < size - k; i++) {
            if (array[i] > array[i + 1]) {
                int tmp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = tmp;
            }
        }
    }
    return array;
}
void merge(int * first, int * second, int size) {
    int k = 0, l = 0, i = 0, flag = 0;
    int len1 = size / 2, len2 = (size - (size / 2));
    while (k < len1 && l < len2) {
        if (first[k] < second[l]) {
            flag = 1;
            new_array[i++] = first[k];
            k++;
        } else {
            flag = 0;
            new_array[i++] = second[l];
            l++;
        }
    }    
    if (flag == 1) {
        while (l < len2) {
            new_array[i++] = second[l];
            l++;
        }
    } else {
         while (k < len1) {
            new_array[i++] = first[k];
            k++;
        }
    }   
    return;
}
int main(int argc, char *argv[]) {
    enum { maxSons = 100 };
    int fd[maxSons][2];
    pid_t id[maxSons];
    int sons = 2, fullSize, i;
    int n, array[100], first[100], second[100];
    scanf("%d", &n);
    for (int k = 0; k < n; k++) 
        scanf("%d", &array[k]);
    for (int k = 0; k < n / 2; k++)
        first[k] = array[k];
    int j = 0;
    for (int k = n / 2; k < n; k++)
        second[j++] = array[k];
    for (i = 0; i < sons; i++) {
	pipe(fd[i]);
	if ((id[i] = fork()) == 0) {
	    cpu_set_t mask;
	    CPU_ZERO( &mask );
	    CPU_SET(i % 2, &mask );
	    if( sched_setaffinity( 0, sizeof(mask), &mask ) == -1 ) {
		printf("WARNING: Could not set CPU Affinity, continuing...\n");
	    }
            int *new_array;
            if (!(i % 2)) {
                new_array = bubblesort(first, n / 2);
            } else {
                new_array = bubblesort(second, n - (n / 2));
            }		// son
	    close(fd[i][0]);
            if (!(i % 2)) 
	        write(fd[i][1], new_array, (n / 2) * sizeof(int));
            else
                write(fd[i][1], new_array, (n - (n / 2)) * sizeof(int));
		close(fd[i][1]);
		return 0;
        }
    }
	// parent
    int first_sorted[100], second_sorted[100];
    for (i = 0; i < sons; i++) {
        close(fd[i][1]);
	int st;
	wait4(id[i], &st, 0, NULL);
        if (!(i % 2))
            read(fd[i][0], first_sorted, (n / 2) * sizeof(int));
        else
            read(fd[i][0], second_sorted, (n - (n / 2)) * sizeof(int));
        close(fd[i][0]);
    }
    printf("arrays:");
    putchar('\n');
    for (int k = 0; k < n / 2; k++)
        printf("%d ", first_sorted[k]);
    putchar('\n');
    for (int k = 0; k < (n - (n / 2)); k++)
        printf("%d ", second_sorted[k]);
    putchar('\n');
    int * sorted;
    int sort[100];
    merge(first_sorted, second_sorted, n);
    for (int k = 0; k < n; k++)
        printf("%d ", new_array[k]);
    return 0;
}
