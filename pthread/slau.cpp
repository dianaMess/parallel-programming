#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <pthread.h>
#include <iostream>
#include <vector>
using namespace std;

vector<vector<double>> A_matrix(100, vector<double>(100));
vector<double> f_vector(100);

typedef struct Index_info {
    int i;
    int k;
    int n;
} info;

void generate_matrix(int n) {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            A_matrix[i][j] = rand() % 50;
            sum += A_matrix[i][j];
        }
    }
    for (int i = 0; i < n; i++) {
        A_matrix[i][i] += sum;
    }
    for (int i = 0; i < n; i++) {
        f_vector[i] = rand() % 25;
    }
    return;
}

void* lines_computing(void *args) {
    info *arg = (info*) args;
    int k = arg -> k;
    int i = arg -> i;
    int n = arg -> n;
    for(int j = k + 1; j < n; j++) {
        A_matrix[i][j] = A_matrix[i][j] - A_matrix[i][k] * A_matrix[k][j];
    }
    f_vector[i] = f_vector[i] - A_matrix[i][k] * f_vector[k];
    A_matrix[i][k] = 0;
    return nullptr;
}

void gauss(int n, int count) {
    int i = 0, j = 0, k = 0, status, status_addr, pthread_iter;
    int pthread_count = count;
    pthread_t threads[10];
    info args[10];
    for(k = 0; k < n; k++) {
        for(j = k + 1; j < n; j++) {
            A_matrix[k][j] = A_matrix[k][j] / A_matrix[k][k];
        }
        f_vector[k] = f_vector[k] / A_matrix[k][k];
        A_matrix[k][k] = A_matrix[k][k] / A_matrix[k][k];
        for(i = k + 1; i < n; i = i + 2) {
            for (pthread_iter = 0; pthread_iter < count; pthread_iter++) {
                if(i + pthread_iter < n) {
                    args[pthread_iter].k = k;
                    args[pthread_iter].i = i + pthread_iter;
                    args[pthread_iter].n = n;
                    pthread_create(&threads[pthread_iter], NULL, lines_computing, (void*) &args[pthread_iter]);
                    pthread_count = 2;
                } else {
                    pthread_count = 1;
                }
            }
            for (pthread_iter = 0; pthread_iter < pthread_count; pthread_iter++) {
                pthread_join(threads[pthread_iter], (void**)&status_addr);
            }
            pthread_count = 2;
        }
    }

    return;
}

int main(int argc, char * argv[]) {
    int n = atoi(argv[1]);
    int i, j, k;
    double num;
    int pthread_count = atoi(argv[2]);
    generate_matrix(n);
    gauss(n, pthread_count);
    for(i = 0; i < n; i++) {
        for(j = 0; j < n; j++) {
            cout<<A_matrix[i][j]<<' ';
        }
        cout<<endl;
    }
    for(i = 0; i < n; i++) {
        cout<<f_vector[i]<<' ';
    }
    cout<<endl;
    return 0;
}

