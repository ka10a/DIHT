#include <bits/stdc++.h>

using namespace std;

/*Даны два массива целых чисел одинаковой длины A[0..n-1] и B[0..n-1].
Необходимо найти первую пару индексов i0 и j0, (i0 <= j0)
такую что A[i0] + B[j0] = max {A[i] + B[j],
где 0 <= i < n, 0 <= j < n, i <= j}. Время работы - O(n). n ≤ 100000. */


pair <int, int> init(int a, pair <int, int> prev, int i){
    if (prev.first >= a)
        return prev;
    return {a, i};
}


pair<int, int> calc(int n, pair<int, int>* arr, int* b) {
    int maxx = b[0] + arr[0].first, ans1 = arr[0].second, ans2 = 0;
    for (int i = 1; i < n; i++){

        //Считаем максимальную сумму для каждого B[i]
        if (b[i] + arr[i].first > maxx){
            maxx = b[i] + arr[i].first;
            ans1 = arr[i].second;
            ans2 = i;
        }
    }

    return {ans1, ans2};
}


int main(){

    int n;
    cin >> n;
    pair <int, int> arr[n];

    int a;
    cin >> a;
    arr[0] = {a, 0};
    for (int i = 1; i < n; i++){
        cin >> a;

        //В массиве arr считаем максимум на префиксах
        arr[i] = init(a, arr[i - 1], i);
    }

    int b[n];
    for (int i = 0; i < n; i++)
        cin >> b[i];

    pair <int, int> ans = calc(n, arr, b);
    cout << ans.first << " " << ans.second << endl;

    return 0;
}
