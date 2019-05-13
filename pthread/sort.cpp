#include<iostream>
#include<vector>
#include<pthread.h>
#include<cstdlib>
using namespace std;
struct arg {
    vector<int> vec;
};
void generate_array(vector<int> &array, int n) {
    for (int i = 0; i < n; i++) {
        array.push_back(rand() % 50);
    }
    return;
}

void *bubblesort(void *info) {
    struct arg *Vec = (struct arg *)info;
    for(int k = 0; k < Vec->vec.size(); k++) {
        for(int i = 0; i + 1 < Vec->vec.size() - k; i++) {
            if (Vec->vec[i] > Vec->vec[i + 1]) {
                int tmp = Vec->vec[i];
                Vec->vec[i] = Vec->vec[i + 1];
                Vec->vec[i + 1] = tmp;
            }
        }
    }
}
void merge(struct arg info[], vector<int> &res) {
    int len1 = info[0].vec.size(), len2 = info[1].vec.size(), k = 0, l = 0;
    int i = 0, flag = 0;
    while (k < len1 && l < len2) {
        if (info[0].vec[k] < info[1].vec[l]) {
            flag = 1;
            res.push_back(info[0].vec[k]);
            k++;
        } else {
            flag = 0;
            res.push_back(info[1].vec[l]);
            l++;
        }
    }    
    if (flag == 1) {
        while (l < len2) {
            res.push_back(info[1].vec[l]);
            l++;
        }
    } else {
         while (k < len1) {
            res.push_back(info[0].vec[k]);
            k++;
        }

    }  
    return; 
}
int main() {
    pthread_t threads[2];
    int n = 100, elem;
    struct arg info[2];
//    cin>>n;
    vector<int> vec;
    generate_array(vec, n);  
    for (int i = 0; i < n / 2; i++)
        info[0].vec.push_back(vec[i]);
    for (int i = (n / 2); i < n; i++)
        info[1].vec.push_back(vec[i]);
    for (int i = 0; i < 2; i++)
        pthread_create(&threads[i], NULL, &bubblesort, &info[i]);
    for (int i = 0; i < 2; i++)
        pthread_join(threads[i], NULL);
    vector<int> res;
    merge(info, res);
    for (int i = 0; i < res.size(); i++)
        cout<<res[i]<<' ';
    cout<<endl;
    return 0;
}
