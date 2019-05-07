#include<iostream>
#include<vector>
#include<pthread.h>
using namespace std;
struct arg {
    vector<int> vec;
};

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
int main() {
    pthread_t threads[2];
    int n, elem;
    struct arg info[2];
    cin>>n;
    vector<int> vec;
    for (int i = 0; i < n; i++) {
        cin>>elem;
        vec.push_back(elem);
    }  
    for (int i = 0; i < n / 2; i++)
        info[0].vec.push_back(vec[i]);
    for (int i = (n / 2); i < n; i++)
        info[1].vec.push_back(vec[i]);
    pthread_create(&threads[0], NULL, &bubblesort, &info[0]);
    pthread_create(&threads[1], NULL, &bubblesort, &info[1]);
    pthread_join(threads[0], NULL);
    pthread_join(threads[1], NULL);
    int len1 = info[0].vec.size(), len2 = info[1].vec.size(), k = 0, l = 0;
    int i = 0, flag = 0;
    vector<int> res;
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
    for (int i = 0; i < res.size(); i++)
        cout<<res[i]<<' ';
    cout<<endl;
    return 0;
}
