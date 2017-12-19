#include <bits/stdc++.h>

/* Дана очень длинная последовательность целых чисел длины n.
 * Требуется вывести в отсортированном виде её наименьшие k элементов.
 * Последовательность может не помещаться в память.
 * Время работы O(n * log(k)). Доп. память O(k). Использовать слияние.
 */

using namespace std;

// Сливает два отсортированных куска в отсортированный кусок длины k с выборкой минимальных элементов из первых двух
vector<int> Merge(vector<int> &ans, vector<int> &tmp) {
    vector<int> local_ans((int) ans.size());
    // Указатели на текущее место копирования элемента в local_ans и на текущие элементы в ans и tmp
    int k = 0, i = 0, j = 0;
    while ((k < (int) local_ans.size()) && (i < (int) ans.size()) && (j < (int) tmp.size())){
        if (ans[i] < tmp[j]) {
            local_ans[k] = ans[i];
            i++;
        }
        else {
            local_ans[k] = tmp[j];
            j++;
        }
        k++;
    }

    // Если local_ans не заполнен до конца, значит, в tmp меньше элементов, чем k.
    // Значит, нужно просто переписать элементы из ans пока не заполним до конца
    for ( ; k < (int) local_ans.size(); i++){
        local_ans[k] = ans[i];
        k++;
    }

    return local_ans;
}

int main() {
    int n, k;
    cin >> n >> k;

    vector<int> ans(k);
    for (int i = 0; i < k; i++)
        cin >> ans[i];
    sort(ans.begin(), ans.end());

    // Текущий размер массива tmp, т.к. самый последний кусок может быть размером меньше k
    int tmpsize = k;

    for (int i = k; i < n; i += k) {

        // Если это последний кусок и его размер меньше k
        if (i > n - k)
            tmpsize = n % k;

        vector<int> tmp(tmpsize);
        for (int j = 0; j < tmpsize; j++)
            cin >> tmp[j];
        sort(tmp.begin(), tmp.end());

        // Ответ для i*k первых элементов
        ans = Merge(ans, tmp);
    }

    for (auto elem : ans)
        cout << elem << " ";

    return 0;
}