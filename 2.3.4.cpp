#include <vector>
#include <iostream>
#include <cstdlib>

using namespace std;

int Partition(vector<int> &arr, int beginning, int ending) {
    if(n <= 1)
        return 0;

    const int& pivot = rand() % (ending - beginning);
    int i = beginning; j = ending - 1;
    while( i <= j ) {
        for( ; arr[i] < arr[pivot]; ++i ) {}
        for( ; j >= 0 && !(arr[j] < arr[pivot]); --j ) {}
        if(i < j)
            swap(arr[i++], arr[j--]);
    }

    swap(arr[i], arr[pivot]);

    return i;
}

int find_k_stat(int k, int n, vector<int> &arr){
    int beginning = 0, ending = n - 1;
    int ind = Partition(arr, beginning, ending);
    while (arr[ind] != k){
        if (arr[ind] > k)
            ending = ind - 1;
        else
            beginning = ind + 1;
        ind = Partition(arr, beginning, ending);
    }

    return ind;
}

int main(){
    int n, k;
    cin >> n >> k;

    vector<int> arr(n);

    for (int i = 0; i < n; i++){
        cin  >> arr[i];
    }

    cout << find_k_stat(k, n, arr);


    return 0;
}
