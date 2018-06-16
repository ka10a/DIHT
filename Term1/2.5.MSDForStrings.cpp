#include <bits/stdc++.h>

/* Дан массив строк. Количество строк не больше 100000.
 * Отсортировать массив методом поразрядной сортировки MSD по символам.
 * Размер алфавита - 256 символов. Последний символ строки = '\0'.
*/

using namespace std;

const int K = 256; // размер алфавита


// Сортировка подсчетом
void CountingSort(vector<string> &arr, int left, int right, int byte, vector<int> &c) {

    // Считаем, сколько каждого символа на месте byte
    for (int i = left; i < right; i++) {
        c[(int) arr[i][byte]]++;
    }

    // Считаем, где должен заканчиваться кусок данного куска с последним символом char(i) на месте byte
    for (int i = 1; i < K + 1; i++) {
        c[i] += c[i - 1];
    }

    // Делаем данный кусок [left, right) отсортированным и записываем в tmp
    vector<string> tmp(right - left);
    for (int i = left; i < right; i++) {
        c[(int) arr[i][byte]]--;
        tmp[c[(int) arr[i][byte]]] = arr[i];
    }

    // Переписываем в arr отсортированный кусок из tmp
    for (int i = left; i < right; i++) {
        arr[i] = tmp[i - left];
    }
}


void MSDsort(vector<string> &arr, int left, int right, int byte = 0) {

    // Если осталось 1 или 0 элементов, их можно не сортировать
    if (right - left <= 1) {
        return;
    }

    // Сортировка куска [left, right) подсчетом
    vector<int> c(K + 1, 0);
    CountingSort(arr, left, right, byte, c);

    for(int i = 1; i < K; i++){
        // Если в куске 0 или 1 элемент, его не надо сортировать
        if (c[i + 1] - c[i] <= 1)
            continue;
        MSDsort(arr, c[i] + left, c[i + 1] + left, byte + 1);
    }
}

int main() {
    int n = 0;

    vector<string> arr;
    string s;
    while (getline(cin, s)){
        s.push_back('\0');
        arr.push_back(s);
        n++;
    }

    MSDsort(arr, 0, n);

    for(auto elem : arr) {

        // Удаляем последний символ, т.к. добавили его при вводе
        elem.pop_back();

        cout << elem << endl;
    }
    return 0;
}
