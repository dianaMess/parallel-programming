#include<iostream>
#include<vector>
#include<pthread.h>
#include<cstdlib>
using namespace std;
void generate_array(vector<int> &array, int n) {
    for (int i = 0; i < n; i++) {
        array.push_back(rand() % 50);
    }
    return;
}

void bubblesort(vector<int> &vec) {
    for(int k = 0; k < vec.size(); k++) {
        for(int i = 0; i + 1 < vec.size() - k; i++) {
            if (vec[i] > vec[i + 1]) {
                int tmp = vec[i];
                vec[i] = vec[i + 1];
                vec[i + 1] = tmp;
            }
        }
    }
}
int main() {
    int n, elem;
//    cin>>n;
    n = 100;
    vector<int> vec;
    generate_array(vec, n);  
/*    for (int i = 0; i < n / 2; i++)
        vec.push_back(vec[i]);
    for (int i = (n / 2); i < n; i++)
        vec.push_back(vec[i]);
    vector<int> res;
    merge(info, res);
*/
    bubblesort(vec);
    for (int i = 0; i < vec.size(); i++)
        cout<<vec[i]<<' ';
    cout<<endl;
    return 0;
}
