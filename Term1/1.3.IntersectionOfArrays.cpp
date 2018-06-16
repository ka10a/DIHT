#include <bits/stdc++.h>

using namespace std;
/*
Даны два массива неповторяющихся целых чисел, упорядоченные по возрастанию.
A[0..n-1] и B[0..m-1]. n » m. Найдите их пересечение.
Требуемое время работы: O(m * log k), где k - позиция элементта B[m-1]
в массиве A..
В процессе поиска очередного элемента B[i] в массиве A пользуйтесь
результатом поиска элемента B[i-1]. n, k ≤ 10000.
*/

int binsearch(int* aarr, int left, int right, int b) {
    while (left + 1 < right){
        int mid = (left + right) / 2;
        if (!(aarr[mid] > b))
            left = mid;
        else
            right = mid;
    }
    return left;
}

int main(){
    int n, m;
    cin >> n >> m;

    int *aarr = new int[n];
    for (int i = 0; i < n; i++){
        cin >> aarr[i];
    }

    int last_index = -1;
    int *ans = new int[m];
    int cnt = 0;
    for (int j = 0; j < m; j++){
        int b;
        cin >> b;

        if (last_index == n)
            break;

        //Бинпоиском ищем в массиве А элемент b массива В
        int left = binsearch(aarr, last_index, n, b);

        if ((left < n) && (left > -1) && (aarr[left] == b)){
            ans[cnt] = b;
            cnt++;
        }

        //Запоминаем результат поиска элемента B[i] для следующего B[i+1]
        last_index = left;
    }

    if (cnt > 0){
        cout << ans[0];
        for (int j = 1; j < cnt; j++)
            cout << " " << ans[j];
    }

    delete[] ans;
    delete[] aarr;

    return 0;
}
